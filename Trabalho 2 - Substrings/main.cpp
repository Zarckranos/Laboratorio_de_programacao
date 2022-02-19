#include "instancias_Reais_Trabalho_2.hpp"

#include <cstdlib>
using std::rand; using std::srand;
#include <ctime>
using std::time;

#include <stdio.h>
#include <string.h>
#include <iostream>
using std::cout; using std::cin;

#include <new>
using std::nothrow;

#include <chrono>
using std::chrono::duration; using std::chrono::steady_clock;

//T é o padrão, P é o padrão a ser buscado e O onde deve escrever as ocorrencias
bool forca_bruta(const char *T, const char *P, int *O){
    int *s = O;
    for(const char *i = T; *i != '\0'; ++i){
        //j passeia do ponto i em diante, ponteiro k que começa no inicio do padrão
        const char *j = i, *k = P;

        while(*k != '\0' and *j == *k){ //se os caracteres apontado são iguais, passa pra frente
            ++j; ++k;
        }

        if(*k == '\0'){
            *s = i - T;
            ++s;
        }
    }
    *s = -1;
    return true;
}

bool KMP(const char *T, const char *P, int *O){
    //Computar vetor Auxiliar A
    int m = strlen(P); //tamanho do padrao
    int *A = new(nothrow) int[m]; if(A == nullptr) return false;
    int i = 0, j = -1;
    A[0] = -1;

    while(i+1 < m){
        //Prefixo igual o sufixo?
        if(P[i+1] == P[j+1]){
            A[i+1] = j + 1;
            ++i; ++j;
        } else{
            if(j == -1){
                A[i+1] = -1;
                ++i;
            } else{
                j = A[j];
            }
        }
    }

    //Segunda parte do KMP, buscar padrão no texto
    int n = strlen(T); //tamanho do texto
    int w = 0; //posição "w" do vetor O
    i = 0; j = 0;//Posição "i" do texto para comparar com a "j" do padrão

    while(i < n){ //Invariante: P[0 até j-1] = T[i-j até i-1]
        if(T[i] == P[j]){
            if (j == m-1){
                O[w] = i - j;//Ocorrencia do padrao iniciando em T[i-j]
                ++w;
                j = A[j];
            }
            ++j; ++i;
        } else{ //T[i] != P[J]
            if(j == 0){
                ++i;
            } else{
                j = A[j-1] + 1;
            }
        }
    }
    O[w] = -1;

    delete[] A;
    return true;
}

//Funcao para gerar instancia (pseudo)aleatoria
void gerar_instancia(char *T, char *P, int n, int m, int l){
    srand((unsigned int) time(nullptr));
    
    int max = l - 97; //numero referente ao caractere passado em l. Ex.: l = 'e' = 101 em ascii; 101 - 97 = 4
    int i; char c;

    //Preenchendo o vetor T, o texto, com caracteres pseudoaleatorios
    for(i = 0; i <= n; ++i){ 
        c = 'a' + (rand() % (max+1)) % 26;
        if(i != n){
            T[i] = c;
        } else{
            T[i] = '\0';
        }
    }

    //Preenchendo o vetor P, o padrao, com caracteres pseudoaleatorios
    for(i = 0; i <= m; ++i){
        c = 'a' + (rand() % (max+1)) % 26;
        if(i != m){
            P[i] = c;
        } else{
            P[i] = '\0';
        }
    }
}

//Funcao para comparar a saida do algoritmos. Retorna true para iguais e false para diferentes
bool comparar_saidas(int *Ofb, int *Okmp){
    int i = 0;
    while((Ofb[i] != -1) || (Okmp[i] != -1)){
        if(Ofb[i] != Okmp[i]){ //Se os valores forem diferente, retorna false
            return false;
        }
        ++i;
    }
    return true;
}

//Funcao para calcular o tempo dos algoritmos. I é numero de instancias
bool calc_tempo(const char *T, const char *P, int *Ofb, int *Okmp, double *tempo, int I){
    for(int i = 1; i <= I; ++i){
        auto i1 = steady_clock::now();
        forca_bruta(T, P, Ofb);
        auto f1 = steady_clock::now(); duration<double> tempo_fb = f1-i1;
        tempo[0] = tempo[0] + tempo_fb.count();

        auto i2 = steady_clock::now();
        KMP(T, P, Okmp);
        auto f2 = steady_clock::now(); duration<double> tempo_kmp = f2-i2;
        tempo[1] = tempo[1] + tempo_kmp.count();

        if(!comparar_saidas(Ofb, Okmp)){
            cout << "Saidas diferentes";
            return false;
        }
    }
    return true;
}

int main(int argc, char* argv[]){
    double tempo[2] = {0.0, 0.0}; //vetor com o tempo dos algoritmos. indice 0: forca bruta - FB; indice 1: KMP
    int i = argc; //só pra tirar a mensagem sobre o argc inutilizado

    if(argv[1][0] == 'A'){
        char l = argv[2][0];
        int m = atoi(argv[3]);
        int n = atoi(argv[4]);
        int I = atoi(argv[5]);

        char *texto = new(nothrow) char[n]; if(texto == nullptr) return 1;
        char *padrao = new(nothrow) char[m]; if(padrao == nullptr) return 1;
        gerar_instancia(texto, padrao, n, m, int(l));

        int *Ofb = new(nothrow) int[n+1]; if(Ofb == nullptr) return 1;
        int *Okmp = new(nothrow) int[n+1]; if(Okmp == nullptr) return 1;

        calc_tempo(texto, padrao, Ofb, Okmp, tempo, I);

        delete[] texto;
        delete[] padrao;
        delete[] Ofb;
        delete[] Okmp;
    } else{
        int x = atoi(argv[2]);
        int y = atoi(argv[3]);

        int n = strlen(Texto_Livros);

        int *Ofb = new(nothrow) int[n+1]; if(Ofb == nullptr) return 1;
        int *Okmp = new(nothrow) int[n+1]; if(Okmp == nullptr) return 1;

        for(i = x; i <= y; ++i){
            calc_tempo(Texto_Livros, Padroes_Palavras[i], Ofb, Okmp, tempo, 1);
        }
        delete[] Ofb;
        delete[] Okmp;
    }

    cout << "Tempo do Forca Bruta: " << tempo[0] << '\n';
    cout << "Tempo do KMP: " << tempo[1] << '\n';
}