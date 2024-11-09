#include <stdio.h>
#include "automato.h"

int main()
{
    int D, geracoes;
    scanf("%d %d", &D, &geracoes);

    AutomatoCelular *automato = alocarReticulado(D, geracoes);
    if (!automato)
    {
        printf("Erro ao alocar o reticulado.\n");
        return 1;
    }

    leituraReticulado(automato);

    for (int i = 0; i < geracoes; i++)
    {
        evoluirReticulado(automato);
    }

    imprimeReticulado(automato);

    desalocarReticulado(automato);
    return 0;
}