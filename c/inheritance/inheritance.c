#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Cada pessoa tem dois pais e dois alelos
typedef struct person
{
    struct person *parents[2];
    char alleles[2];
} person;

const int GENERATIONS = 3;
const int INDENT_LENGTH = 4;

person *create_family(int generations);
void print_family(person *p, int generation);
void free_family(person *p);
char random_allele();

int main(void)
{
    // Seed para o gerador de números aleatórios
    srand(time(0));

    // Criar uma nova família com três gerações
    person *p = create_family(GENERATIONS);

    // Imprimir a árvore genealógica dos tipos sanguíneos
    print_family(p, 0);

    // Liberar a memória alocada
    free_family(p);
}

// Criar um novo indivíduo com `generations`
person *create_family(int generations)
{
    // Alocar memória para uma nova pessoa
    person *new_person = malloc(sizeof(person));

    // Se ainda houver gerações para criar
    if (generations > 1)
    {
        // Criar dois novos pais para a pessoa atual, chamando create_family recursivamente
        new_person->parents[0] = create_family(generations - 1);
        new_person->parents[1] = create_family(generations - 1);

        // Atribuir alelos da pessoa atual com base nos alelos dos pais
        new_person->alleles[0] = new_person->parents[0]->alleles[rand() % 2];
        new_person->alleles[1] = new_person->parents[1]->alleles[rand() % 2];
    }
    else
    {
        // Se não houver mais gerações, definir os pais como NULL
        new_person->parents[0] = NULL;
        new_person->parents[1] = NULL;

        // Atribuir alelos aleatórios
        new_person->alleles[0] = random_allele();
        new_person->alleles[1] = random_allele();
    }

    // Retornar a pessoa recém-criada
    return new_person;
}

// Liberar `p` e todos os ancestrais de `p`
void free_family(person *p)
{
    // Caso base: se a pessoa for NULL, retornar
    if (p == NULL)
    {
        return;
    }

    // Liberar os pais recursivamente
    free_family(p->parents[0]);
    free_family(p->parents[1]);

    // Liberar a memória da pessoa atual
    free(p);
}

// Imprimir cada membro da família e seus alelos
void print_family(person *p, int generation)
{
    // Caso base: se a pessoa for NULL, retornar
    if (p == NULL)
    {
        return;
    }

    // Imprimir indentação
    for (int i = 0; i < generation * INDENT_LENGTH; i++)
    {
        printf(" ");
    }

    // Imprimir a pessoa
    if (generation == 0)
    {
        printf("Child (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }
    else if (generation == 1)
    {
        printf("Parent (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }
    else
    {
        for (int i = 0; i < generation - 2; i++)
        {
            printf("Great-");
        }
        printf("Grandparent (Generation %i): blood type %c%c\n", generation, p->alleles[0],
               p->alleles[1]);
    }

    // Imprimir os pais da pessoa atual
    print_family(p->parents[0], generation + 1);
    print_family(p->parents[1], generation + 1);
}

// Escolher aleatoriamente um alelo de tipo sanguíneo
char random_allele()
{
    int r = rand() % 3;
    if (r == 0)
    {
        return 'A';
    }
    else if (r == 1)
    {
        return 'B';
    }
    else
    {
        return 'O';
    }
}
