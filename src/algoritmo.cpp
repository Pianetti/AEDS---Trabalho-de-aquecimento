#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <iomanip>
#include <cmath>
#include "algoritmo.hpp"
#include "individuo.hpp"

using namespace std;

void gerarValoresAleatorios(double& a, double& b, mt19937& gen) {
    uniform_int_distribution<> dis(0, 1000);
    a = dis(gen) / 100.0;
    b = dis(gen) / 100.0;
}

void calcularFitness(vector<Individuo>& individuo, float matriz_coordenadas[][2], int N, int M) {
    for (int j = 0; j < M; j++) {
        individuo[j].erro = 0;
        for (int i = 0; i < N; i++) {
            individuo[j].erro += pow((matriz_coordenadas[i][1] - (matriz_coordenadas[i][0] * individuo[j].a + individuo[j].b)), 2);
        }
        individuo[j].erro = individuo[j].erro / N;
        individuo[j].fitness = 1 / (1 + individuo[j].erro);
    }
}

void ordenar(vector<Individuo>& individuo, int M) {
    for (int j = 0; j < M; j++) {
        for (int i = 0; i < M - 1; i++) {
            if (individuo[i].fitness < individuo[i + 1].fitness) {
                Individuo aux = individuo[i];
                individuo[i] = individuo[i + 1];
                individuo[i + 1] = aux;
            }
        }
    }
}

void crossover(vector<Individuo>& individuo, int M, int geracoes) {
    uniform_int_distribution<> sorteio(0, M / 2 - 1);
    mt19937 chance(geracoes);

    for (int i = M / 2; i < M; i++) {
        int pai_a = sorteio(chance);
        int pai_b = sorteio(chance);

        while (pai_b == pai_a) {
            pai_b = sorteio(chance);
        }

        individuo[i].a = individuo[pai_a].a;
        individuo[i].b = individuo[pai_b].b;
    }
}

void mutacao(vector<Individuo>& individuo, int M, int geracoes) {
    uniform_real_distribution<> mut(-0.5, 0.5);
    mt19937 probabilidade(geracoes);
    uniform_int_distribution<> AouB(0, 1);

    for (int i = M / 2; i < M; i++) {
        if (AouB(probabilidade) == 0) {
            individuo[i].a += mut(probabilidade);
        } else {
            individuo[i].b += mut(probabilidade);
        }
    }
}

void gravarOutput(ofstream& arquivo, int geracao, Individuo& melhor) {
    arquivo << "Número da geração atual: " << geracao + 1 << endl;
    arquivo << "Valor de a:              " << melhor.a << endl;
    arquivo << "Valor de b:              " << melhor.b << endl;
    arquivo << "Valor do erro:           " << melhor.erro << endl;
    arquivo << "Valor do fitness:        " << setprecision(20) << melhor.fitness << endl << endl;
}