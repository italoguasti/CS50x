#include <stdio.h>
#include <stdlib.h>
#include "automato.h"
#include "double_hash.h"

// Função para alocar o reticulado
/*
* Aloca o reticulado
*/
AutomatoCelular *alocarReticulado(int D, int geracoes)
{
    AutomatoCelular *automato = (AutomatoCelular *)malloc(sizeof(AutomatoCelular));
    if (!automato)
        return NULL;
    automato->D = D;
    automato->geracoes = geracoes;
    automato->celulas = (int *)calloc(D * D, sizeof(int)); // Inicializa com zeros
    if (!automato->celulas)
    {
        free(automato);
        return NULL;
    }
    return automato;
}

// Função para desalocar o reticulado
void desalocarReticulado(AutomatoCelular *automato)
{
    if (automato)
    {
        free(automato->celulas);
        free(automato);
    }
}

// Função para ler o reticulado inicial
void leituraReticulado(AutomatoCelular *automato)
{
    for (int i = 0; i < automato->D * automato->D; i++)
    {
        scanf("%d", &(automato->celulas[i]));
    }
}

// Função para evoluir o reticulado de forma recursiva
void evoluirReticulado(AutomatoCelular *automato)
{
    if (automato->geracoes <= 0)
        return;

    int D = automato->D;
    int *novaGeracao = (int *)calloc(D * D, sizeof(int));
    if (!novaGeracao)
        return;

    // Aplica as regras do Jogo da Vida para cada célula
    for (int i = 0; i < D; i++)
    {
        for (int j = 0; j < D; j++)
        {
            int vizinhosVivos = contarVizinhosVivos(automato, i, j);
            int estadoAtual = automato->celulas[i * D + j];

            if (estadoAtual == 1)
            {
                if (vizinhosVivos == 2 || vizinhosVivos == 3)
                {
                    novaGeracao[i * D + j] = 1; // Mantém viva
                }
            }
            else
            {
                if (vizinhosVivos == 3)
                {
                    novaGeracao[i * D + j] = 1; // Renascimento
                }
            }
        }
    }

    // Atualiza a geração atual
    for (int i = 0; i < D * D; i++)
    {
        automato->celulas[i] = novaGeracao[i];
    }

    free(novaGeracao);

    // Reduz o contador de gerações e chama recursivamente
    automato->geracoes--;
    evoluirReticulado(automato);
}

// Função para imprimir o reticulado
void imprimeReticulado(AutomatoCelular *automato)
{
    for (int i = 0; i < automato->D; i++)
    {
        for (int j = 0; j < automato->D; j++)
        {
            printf("%d ", automato->celulas[i * automato->D + j]);
        }
        printf("\n");
    }
}

// Função auxiliar para contar vizinhos vivos
int contarVizinhosVivos(AutomatoCelular *automato, int linha, int coluna)
{
    int D = automato->D;
    int vivos = 0;

    // Definindo as direções para os vizinhos
    int direcoes[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1}};

    // Verifica todas as direções
    for (int i = 0; i < 8; i++)
    {
        int novaLinha = linha + direcoes[i][0];
        int novaColuna = coluna + direcoes[i][1];
        if (novaLinha >= 0 && novaLinha < D && novaColuna >= 0 && novaColuna < D)
        {
            vivos += automato->celulas[novaLinha * D + novaColuna];
        }
    }

    return vivos;
}