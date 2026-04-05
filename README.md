# 🧬 Algoritmo Genético para Ajuste de Função Linear

[![Status](http://img.shields.io/static/v1?label=STATUS&message=EM%20DESENVOLVIMENTO&color=GREEN&style=for-the-badge)]()
[![Linguagem](http://img.shields.io/static/v1?label=Linguagem&message=C%2B%2B&color=GREEN&style=for-the-badge)]()

---

## 📃 Introdução

Este projeto foi desenvolvido como trabalho de aquecimento para a disciplina de Algoritmos e Estruturas de Dados I (AEDS I), ministrada pelo professor Michel Pires da Silva, no Centro Federal de Educação Tecnológica de Minas Gerais (CEFET-MG), Campus V – Divinópolis.

O trabalho consiste na implementação de um Algoritmo Genético (AG) simplificado, aplicado ao problema de ajuste de parâmetros de uma função linear da forma:

**ŷ = ax + b**

Algoritmos Genéticos são meta-heurísticas de busca e otimização inspiradas nos princípios da seleção natural. Neste contexto, cada solução candidata — chamada de **indivíduo** — representa um par de parâmetros (a, b) que define uma reta no plano cartesiano. O algoritmo evolui iterativamente essa população de soluções, aplicando operações de **seleção**, **crossover** e **mutação**, com o objetivo de encontrar a reta que melhor se ajusta a um conjunto de pontos fornecido como entrada.

A qualidade de cada indivíduo é medida por uma função de **fitness**, derivada do Erro Quadrático Médio (MSE) entre os valores reais e os valores estimados pela reta. Quanto menor o erro, maior o fitness — e melhor a solução.

Além de introduzir conceitos de otimização heurística de forma prática, o projeto tem como objetivo consolidar habilidades fundamentais de programação em C++, incluindo manipulação de vetores, uso de estruturas dinâmicas, modularização de código e leitura/escrita de arquivos.

---

## 📋 Problema Proposto

O problema consiste em ajustar uma função linear **ŷ = ax + b** a um conjunto fixo de pontos no plano cartesiano, fornecido como entrada no arquivo `input.dat`. Cada ponto representa uma observação empírica do fenômeno estudado, e o objetivo do algoritmo é encontrar os valores de **a** (coeficiente angular) e **b** (coeficiente linear) que minimizem o erro entre a reta estimada e os pontos reais.

### 📌 Representação dos Indivíduos

Cada indivíduo da população codifica uma hipótese linear, armazenando um par de parâmetros (a, b). Para um indivíduo específico, cada ponto da amostra gera uma predição:

**ŷᵢ = axᵢ + b**

O erro em cada ponto corresponde à diferença vertical entre o valor real e o estimado:

**eᵢ = yᵢ − ŷᵢ**

### 📌 Função de Erro e Fitness

O erro global de cada indivíduo é calculado como o **Erro Quadrático Médio (MSE)**:

**MSE = (1/N) × Σ(yᵢ − ŷᵢ)²**

A partir do erro, o fitness é calculado de forma que **quanto menor o erro, maior o fitness**:

**fitness = 1 / (1 + MSE)**

O fitness varia entre 0 e 1, onde valores próximos de 1 indicam um ajuste de alta qualidade.

### 📌 Etapas do Algoritmo Genético

O ciclo evolutivo segue as seguintes etapas a cada geração:

**1. Inicialização**
A população inicial de M indivíduos é gerada aleatoriamente, com valores de a e b sorteados dentro de limites definidos, controlados por uma semente (seed) para garantir reprodutibilidade.

**2. Avaliação**
O erro e o fitness de cada indivíduo são calculados com base no conjunto de pontos fornecido, que permanece fixo durante toda a execução.

**3. Seleção e Ordenação**
Os indivíduos são ordenados por fitness em ordem decrescente. Os M/2 melhores são preservados e os M/2 piores são substituídos a cada geração.

**4. Crossover (gerações ímpares)**
Os M/2 piores indivíduos são substituídos por filhos gerados a partir da combinação aleatória dos parâmetros dos M/2 melhores:

| Pai 1 | a₁ | b₁ |
|-------|----|----|
| Pai 2 | a₂ | b₂ |
| Filho | a₁ | b₂ |

**5. Mutação (gerações pares)**
Os M/2 piores indivíduos sofrem uma alteração pontual em um dos parâmetros — a ou b — escolhido aleatoriamente, com uma pequena variação controlada δ:

**p = (a, b) → p' = (a, b + δ)**

**6. Atualização**
Após o crossover ou mutação, o fitness é recalculado e a população é reordenada, preparando a próxima geração.

### 📌 Entrada e Saída

O programa lê os dados a partir de um arquivo `input.dat` com o seguinte formato:

```
N M G
x1 y1
x2 y2
...
xN yN
```

Onde:
- **N**: número de pontos do conjunto de dados
- **M**: tamanho da população
- **G**: número de gerações

A cada geração, o arquivo `output.dat` registra o melhor indivíduo, contendo:
- Número da geração
- Valores de a e b
- Erro (MSE)
- Fitness

## 🖥️ Ambiente de Criação
 
O código foi desenvolvido e testado utilizando as seguintes ferramentas e configurações:
 
[![Linguagem](https://img.shields.io/badge/Linguagem-C%2B%2B-blue?style=for-the-badge)]()
[![IDE](https://img.shields.io/badge/IDE-Visual%20Studio%20Code-blueviolet?style=for-the-badge)]()
[![SO](https://img.shields.io/badge/OS-Ubuntu%2024.04.4%20LTS-orange?style=for-the-badge)]()
[![WSL](https://img.shields.io/badge/WSL-2.6.3-orange?style=for-the-badge)]()
 
### 💻 Especificações da Máquina
 
| Componente | Descrição |
|------------|-----------|
| **Processador** | AMD Ryzen 7 7735HS with Radeon Graphics |
| **Memória RAM** | 24 GB |
| **Sistema Operacional** | Ubuntu 24.04.4 LTS |
| **Ambiente** | WSL 2.6.3 (Windows Subsystem for Linux) |
| **Compilador** | g++ (C++17 ou superior) |
| **IDE** | Visual Studio Code |
 
 ## 📁 Estrutura Geral do Projeto
 
```
.
├── Makefile                        # Script de compilação automática do projeto
├── input/
│   └── input.dat                   # Arquivo de entrada com os dados do problema (N, M, G e pontos)
├── output/
│   └── output.dat                  # Arquivo de saída gerado a cada execução com os resultados por geração
└── src/
    ├── individuo.hpp               # Declaração da struct Individuo (a, b, erro, fitness)
    ├── Abre_arquivo.hpp            # Declaração das funções de leitura do arquivo de entrada
    ├── Abre_arquivo.cpp            # Implementação das funções de leitura do arquivo de entrada
    ├── algoritmo.hpp               # Declaração das funções do algoritmo genético
    ├── algoritmo.cpp               # Implementação das funções do algoritmo genético
    └── main.cpp                # Função principal — coordena o fluxo do programa
```
 
### 📌 Descrição dos Módulos
 
**`individuo.hpp`**
Define a estrutura de dados `Individuo`, que armazena os campos `a`, `b`, `erro` e `fitness`. É incluída pelos demais módulos que precisam conhecer a representação de um indivíduo.
 
**`Abre_arquivo.hpp` / `Abre_arquivo.cpp`**
Responsáveis pela leitura do arquivo `input.dat`. Contém duas funções: `lerArquivo`, que lê os parâmetros N, M e G, e `lerCoordenadas`, que preenche a matriz de pontos (x, y).
 
**`algoritmo.hpp` / `algoritmo.cpp`**
Núcleo do algoritmo genético. Contém as funções de geração aleatória de valores, cálculo de fitness, ordenação da população, crossover, mutação e gravação do arquivo de saída.
 
**`main.cpp`**
Coordena o fluxo completo do programa: leitura dos dados, inicialização da população, loop de gerações e encerramento.

## ⚙️ Metodologia
 
Esta seção descreve em detalhes como o algoritmo genético foi implementado, desde a leitura dos dados até o encerramento do ciclo evolutivo.
 
---
 
### 📌 1. Leitura dos Dados
 
A execução inicia com a leitura do arquivo `input.dat`, realizada em duas etapas pelo módulo `Abre_arquivo.cpp`:
 
**Etapa 1 — Leitura dos parâmetros:**
A função `lerArquivo` lê a primeira linha do arquivo, extraindo os valores de N (número de pontos), M (tamanho da população) e G (número de gerações).
 
**Etapa 2 — Leitura das coordenadas:**
A função `lerCoordenadas` reabre o arquivo e preenche a matriz `matriz_coordenadas[N][2]` com os pares (x, y) de cada ponto do conjunto amostral. Esses pontos permanecem fixos durante toda a execução do algoritmo.
 
---
 
### 📌 2. Inicialização da População
 
Após a leitura, são criados M indivíduos com valores de `a` e `b` gerados aleatoriamente pela função `gerarValoresAleatorios`, utilizando o gerador `mt19937` com uma semente (seed) fixa de valor 67, garantindo reprodutibilidade dos experimentos.
 
Cada indivíduo é representado pela struct `Individuo`:
 
```cpp
struct Individuo {
    float a;        // coeficiente angular
    float b;        // coeficiente linear
    float erro;     // Erro Quadrático Médio (MSE)
    float fitness;  // qualidade da solução
};
```
 
---
 
### 📌 3. Avaliação Inicial
 
Antes de entrar no loop de gerações, o fitness de toda a população é calculado uma vez pela função `calcularFitness`. Para cada indivíduo, o erro MSE é computado somando as diferenças quadráticas entre os valores reais e os estimados pela reta:
 
```
MSE = (1/N) × Σ(yᵢ − (a × xᵢ + b))²
```
 
O fitness é então derivado do erro:
 
```
fitness = 1 / (1 + MSE)
```
 
Em seguida, a população é ordenada em ordem decrescente de fitness pela função `ordenar`, usando o algoritmo Bubble Sort. Após a ordenação, o estado inicial (geração 0) é gravado no `output.dat`.
 
---
 
### 📌 4. Ciclo Evolutivo
 
O ciclo evolutivo se repete por G gerações. A cada iteração, o algoritmo executa as seguintes etapas na ordem:
 
```
Para cada geração de 1 até G:
    │
    ├── Se geração PAR → Crossover
    │       Sorteia pais aleatoriamente entre os M/2 melhores
    │       Gera filhos combinando a de um pai e b de outro
    │       Substitui os M/2 piores pelos filhos
    │
    ├── Se geração ÍMPAR → Mutação
    │       Escolhe aleatoriamente entre mutar a ou b
    │       Aplica variação δ ∈ [-0.5, 0.5] no parâmetro escolhido
    │       Aplica nos M/2 piores indivíduos
    │
    ├── Recalcula fitness de toda a população
    ├── Reordena em ordem decrescente de fitness
    └── Grava o melhor indivíduo no output.dat
```
 
#### 4.1 Crossover
 
O crossover combina os parâmetros de dois indivíduos da metade superior da população, sorteados aleatoriamente, para gerar um filho. O sorteio é feito com `uniform_int_distribution` e um gerador `mt19937` com seed baseada no número da geração, garantindo variação entre gerações:
 
```
Pai 1 sorteado aleatoriamente → fornece o valor de a
Pai 2 sorteado aleatoriamente → fornece o valor de b
Filho → (a do Pai 1, b do Pai 2)
```
 
Um laço `while` garante que os dois pais sorteados sejam sempre diferentes, evitando filhos idênticos a um único pai.
 
#### 4.2 Mutação
 
A mutação aplica uma pequena variação controlada δ em um dos parâmetros do indivíduo. O parâmetro a ser mutado (a ou b) é escolhido aleatoriamente a cada indivíduo, introduzindo diversidade sem destruir completamente as soluções existentes:
 
```
Se sorteio == 0:
    a = a + δ    (δ ∈ [-0.5, 0.5])
Senão:
    b = b + δ    (δ ∈ [-0.5, 0.5])
```
 
O intervalo de mutação de ±0.5 foi escolhido para realizar ajustes finos nos parâmetros, evitando variações muito grandes que afastariam os indivíduos das boas soluções já encontradas.
 
---
 
### 📌 5. Ordenação da População
 
A ordenação é feita pelo algoritmo **Bubble Sort**, implementado manualmente na função `ordenar`. O vetor de indivíduos é ordenado em ordem **decrescente** de fitness, garantindo que os melhores sempre ocupem as primeiras posições e sejam preservados nas próximas gerações:
 
```cpp
for(int j = 0; j < M; j++){
    for(int i = 0; i < M - 1; i++){
        if(individuo[i].fitness < individuo[i+1].fitness){
            Individuo aux = individuo[i];
            individuo[i] = individuo[i+1];
            individuo[i+1] = aux;
        }
    }
}
```
 
---
 
### 📌 6. Gravação do Output
 
A função `gravarOutput` registra no arquivo `output.dat` o estado do melhor indivíduo (`individuo[0]`) a cada geração, incluindo o número da geração, os valores de `a` e `b`, o erro MSE e o fitness. O arquivo é aberto uma única vez antes do loop e fechado ao término, evitando sobrescrita dos dados anteriores.
 
Exemplo de saída:
```
Número da geração atual: 1
Valor de a:              2.57
Valor de b:              1.83
Valor do erro:           6.42
Valor do fitness:        0.13459...
```
 
---
 
### 📌 Fluxo Completo Resumido
 
```
lerArquivo()
lerCoordenadas()
inicializarPopulacao()
 
calcularFitness()       ← avaliação inicial
ordenar()               ← ordenação inicial
gravarOutput(geração 0) ← estado inicial
 
Para geração 1 até G:
    crossover() ou mutacao()
    calcularFitness()
    ordenar()
    gravarOutput(geração atual)
 
Exibe melhor indivíduo final
```
 ## 📊 Análises e Conclusões
 
### 📌 1. Complexidade das Principais Rotinas
 
A tabela abaixo apresenta a análise assintótica das principais funções implementadas:
 
| Função | Complexidade de Tempo | Complexidade de Espaço |
|--------|----------------------|------------------------|
| `calcularFitness` | O(M × N) | O(1) |
| `ordenar` (Bubble Sort) | O(M²) | O(1) |
| `crossover` | O(M/2) | O(1) |
| `mutacao` | O(M/2) | O(1) |
| `lerCoordenadas` | O(N) | O(N) |
| **Loop completo (G gerações)** | **O(G × (M×N + M²))** | **O(M + N)** |
 
**Legenda:**
- **N**: número de pontos do conjunto amostral
- **M**: tamanho da população
- **G**: número de gerações
 
#### 1.1 Gargalo Principal — Ordenação
 
O maior custo por geração vem da função `ordenar`, que utiliza Bubble Sort com complexidade **O(M²)**. Para populações pequenas (como M=10), o impacto é desprezível. Porém, para populações maiores, esse custo cresce quadraticamente e pode se tornar o principal gargalo do algoritmo. Uma alternativa mais eficiente seria o uso de algoritmos como Merge Sort ou Quick Sort, com complexidade **O(M log M)**.
 
#### 1.2 Custo de Avaliação
 
A função `calcularFitness` tem custo **O(M × N)** por geração, pois avalia todos os M indivíduos sobre os N pontos do conjunto amostral. Para G gerações, o custo total acumulado é **O(G × M × N)**, tornando-a a operação mais custosa em cenários com muitos pontos.
 
---
 
### 📌 2. Comportamento do Erro ao Longo das Gerações
 
O algoritmo apresenta três fases distintas de comportamento ao longo das gerações:
 
**Fase 1 — Exploração (gerações iniciais)**
Nas primeiras gerações, a população ainda é diversificada e o fitness melhora rapidamente. O crossover e a mutação combinados geram indivíduos significativamente melhores que a população inicial, reduzindo o erro de forma expressiva.
 
**Fase 2 — Convergência (gerações intermediárias)**
À medida que os melhores indivíduos dominam a população, o progresso desacelera. O crossover começa a gerar filhos cada vez mais semelhantes aos pais, pois os melhores indivíduos já têm parâmetros próximos entre si.
 
**Fase 3 — Estagnação (gerações finais)**
A população converge para um valor de fitness estável. A mutação com δ ∈ [-0.5, 0.5] é responsável por manter pequenas variações, mas dificilmente supera o melhor valor já encontrado. Isso indica que o algoritmo atingiu um ótimo local ou global para os parâmetros configurados.
 
---
 
### 📌 3. Impacto dos Parâmetros
 
#### Tamanho da População (M)
Populações maiores aumentam a diversidade genética e reduzem o risco de convergência prematura, porém elevam o custo computacional quadraticamente devido ao Bubble Sort.
 
#### Número de Gerações (G)
Aumentar G permite mais iterações de refinamento, mas após a convergência o ganho marginal por geração se torna praticamente nulo. O algoritmo estagna antes de atingir G gerações na maioria dos casos testados.
 
#### Intervalo de Mutação (δ)
O valor de ±0.5 se mostrou adequado para refinamento após a convergência. Valores maiores (ex: ±10) introduzem variações excessivas que dificultam a convergência, enquanto valores menores tornam a busca muito lenta nas fases iniciais.
 
---
 
### 📌 4. Conclusão
 
O algoritmo genético implementado demonstrou ser capaz de ajustar progressivamente os parâmetros de uma função linear a um conjunto de dados, com melhora consistente do fitness ao longo das gerações. Os principais pontos observados foram:
 
- A **separação entre crossover e mutação** por gerações alternadas se mostrou eficaz, permitindo que o crossover explore combinações dos melhores indivíduos enquanto a mutação introduz diversidade controlada
- A **preservação da metade superior** da população garante que boas soluções não sejam perdidas entre gerações
- O algoritmo **converge rapidamente** nas primeiras centenas de gerações e estagna em seguida, sugerindo que para refinamentos mais precisos seria necessário implementar estratégias como redução progressiva do δ de mutação ou reinicialização parcial da população ao detectar estagnação
- A **reprodutibilidade** garantida pela seed fixa permite comparar experimentos de forma consistente sob as mesmas condições iniciais
 
 ## ⌨️ Instalação e Configuração
 
### 📌 Pré-requisitos
 
Para compilar e executar o projeto, certifique-se de ter instalado:
 
- **g++** com suporte a C++17 ou superior
- **Make**
- **Linux** (Ubuntu 24.04 ou equivalente via WSL)
 
---
 
### 📌 Passo a Passo
 
#### 1. Verificar e instalar o compilador g++
 
```bash
g++ --version
```
 
Caso não esteja instalado ou a versão seja inferior ao C++17:
 
```bash
sudo apt update
sudo apt install g++ -y
```
 
#### 2. Verificar e instalar o Make
 
```bash
make --version
```
 
Caso não esteja instalado:
 
```bash
sudo apt update
sudo apt install make -y
```
 
#### 3. Clonar o repositório
 
```bash
git clone https://github.com/seu-usuario/seu-repositorio.git
cd seu-repositorio
```
 
#### 4. Configurar o arquivo de entrada
 
O arquivo `input/input.dat` deve seguir o seguinte formato:
 
```
N M G
x1 y1
x2 y2
...
xN yN
```
 
Onde:
- **N**: número de pontos do conjunto de dados
- **M**: tamanho da população
- **G**: número de gerações
 
Exemplo:
```
10 10 4000
1.5 3.2
2.3 5.1
3.7 7.4
...
```
 
#### 5. Compilar o projeto
 
```bash
make
```
 
Para recompilar do zero após alterações:
 
```bash
make clean
make
```
 
#### 6. Executar o projeto
 
```bash
make run
```
 
---

## 👨‍💻 Desenvolvido por

<div align="center">

<img src="https://media.licdn.com/dms/image/v2/D4E03AQFe0L1ZeCkDvg/profile-displayphoto-scale_200_200/B4EZgZ2lg9HEAs-/0/1752780398339?e=1776902400&v=beta&t=FT8v-wBpeCAIOPYT4VI-HSHUTbS_Jalbxrgtta31ZQY" width="150" style="border-radius: 50%;" />

### Samuel Pianetti Cordeiro

[![GitHub](https://img.shields.io/badge/GitHub-Perfil-000?style=for-the-badge&logo=github)](https://github.com/pianetti)
[![LinkedIn](https://img.shields.io/badge/LinkedIn-Perfil-0077B5?style=for-the-badge&logo=linkedin&logoColor=white)](https://www.linkedin.com/in/samuel-pianetti-cordeiro-979b742b0/)

</div>

---

### 🚀 Sobre

Desenvolvedor focado em tecnologia, programação e construção de soluções modernas.  
Sempre buscando aprender, evoluir e criar projetos eficientes e escaláveis.
