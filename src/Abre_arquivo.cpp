#include "Abre_arquivo.hpp"
#include <iostream>
#include <fstream>
using namespace std;

void lerArquivo(const string& caminho, int& N, int& M, int& G) {
    ifstream meuArquivo(caminho);
    if (meuArquivo.is_open()) {
        meuArquivo >> N >> M >> G;
        cout << N << " " << M << " " << G << endl;
        meuArquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }
}

void lerCoordenadas(const string& caminho, int N, int M, int G, float matriz_coordenadas[][2]) {
    ifstream meuArquivo(caminho);
    if (meuArquivo.is_open()) {
        meuArquivo >> N >> M >> G;
        for (int i = 0; i < N; i++) {
            meuArquivo >> matriz_coordenadas[i][0] >> matriz_coordenadas[i][1];
            cout << matriz_coordenadas[i][0] << " " << matriz_coordenadas[i][1] << endl;
        }
        meuArquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }
}