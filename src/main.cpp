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

        // Fecha o arquivo
        meuArquivo.close();
    } else {
        cerr << "Erro ao abrir o arquivo!" << endl;
    }

    //Struct que armazena os valores de a e b
    struct Individuo{
        float a, b, erro, fitness;
    };
    vector<Individuo> individuo(M);

    // Matriz para armazenar x e y
    float matriz_coordenadas[N][2];

    // Reabre o arquivo
    meuArquivo.open("/home/samuel/TRABALHOS/AEDS1 - Trabalho de aquecimento/input/Teste.txt");
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
        individuo[j].erro = 0;
        for(int i=0; i<N; i++){
            individuo[j].erro += pow((matriz_coordenadas[i][1] - (matriz_coordenadas[i][0] * individuo[j].a + individuo[j].b)), 2);
        }
        individuo[j].erro = individuo[j].erro / N;
        individuo[j].fitness = 10000 / (1 + individuo[j].erro);

        cout << "Valor do Fitness do indivíduo " << j << ":    " << individuo[j].fitness << endl;

    }

    //Ordenar o vetor do fitness em ordem decrescente
    for(int j = 0; j < M; j++){
            for(int i = 0; i < M - 1; i++){
                if(individuo[i].fitness < individuo[i+1].fitness){
                Individuo aux = individuo[i];
                individuo[i] = individuo[i+1];
                individuo[i+1] = aux;
            }
        }
    }

    for(int j = 0; j < M; j++){
        cout << "Fitness do individuo " << j << ": " << individuo[j].fitness << endl;
    }






    // Seleção e crossover
    for(int geracoes = 0; geracoes < G; geracoes++){
        
        cout << "Gereção " << geracoes + 1 << ": " << endl;

        if(geracoes % 2 == 0){
            individuo[M - 1].a = individuo[0].a;
            individuo[M - 1].b = individuo[1].b;
            individuo[M - 2].a = individuo[1].a;
            individuo[M - 2].b = individuo[0].b;
        } else {

            // Mutação com uma variação aleatória nos 2 piores
            uniform_real_distribution<> mutacao(-10.0, 10.0);

            // Um seed diferente em cada geração
            mt19937 probabilidade(geracoes);
            individuo[M - 1].a += mutacao(probabilidade);
            individuo[M - 1].b += mutacao(probabilidade);
            individuo[M - 2].a += mutacao(probabilidade);
            individuo[M - 2].b += mutacao(probabilidade);
        }

        for (int j=0; j<M; j++){
            individuo[j].erro = 0;
            for(int i=0; i<N; i++){
                individuo[j].erro += pow((matriz_coordenadas[i][1] - (matriz_coordenadas[i][0] * individuo[j].a + individuo[j].b)), 2);
            }
            individuo[j].erro = individuo[j].erro / N;
            individuo[j].fitness = 10000 / (1 + individuo[j].erro);

            cout << "Valor do Fitness do indivíduo " << j << ":    " << individuo[j].fitness << endl;

        }

        //Ordenar o vetor do fitness em ordem decrescente
        for(int j = 0; j < M; j++){
            for(int i = 0; i < M - 1; i++){
                if(individuo[i].fitness < individuo[i+1].fitness){
                    Individuo aux = individuo[i];
                    individuo[i] = individuo[i+1];
                    individuo[i+1] = aux;
                }
            }
        }


    }

    return 0;
}