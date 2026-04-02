#include <iostream>
#include <fstream>
#include <string>
using namespace std;
#include <random>
#include <iomanip>
#include <cmath>
#include "algoritmo.hpp"
#include "individio.hpp"
#include "Abre_arquivo.hpp"

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
    ifstream meuArquivo("/home/samuel/TRABALHOS/AEDS1 - Trabalho de aquecimento/input/input.dat");

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
    meuArquivo.open("/home/samuel/TRABALHOS/AEDS1 - Trabalho de aquecimento/input/input.dat");
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




    //Função que calcula erro e fitness
    for (int j=0; j<M; j++){
        individuo[j].erro = 0;
        for(int i=0; i<N; i++){
            individuo[j].erro += pow((matriz_coordenadas[i][1] - (matriz_coordenadas[i][0] * individuo[j].a + individuo[j].b)), 2);
        }
        individuo[j].erro = individuo[j].erro / N;
        individuo[j].fitness = 1 / (1 + individuo[j].erro);

        cout << "Valor do Fitness do indivíduo " << j << ":    " << setprecision(20) << individuo[j].fitness << endl;

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

    


    //Arquivo do output
    ofstream Arquivo_de_saida("/home/samuel/TRABALHOS/AEDS1 - Trabalho de aquecimento/output/output.dat");

    Arquivo_de_saida << "Número da geração atual:  0" << endl;
    Arquivo_de_saida << "Valor de a:              " << individuo[0].a << endl;
    Arquivo_de_saida << "Valor de b:              " << individuo[0].b << endl;
    Arquivo_de_saida << "Valor do erro:           " << individuo[0].erro << endl;
    Arquivo_de_saida << "Valor do fitness:        " << setprecision(20) << individuo[0].fitness << endl << endl;
    


    if(Arquivo_de_saida.is_open()){


        //Função que calcula erro e fitness
        for(int geracoes = 1; geracoes < G; geracoes++){


            //Geração par: crossover
            if(geracoes % 2 == 0){

                //Escolhe alguém da primeira metade aleatoriamente para fazer o crossover com a metade ruim
                uniform_int_distribution<> crossover(0, M/2 -1);
                mt19937 chance(geracoes);

                for(int i = M/2; i < M; i++){
                    double pai_a = crossover(chance);
                    double pai_b = crossover(chance);
                    
                    while(pai_b == pai_a){
                        pai_b = crossover(chance);
                    }
                    individuo[i].a = individuo[pai_a].a;
                    individuo[i].b = individuo[pai_b].b;
                }

            //Geração ímpar: Mutação
            } else {
                // Mutação com uma variação aleatória na metade pior
                uniform_real_distribution<> mutacao(-0.5, 0.5);

                // Um seed diferente em cada geração
                mt19937 probabilidade(geracoes);

                uniform_int_distribution<> AouB(0,1);
                
                //A metade pior sofre mutação
                for(int i = M/2; i < M; i++){

                    // Esolhe aletoriamente se A ou B será mutado
                    
                    if(AouB(probabilidade) % 2 == 0){
                        individuo[i].a += mutacao(probabilidade);

                    } else{
                        individuo[i].b += mutacao(probabilidade);
                    }
                }
            }

            //Função que calcula erro e fitness
            for (int j=0; j<M; j++){
                individuo[j].erro = 0;
                for(int i=0; i<N; i++){
                    individuo[j].erro += pow((matriz_coordenadas[i][1] - (matriz_coordenadas[i][0] * individuo[j].a + individuo[j].b)), 2);
                }
                individuo[j].erro = individuo[j].erro / N;
                individuo[j].fitness = 1 / (1 + individuo[j].erro);
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
            // printa na tela cada geração
            cout << "Geração " << geracoes + 1 << ": " << endl;

            for (int i = 0; i < M; i++){
                cout << "Valor do Fitness do indivíduo " << i << ":    " << setprecision(20) << individuo[i].fitness << endl;
            }


        Arquivo_de_saida << "Número da geração atual: " << geracoes + 1 << endl;
        Arquivo_de_saida << "Valor de a:              " << individuo[0].a << endl;
        Arquivo_de_saida << "Valor de b:              " << individuo[0].b << endl;
        Arquivo_de_saida << "Valor do erro:           " << individuo[0].erro << endl;
        Arquivo_de_saida << "Valor do fitness:        " << individuo[0].fitness << endl << endl;
        }
        Arquivo_de_saida.close();
    } else{
        cout << "Erro2" << endl;
    }

    return 0;
}