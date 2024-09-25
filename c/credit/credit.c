#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int luhn_check(const char *number);
void check_card_type(const char *number);

int main(void)
{
    char number[20];
    printf("Number: ");
    scanf("%s", number);

    // Remove os não digitos
    for (int i = 0; i < strlen(number); i++)
    {
        if (!isdigit(number[i]))
        {
            printf("INVALID\n");
            return 0;
        }
    }

    // Checa se o número é válido usando o Luhn's Algorithm
    if (!luhn_check(number))
    {
        printf("INVALID\n");
    }
    else
    {
        check_card_type(number);
    }

    return 0;
}

int luhn_check(const char *number)
{
    int sum = 0;
    int length = strlen(number);
    int parity = length % 2;

    for (int i = 0; i < length; i++)
    {
        int digit = number[i] - '0';

        if (i % 2 == parity)
        {
            digit *= 2;
            if (digit > 9)
            {
                digit -= 9;
            }
        }

        sum += digit;
    }

    return (sum % 10) == 0;
}

void check_card_type(const char *number)
{
    int length = strlen(number);

    if (length == 15 && (strncmp(number, "34", 2) == 0 || strncmp(number, "37", 2) == 0))
    {
        printf("AMEX\n");
    }
    else if (length == 16 && (strncmp(number, "51", 2) == 0 || strncmp(number, "52", 2) == 0 ||
                              strncmp(number, "53", 2) == 0 || strncmp(number, "54", 2) == 0 ||
                              strncmp(number, "55", 2) == 0))
    {
        printf("MASTERCARD\n");
    }
    else if ((length == 13 || length == 16) && number[0] == '4')
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
}
    }
