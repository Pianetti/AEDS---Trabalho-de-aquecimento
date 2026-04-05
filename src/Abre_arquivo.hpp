#ifndef ABRE_ARQUIVO_HPP
#define ABRE_ARQUIVO_HPP
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <random>
#include <iomanip>
#include <cmath>
#include <string>

void lerArquivo(const std::string& caminho, int& N, int& M, int& G);
void lerCoordenadas(const std::string& caminho, int N, int M, int G, float matriz_coordenadas[][2]);

#endif