from cs50 import get_float


def main():
    while True:
        change = get_float("Change: ")
        if change >= 0:
            break

    cents = round(change * 100)

    coins = 0

    coin_values = [25, 10, 5, 1]

    for coin in coin_values:
        while cents >= coin:
            cents -= coin
            coins += 1

    print(coins)


if __name__ == "__main__":
    main()
