#ifndef ALGORITMO_HPP
#define ALGORITMO_HPP

#include <vector>
#include <fstream>
#include <random>
#include "individuo.hpp"

void gerarValoresAleatorios(double& a, double& b, std::mt19937& gen);
void calcularFitness(std::vector<Individuo>& individuo, float matriz_coordenadas[][2], int N, int M);
void ordenar(std::vector<Individuo>& individuo, int M);
void crossover(std::vector<Individuo>& individuo, int M, int geracoes);
void mutacao(std::vector<Individuo>& individuo, int M, int geracoes);
void gravarOutput(std::ofstream& arquivo, int geracao, Individuo& melhor);

#endif
