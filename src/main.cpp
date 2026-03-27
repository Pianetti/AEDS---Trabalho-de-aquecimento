#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <random>
#include <iomanip>
#include <cmath>

void gerarValoresAleatorios(double &a, double &b, mt19937& gen){
    uniform_int_distribution<> dis(0, 1000); 
    a = dis(gen) / 100.0; 
    b = dis(gen) / 100.0; 
}
int main() {
    // Valores de entrada
    int N, M, G;

    // Matriz para armazenar x e y
    float matriz_coordenadas[N][2];

    //Struct que armazena os valores de a e b
    struct {
        float a, b, erro, fitness;
    } individuo[M];
    
    // seed
    int seed = 67;
    double valorA, valorB;
    // Abre o arquivo para leitura
    ifstream meuArquivo("/home/samuel/TRABALHOS/AEDS1 - Trabalho de aquecimento/input/Teste.txt");

    // Verifica se o arquivo abriu corretamente
    if (meuArquivo.is_open()) {

        // Lê os valores de N, M e G
        meuArquivo >> N >> M >> G; 
        cout << N << " " << M << " " << G << endl;

        // Lê linha por linha até o final do arquivo
        for(int i=0; i<N; i++){            
                meuArquivo >> matriz_coordenadas[i][0] >> matriz_coordenadas[i][1];
                cout << matriz_coordenadas[i][0] << " " << matriz_coordenadas[i][1] << endl;
        }
        // Fecha o arquivo
        meuArquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    //FUnção que gera valores aleatórios para a e b
    mt19937 gerar_seed(seed);
    cout << fixed << setprecision(2);

    for(int i=0; i<M; i++){
        gerarValoresAleatorios(valorA, valorB, gerar_seed);
        individuo[i].a = valorA;
        individuo[i].b = valorB;
        cout << "Valor A: " << valorA << " Valor B: " << valorB << endl;
    }
    
    // Calcular erro e fitness de cada indivíduo
    for (int j=0; j<M; j++){
        for(int i=0; i<N; i++){
            individuo[j].erro += pow((matriz_coordenadas[i][1] - (matriz_coordenadas[i][0] * individuo[j].a + individuo[j].b)), 2);
        }
        individuo[j].erro = individuo[j].erro / N;
        individuo[j].fitness = 1 / (1 + individuo[j].erro);

        cout << "Valor do Fitness do indivíduo " << j << ":    " << individuo[j].fitness << endl;

    }


    return 0;
}