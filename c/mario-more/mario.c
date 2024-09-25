#include <stdio.h>

int main()
{

    int height;

    do
    {
        printf("Digite a altura da pirâmide (entre 1 e 8): ");
        scanf("%d", &height);
    }
    while (height < 1 || height > 8);
    {
        for (int i = 1; i <= height; i++)
        {
            for (int j = 0; j < height - i; j++)
            {
                printf(" ");
            }

            for (int j = 0; j < i; j++)
            {
                printf("#");
            }

            printf("  ");

            for (int j = 0; j < i; j++)
            {
                printf("#");
            }

            printf("\n");
        }
    }
    return 0;
}
