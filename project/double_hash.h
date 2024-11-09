#ifndef DOUBLE_HASH_H
#define DOUBLE_HASH_H

typedef struct
{
    int *table; // Tabela de células vivas
    int size;   // Tamanho da tabela
    int count;  // Contador de células vivas
} HashTable;

HashTable *criarTabela(int size);
void destruirTabela(HashTable *table);
int inserirTabela(HashTable *table, int key, int value);
int buscarTabela(HashTable *table, int key);
int hash1(int key, int size);
int hash2(int key, int size);

#endif