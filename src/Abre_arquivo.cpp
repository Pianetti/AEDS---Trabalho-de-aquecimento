
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <random>
#include <iomanip>
#include <cmath>
#include "Abre_arquivo.hpp"

void leitura_do_arquivo(const string& arquivo, int& N, int& M, int& G){
    ifstream meuArquivo(arquivo);
    if (meuArquivo.is_open()){
        meuArquivo >> N >> M >> G;
        cout << N << " " << M << " " << G << endl;
        meuArquivo.close();
    } else {
        cerr << "Erro ao abrir arquivo" << endl;
    }
}


void gravar_no_arquivo(const string& arquivo, int){
    
}