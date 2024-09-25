#include <ctype.h>
#include <stdio.h>
#include <string.h>

int calcula_pontuacao(const char *palavra)
{
    int pontuacao = 0;
    int valores[26] = {1, 3, 3, 2,  1, 4, 2, 4, 1, 8, 5, 1, 3,
                       1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

    for (int i = 0; palavra[i] != '\0'; i++)
    {
        char letra = toupper(palavra[i]);
        if (letra >= 'A' && letra <= 'Z')
        {
            pontuacao += valores[letra - 'A'];
        }
    }

    return pontuacao;
}

int main()
{
    char palavra1[100], palavra2[100];

    // Entrada da palavra do Jogador 1
    printf("Jogador 1: ");
    scanf("%s", palavra1);

    // Entrada da palavra do Jogador 2
    printf("Jogador 2: ");
    scanf("%s", palavra2);

    // Calcula as pontuações
    int pontuacao1 = calcula_pontuacao(palavra1);
    int pontuacao2 = calcula_pontuacao(palavra2);

    // Determina o vencedor
    if (pontuacao1 > pontuacao2) {
        printf("Player 1 wins!\n");
    } else if (pontuacao2 > pontuacao1) {
        printf("Player 2 wins!\n");
    } else {
        printf("Tie!\n");
    }

    return 0;
}
