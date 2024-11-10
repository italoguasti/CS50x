# Final Project

Este é o projeto final. O projeto final é uma oportunidade de colocar em prática minhas novas habilidades em programação e desenvolver um software próprio de forma livre.

<div align="center" style="display: flex; justify-content: center;">
    <img src="https://github.com/user-attachments/assets/3a883f9f-0025-433d-a36b-933c61d96e41" style="width: 20%;">
    &nbsp;&nbsp;&nbsp;
    <img src="https://github.com/user-attachments/assets/45ba926d-a54b-4000-a4ce-16d668e3886f" style="width: 20%;">
</div>

## Autómato celular - Jogo da vida

Um autômato celular é um modelo matemático usado para simular sistemas complexos com base em regras simples. Ele consiste em uma grade de células (geralmente bidimensional) onde cada célula pode estar em um de vários estados (como "ativo" ou "inativo"). O estado de cada célula evolui ao longo de iterações, determinado por regras locais que dependem do estado das células vizinhas.

O exemplo mais famoso é o Jogo da Vida de John Conway, em que células "vivem", "morrem" ou "nascem" dependendo do número de vizinhos ativos. Autômatos celulares são aplicados em áreas como biologia, física e ciência da computação para estudar fenômenos como crescimento de populações, propagação de incêndios e padrões na natureza.

## Diretivas de compilação

Para compilar o projeto é necessário um ambiente C configurado, recomendo utilizar a IDE VSCode. Sendo assim, em seu terminal acesse a pasta do projeto e rode o comando:

```bash
make
```

O `Makefile` irá compilar automaticamente todos os arquivos necessários. Após a compilação, você pode executar o programa com o comando:

```bash
./exe
```

### Input do Programa

1. Ao rodar o executável, primeiro insira o tamanho do reticulado desejado. Exemplo: `3 3`.
2. Em seguida, insira os valores das células do autômato (usando `1` e `0`) conforme o tamanho do reticulado especificado, lembrando que `1` para uma célula viva e `0` para uma célula morta.

### Entrada via arquivo

Para facilitar a execução, você também pode inserir o reticulado através de um arquivo.
Deixei algumas entradas prontas nos arquivos dentro da pasta /inputs o intuito é facilitar o uso do programa.

```bash
./exe < ./inputs/4-4.in
```
O arquivo de entrada assim como (`4-4.in`) deve conter o tamanho do reticulado na primeira linha, seguido pela matriz de células nas linhas subsequentes.

<div align="center" style="display: flex; justify-content: center;">
    <img src="https://github.com/user-attachments/assets/aa24ffa4-7003-4f6e-8be8-de9c988ef597" style="width: 20%;">
</div>





