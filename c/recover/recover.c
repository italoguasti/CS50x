#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Definir tamanho do bloco como 512 bytes
#define BLOCK_SIZE 512

// Definir um tipo para representar um byte
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Verificar se o número de argumentos é 2
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Abrir o arquivo de imagem forense
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];
    FILE *img = NULL;
    int file_counter = 0;
    char filename[8];
    int jpeg_found = 0;

    // Ler o arquivo de imagem bloco por bloco
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Verificar se encontramos o início de um novo JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // Se já temos um JPEG aberto, fechá-lo
            if (jpeg_found)
            {
                fclose(img);
            }
            else
            {
                jpeg_found = 1; // Encontramos o primeiro JPEG
            }

            // Criar um novo arquivo JPEG
            sprintf(filename, "%03i.jpg", file_counter);
            img = fopen(filename, "w");
            file_counter++;
        }

        // Se já estamos escrevendo em um JPEG, continuar escrevendo
        if (jpeg_found)
        {
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }

    // Fechar quaisquer arquivos abertos
    if (img != NULL)
    {
        fclose(img);
    }

    // Fechar o arquivo de imagem forense
    fclose(file);

    return 0;
}
