#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    int letras = 0, palavras = 1, frases = 0;
    char texto[1000];

    // Obter o texto do usuário
    printf("Text: ");
    fgets(texto, sizeof(texto), stdin);

    // Iterar sobre cada caractere do texto
    for (int i = 0, n = strlen(texto); i < n; i++)
    {
        if (isalpha(texto[i]))
        {
            letras++;
        }
        else if (texto[i] == ' ')
        {
            palavras++;
        }
        else if (texto[i] == '.' || texto[i] == '!' || texto[i] == '?')
        {
            frases++;
        }
    }

    // Calcular L e S
    float L = (float) letras / palavras * 100;
    float S = (float) frases / palavras * 100;

    // Calcular o índice Coleman-Liau
    float indice = 0.0588 * L - 0.296 * S - 15.8;

    // Arredondar o índice para o inteiro mais próximo
    int grau = round(indice);

    // Exibir o grau correspondente
    if (grau < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (grau >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", grau);
    }

    return 0;
}
