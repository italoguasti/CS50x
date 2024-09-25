from cs50 import get_int


def print_pyramid(height):
    for i in range(1, height + 1):
        print(" " * (height - i) + "#" * i)


def main():
    height = 0
    while height < 1 or height > 8:
        height = get_int("Height: ")

    print_pyramid(height)


if __name__ == "__main__":
    main()
