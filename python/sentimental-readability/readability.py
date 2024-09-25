from cs50 import get_string


def main():
    # Solicita ao usuário um texto
    text = get_string("Text: ")

    # Inicializa contadores
    letters = 0
    words = 0
    sentences = 0

    # Percorre cada caractere no texto
    for char in text:
        if char.isalpha():  # Conta letras
            letters += 1
        elif char == ' ':  # Conta palavras
            words += 1
        elif char in ['.', '!', '?']:  # Conta sentenças
            sentences += 1

    # Adiciona 1 ao contador de palavras para contar a última palavra
    words += 1

    # Calcula L e S
    L = (letters / words) * 100
    S = (sentences / words) * 100

    # Calcula o índice de Coleman-Liau
    index = round(0.0588 * L - 0.296 * S - 15.8)

    # Determina a saída conforme o índice
    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print(f"Grade {index}")


if __name__ == "__main__":
    main()
