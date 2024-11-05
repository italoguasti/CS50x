import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    # Obter informações sobre as ações do usuário
    stocks = db.execute("""
        SELECT symbol, SUM(shares) as total_shares
        FROM transactions
        WHERE user_id = ?
        GROUP BY symbol
        HAVING total_shares > 0
    """, session["user_id"])

    # Obter saldo de caixa do usuário
    cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

    # Inicializar valor total das ações com o saldo em caixa
    total_value = cash

    # Lista de ações para enviar ao template
    portfolio = []

    # Calcular valor total das ações e preparar os dados para o template
    for stock in stocks:
        stock_info = lookup(stock["symbol"])

        # Verifica se a função lookup retornou um resultado válido
        if stock_info is None:
            return apology("Invalid stock symbol")

        # Calcular o valor total de cada ação e armazenar no portfólio
        current_price = stock_info["price"]
        total_stock_value = stock["total_shares"] * current_price
        total_value += total_stock_value

        # Adiciona as informações ao portfólio
        portfolio.append({
            "symbol": stock["symbol"],
            "shares": stock["total_shares"],
            "price": current_price,
            "total": total_stock_value
        })

    # Renderizar o template index.html com os dados reais
    return render_template("index.html", stocks=portfolio, cash=cash, total_value=total_value)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        # Obter dados do formulário
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Verificar se os campos estão preenchidos
        if not symbol:
            return apology("must provide a stock symbol", 400)
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("invalid number of shares", 400)

        # Buscar informações da ação
        stock = lookup(symbol)
        if stock is None:
            return apology("invalid stock symbol", 400)

        # Obter dinheiro disponível do usuário
        user_cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])[0]["cash"]

        # Calcular o custo da compra
        total_cost = stock["price"] * int(shares)

        # Verificar se o usuário tem dinheiro suficiente
        if total_cost > user_cash:
            return apology("cannot afford", 400)

        # Inserir a transação na base de dados e atualizar saldo
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session["user_id"], symbol, shares, stock["price"])
        db.execute("UPDATE users SET cash = cash - ? WHERE id = ?", total_cost, session["user_id"])

        # Flash de sucesso e redirecionamento
        flash("Bought!")
        return redirect("/")

    else:
        return render_template("buy.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    if request.method == "POST":
        # Obter dados do formulário
        symbol = request.form.get("symbol")
        shares = request.form.get("shares")

        # Verificar se os campos estão preenchidos
        if not symbol:
            return apology("must provide a stock symbol", 400)
        elif not shares or not shares.isdigit() or int(shares) <= 0:
            return apology("invalid number of shares", 400)

        # Verificar se o usuário possui a ação e a quantidade informada
        user_shares = db.execute("SELECT SUM(shares) as total_shares FROM transactions WHERE user_id = ? AND symbol = ? GROUP BY symbol",
                                 session["user_id"], symbol)[0]["total_shares"]
        if int(shares) > user_shares:
            return apology("too many shares", 400)

        # Buscar informações da ação
        stock = lookup(symbol)

        # Atualizar a tabela de transações e o saldo do usuário
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price) VALUES (?, ?, ?, ?)",
                   session["user_id"], symbol, -int(shares), stock["price"])
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?",
                   stock["price"] * int(shares), session["user_id"])

        # Flash de sucesso e redirecionamento
        flash("Sold!")
        return redirect("/")

    else:
        stocks = db.execute(
            "SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol HAVING SUM(shares) > 0", session["user_id"])
        return render_template("sell.html", stocks=stocks)


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # Buscar todas as transações do usuário
    transactions = db.execute("""
        SELECT symbol, shares, price, transacted
        FROM transactions
        WHERE user_id = ?
        ORDER BY transacted DESC
        """, session["user_id"])

    # Renderizar o template com as transações reais
    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        # Obter símbolo da ação do formulário
        symbol = request.form.get("symbol")

        # Verificar se o campo de símbolo está vazio
        if not symbol:
            return apology("must provide a stock symbol", 400)

        # Obter cotação da ação
        stock = lookup(symbol)
        if stock is None:
            return apology("invalid stock symbol", 400)

        # Renderizar resultado da cotação
        return render_template("quoted.html", stock=stock)

    # Método GET: renderizar o formulário de cotação
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        # Obter dados do formulário
        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Verificar se algum campo está vazio
        if not username:
            return apology("must provide username", 400)
        elif not password:
            return apology("must provide password", 400)
        elif not confirmation:
            return apology("must provide confirmation", 400)

        # Verificar se as senhas são iguais
        if password != confirmation:
            return apology("passwords do not match", 400)

        # Tentar inserir o novo usuário no banco de dados
        try:
            # Gerar hash da senha
            hash = generate_password_hash(password)
            # Inserir usuário
            db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)
        except ValueError:
            return apology("username already exists", 400)

        # Redirecionar o usuário para a página de login
        return redirect("/login")

    # Método GET: renderizar o formulário de registro
    else:
        return render_template("register.html")


@app.route("/deposit", methods=["GET", "POST"])
@login_required
def deposit():
    """Allow user to deposit money to their account"""
    if request.method == "POST":
        # Obter valor do formulário
        amount = request.form.get("amount")

        # Verificar se o valor é válido
        if not amount or not amount.isdigit() or int(amount) <= 0:
            return apology("invalid amount", 400)

        amount = int(amount)

        # Verificar se o valor excede o máximo permitido
        if amount > 5000:
            return apology("Máx Value 5000", 400)

        # Atualizar saldo do usuário
        db.execute("UPDATE users SET cash = cash + ? WHERE id = ?", amount, session["user_id"])

        # Redirecionar para a página inicial com mensagem de sucesso
        flash("Deposited!")
        return redirect("/")

    # Se for GET, renderizar o template de depósito
    return render_template("deposit.html")
