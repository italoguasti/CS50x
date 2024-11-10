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

O reticulado bidimensional possui células em dois estados: viva ou morta. A cada transição (ou iteração), o estado de uma célula pode ou não ser alterado de acordo com as células vizinhas. O conjunto de regras incluem:
- Uma célula viva se mantém viva se tiver 2 (duas) ou 3 (três) células vizinhas vivas;
- Uma célula viva torna-se morta se houver mais de 3 (três) células vizinhas vivas por superpopulação (sufocamento);
- Umacélula viva torna-se morta se houver menos que 2 (duas) células vizinhas vivas por subpopulação (solidão);
- Uma célula morta torna-se viva se houver exatamente 3 (três) células vizinhas vivas, por reprodução
 (renascimento).

Dessa forma, após a inserção de um retículado válido o programa irá gerar o resultado e imprimi-lo para o usuário.
<br> Você pode entender melhor visualmente sobre o funcionamento do automato celular [através deste site](http://cauequeiroz.com.br/game-of-life/) desenvolvido por Caue Queiroz.

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

## Estrutura e Código

Este projeto implementa um autômato celular usando estruturas de dados e algoritmos de hash duplo para armazenar e processar o estado das células em um reticulado (grid).

### Estrutura do Projeto

O projeto é composto por vários arquivos em C (.c) e cabeçalhos (.h):

- **Arquivos `.c`**: Contêm a implementação das funções e a lógica do programa.
- **Arquivos `.h`**: São cabeçalhos que contêm definições de estruturas e declarações de funções, facilitando a organização e a reutilização do código.

### Descrição dos Arquivos

#### `automato.c`

Este arquivo implementa as funções principais para gerenciar o autômato celular, incluindo a alocação e evolução do reticulado.

- **`alocarReticulado`**: Aloca a memória para o reticulado, definindo a dimensão (`D x D`) e o número de gerações. Inicializa as células com valor `0` (inativas).
- **`desalocarReticulado`**: Libera a memória alocada para o reticulado.
- **`leituraReticulado`**: Lê o estado inicial das células do reticulado a partir do input.
- **`evoluirReticulado`**: Aplica as regras do Jogo da Vida para evoluir o reticulado. Para cada célula, conta o número de vizinhos vivos usando `contarVizinhosVivos` e decide o próximo estado da célula (mantém viva, renasce ou permanece inativa).
- **`imprimeReticulado`**: Exibe o reticulado na saída padrão.
- **`contarVizinhosVivos`**: Conta o número de células vizinhas vivas para determinar o estado da célula na próxima geração.

#### `automato.h`

Este cabeçalho declara as funções e a estrutura `AutomatoCelular`, que representa o autômato celular. A estrutura inclui:
- **`D`**: Dimensão do reticulado (`D x D`).
- **`geracoes`**: Número de gerações a serem processadas.
- **`celulas`**: Array que armazena o estado das células.

As funções definidas aqui incluem a alocação, desalocação, evolução e impressão do reticulado, bem como a contagem de vizinhos vivos.

#### `double_hash.c`

Este arquivo implementa uma tabela hash com hashing duplo para armazenar dados de maneira eficiente. Neste contexto, o hash duplo pode ser utilizado para rastrear estados das células vivas ao longo das gerações, se necessário.

- **`criarTabela`**: Aloca uma tabela hash e inicializa seus valores.
- **`destruirTabela`**: Libera a memória da tabela hash.
- **`hash1` e `hash2`**: Funções de hash para indexação na tabela, garantindo uma dispersão eficiente dos valores.
- **`inserirTabela`**: Insere um valor na tabela hash usando hashing duplo para evitar colisões.
- **`buscarTabela`**: Busca uma chave na tabela hash, retornando o índice onde está armazenada ou `-1` se não for encontrada.

#### `double_hash.h`

Este cabeçalho declara a estrutura `HashTable` e as funções para manipular a tabela hash. A estrutura contém:
- **`table`**: Array que representa a tabela hash.
- **`size`**: Tamanho da tabela hash.
- **`count`**: Número de células vivas registradas.

Funções declaradas incluem criação, destruição, inserção e busca na tabela hash.

#### `main.c`

O arquivo principal que executa o autômato celular. A função `main` faz o seguinte:

1. Lê as dimensões do reticulado (`D`) e o número de gerações a serem processadas.
2. Aloca o reticulado com `alocarReticulado`.
3. Lê o estado inicial das células usando `leituraReticulado`.
4. Evolui o reticulado pelas gerações especificadas, chamando `evoluirReticulado`.
5. Imprime o estado final do reticulado com `imprimeReticulado`.
6. Libera a memória com `desalocarReticulado`.

### Estruturas de Dados Utilizadas

- **Estrutura `AutomatoCelular`**: Representa o reticulado e o número de gerações.
- **Tabela Hash com Hash Duplo**: Armazena células vivas para consultas rápidas, permitindo que o programa rastreie o estado das células e otimize a execução de operações como busca e inserção.

Essas estruturas ajudam a gerenciar o estado do autômato de forma eficiente e escalável.






