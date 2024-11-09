#include <stdlib.h>
#include "double_hash.h"

// Função para criar a tabela hash
HashTable *criarTabela(int size)
{
    HashTable *table = (HashTable *)malloc(sizeof(HashTable));
    if (!table)
        return NULL;
    table->table = (int *)calloc(size, sizeof(int));
    table->size = size;
    table->count = 0;
    return table;
}

// Função para destruir a tabela hash
void destruirTabela(HashTable *table)
{
    if (table)
    {
        free(table->table);
        free(table);
    }
}

// Funções de hash
int hash1(int key, int size)
{
    return (key % size);
}

int hash2(int key, int size)
{
    return (1 + (key % (size - 1)));
}

// Função para inserir na tabela hash
int inserirTabela(HashTable *table, int key, int value)
{
    int index = hash1(key, table->size);
    int step = hash2(key, table->size);
    while (table->table[index] != 0)
    {
        index = (index + step) % table->size;
    }
    table->table[index] = value;
    table->count++;
    return index;
}

// Função para buscar na tabela hash
int buscarTabela(HashTable *table, int key)
{
    int index = hash1(key, table->size);
    int step = hash2(key, table->size);
    while (table->table[index] != 0)
    {
        if (table->table[index] == key)
            return index;
        index = (index + step) % table->size;
    }
    return -1;
}