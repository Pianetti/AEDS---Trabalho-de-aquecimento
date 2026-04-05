#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>
#include <cmath>
using namespace std;

#include "algoritmo.hpp"
#include "individuo.hpp"
#include "Abre_arquivo.hpp"


int main() {
    int N, M, G;
    int seed = 67;
    double valorA, valorB;

    string caminho = "input/input.dat";

    lerArquivo(caminho, N, M, G);

    vector<Individuo> individuo(M);
    float matriz_coordenadas[1000][2];

    lerCoordenadas(caminho, N, M, G, matriz_coordenadas);

    mt19937 gerar_seed(seed);
    cout << fixed << setprecision(2);

    for (int i = 0; i < M; i++) {
        gerarValoresAleatorios(valorA, valorB, gerar_seed);
        individuo[i].a = valorA;
        individuo[i].b = valorB;
        cout << "Valor A: " << valorA << " Valor B: " << valorB << endl;
    }

    // Calcula e ordena população inicial
    calcularFitness(individuo, matriz_coordenadas, N, M);
    ordenar(individuo, M);

    // Abre arquivo de saída
    ofstream arquivoSaida("output/output.dat");
    if (!arquivoSaida.is_open()) {
        cerr << "Erro ao abrir output.dat!" << endl;
        return 1;
    }

    // Grava geração 0
    gravarOutput(arquivoSaida, 0, individuo[0]);

    // Loop de gerações
    for (int geracoes = 1; geracoes < G; geracoes++) {

        if (geracoes % 2 == 0) {
            crossover(individuo, M, geracoes);
        } else {
            mutacao(individuo, M, geracoes);
        }

        calcularFitness(individuo, matriz_coordenadas, N, M);
        ordenar(individuo, M);

        cout << "Geração " << geracoes + 1 << ":" << endl;
        for (int i = 0; i < M; i++) {
            cout << "Fitness do indivíduo " << i << ": " << setprecision(20) << individuo[i].fitness << endl;
        }

        gravarOutput(arquivoSaida, geracoes, individuo[0]);
    }

    arquivoSaida.close();

    cout << "\n--- Melhor indivíduo final ---" << endl;
    cout << "a = " << individuo[0].a << endl;
    cout << "b = " << individuo[0].b << endl;
    cout << "erro = " << individuo[0].erro << endl;
    cout << "fitness = " << setprecision(20) << individuo[0].fitness << endl;

    return 0;
}
