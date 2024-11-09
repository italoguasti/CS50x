#ifndef AUTOMATO_H
#define AUTOMATO_H

typedef struct
{
    int D;        // Dimensão do reticulado (D x D)
    int geracoes; // Número de gerações a processar
    int *celulas; // Array de células
} AutomatoCelular;

// Funções para o TAD
AutomatoCelular *alocarReticulado(int D, int geracoes);
void desalocarReticulado(AutomatoCelular *automato);
void leituraReticulado(AutomatoCelular *automato);
int contarVizinhosVivos(AutomatoCelular *automato, int linha, int coluna); // Função auxiliar para evoluirReticulado
void evoluirReticulado(AutomatoCelular *automato);
void imprimeReticulado(AutomatoCelular *automato);

#endif