#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main() {
    // Valores de entrada
    int N, M, G;
    int num_pessoas = 10;
    // Matriz para armazenar x e y
    float matriz[10][2];
    
    // Abre o arquivo para leitura
    ifstream meuArquivo("/home/samuel/TRABALHOS/AEDS1 - Trabalho de aquecimento/input/Teste.txt");
    string linha;

    // Verifica se o arquivo abriu corretamente
    if (meuArquivo.is_open()) {

        // Lê os valores de N, M e G
        meuArquivo >> N >> M >> G; 
        cout << N << " " << M << " " << G << endl;

        // Lê linha por linha até o final do arquivo
        for(int i=0; i<num_pessoas; i++){            
                meuArquivo >> matriz[i][0] >> matriz[i][1];
                cout << matriz[i][0] << " " << matriz[i][1] << endl;

        }
        // Fecha o arquivo
        meuArquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    return 0;
}