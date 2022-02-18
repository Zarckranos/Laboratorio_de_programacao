#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <cstdlib>
using std::atoi;
using std::cout; using std::cin;

#include <new>
using std::nothrow;

#include <random>
using std::mt19937; using std::random_device;
using std::uniform_int_distribution;

#include <chrono>
using std::chrono::duration; using std::chrono::steady_clock;

template <typename T>
//pega um nó e seu maior filho e troca eles de posições - desse o nó em questão
void descer(T *vetor, int i, int filho, int n){
    //faz a troca do nós: vetor e seu filho
    T copia = vetor[i];
    vetor[i] = vetor[filho];
    vetor[filho] = copia;
    
    //indices dos filhos esq. e dir. de filho
    int filhoEsq = 2*filho+1;
    int filhoDir = 2*filho+2;
    int maior = filho; //inicia maior como o filho que foi recebido
    if(filhoEsq <= n && vetor[filhoEsq] > vetor[maior]){ //Se o nó em questão tem filho esquerdo e ele é menor que seu filho
        maior = filhoEsq;
    }
    if(filhoDir <= n && vetor[filhoDir] > vetor[maior]){ //Se tem filho direito e ele é menor que ele
        maior = filhoDir;
    }
    if(maior != filho){ //Caso maior ao final for diferente do que foi definido no começo, chamar descer
        descer(vetor, filho, maior, n);
    }
}

template <typename T>
//Construa um heap a partir de um vetor recebido, após troca o último pelo primeiro e ordena o heap novamente
//fazer isso até o último igual a primeira posição do vetor
void heapMax(T *vetor, int n){
    int esq, dir, maior;
    //consertar a heap de baixo para cima - Floyd
    for(int i = n/2; i >= 0; --i){
        esq = 2*i+1; 
        dir = 2*i+2;
        maior = i;
        //verifica se tem filhos
        if(esq <= n && vetor[esq] > vetor[maior]){ //verificar se tem filho esquerdo 
            maior = esq;
        }
        if(dir <= n && vetor[dir] > vetor[maior]){ //verificar se tem filho direito
            maior = dir;
        }
        if(maior != i){
            descer<int>(vetor, i, maior, n);
        }
    }
}

template <typename T>
//ordena o vetor atraves do HeapMax e troca o conteúdo do último índice com o primeiro
//em seguida ordena o vetor novamente até n = 0;
void heapsort(T *vetor, int n){
    if(n > 0){
        heapMax(vetor, n);
        T copia = vetor[0];
        vetor[0] = vetor[n];
        vetor[n] = copia;
        heapsort(&vetor[0], n-1);
    }
}

//retorna o índice do elemento do meio no intervalo
int pivo(int inicio, int fim){
    return (inicio+fim)/2;
}

int pivo_ale(int inicio, int fim){
    random_device dar_semente; mt19937 gerador( dar_semente() );
    uniform_int_distribution<int> distribuicao(inicio, fim);
    return distribuicao(gerador);
}

template <typename T>
//Pega o pivô e coloca no inicio
//Algoritmo de Antony Hoare
int particionar(T *vetor, int i, int p, int f){
    T copia = vetor[i]; 
    //definindo as setas
    int setaE = i + 1;
    int setaD = f;
    if(setaE == setaD){ //asseguro que em caso das seta forem iguais no começo não ocorra troca desnecessaria
        if(vetor[i] > vetor[setaD]){
            copia = vetor[setaD];
            vetor[setaD] = vetor[i];
            vetor[i] = copia;
        }
        return setaD;
    }
   
    vetor[i] = vetor[p]; //a partir desse momento o que esta na posição vetor[p] não é mais o pivô
    vetor[p] = copia; //por isso vou passar a referir o pivô como vetor[i]
   
    bool teste = true;
    
    //enquanto seta esq. menor ou igual a seta dir. e seta esq. menor que fim
    while(setaE <= setaD && setaE < f){
        if(vetor[setaE] > vetor[i]){ //seta esq. aponta para um valor maior que o pivô, procure um valor menor
            //enquanto as condiçoes forem verdadeiras, tais: seta dir. maior ou igual seta esq. e seta dir maior que inicio
            while(teste){
                if(setaD >= setaE && setaD > i){
                    if(vetor[setaD] <= vetor[i]){ //seta dir. aponta para um valor menor que o pivô, troca os valores das setas
                        copia = vetor[setaD];
                        vetor[setaD] = vetor[setaE];
                        vetor[setaE] = copia;
                        teste = false;
                    }
                    setaD = setaD - 1;
                } else{ 
                    teste = false;
                }
            }
            teste = true;
        }
        setaE = setaE + 1;
    } //vale lembrar que seta esq. maior que seta dir. (e vice versa) implica que elas se cruzaram
    copia = vetor[setaD]; //pega e copia o último menor ou igual ao pivô
    vetor[setaD] = vetor[i];
    vetor[i] = copia;
    return setaD; //retorna a posição do pivô
}

template <typename T>
//particiona o vetor e chama recursivamente particionando o vetor até fica em ordem crescente
void quicksort(T *vetor, int inicio, int fim){
    if(inicio > fim){
        return;
    }
    int part;
    if(inicio < fim){
        int p = pivo(inicio, fim);
        part = particionar(&vetor[0], inicio, p, fim);
        quicksort(&vetor[0], inicio, part-1); //particiona para o lado esquerdo
        quicksort(&vetor[0], part+1, fim); //particiona para o lado direito
    } else if(inicio > fim && fim > 0){
        int p = pivo(fim, inicio);
        part = particionar(&vetor[0], fim, p, inicio);
    }
}

template <typename T>
//particiona o vetor e chama recursivamente particionando o vetor até fica em ordem crescente
void quicksort_ale(T *vetor, int inicio, int fim){
    if(inicio > fim){
        return;
    }
    int part;
    if(inicio < fim){
        int p = pivo(inicio, fim);
        part = particionar(&vetor[0], inicio, p, fim);
        quicksort(&vetor[0], inicio, part-1); //particiona para o lado esquerdo
        quicksort(&vetor[0], part+1, fim); //particiona para o lado direito
    } else if(inicio > fim && fim > 0){
        int p = pivo_ale(fim, inicio);
        part = particionar(&vetor[0], fim, p, inicio);
    }
}

template <typename T>
//utiliza o quicksort e passa para o heapsort quando chegar no limite do quicksort
void intro_rec(T *vetor, int i, int f, int nv_rest){
    if(i == f){ //Caso base: 1 elemento para ordenar
        return;
    }
    if(nv_rest < 1){ //Ainda tem níveis para descer? Caso contrario, trocar para o heapsort
        heapsort<int>(&vetor[0], f);
    } else { //ainda tem níveis para descer, então agir como quicksort
        if(i < f){
            int p = pivo(i, f);
            int part = particionar(&vetor[0], i, p, f);
            
            intro_rec(&vetor[0], i, part-1, nv_rest-1);
            intro_rec(&vetor[0], part+1, f, nv_rest-1);
        } else if(i > f && f > 0){
            int p = pivo(f, i);
            particionar(&vetor[0], f, p, i);
        } 
    }
}

template <typename T>
//
void insertionsort(T *vetor, int n){
    T copia;
    int w;
    for(int i = 1; i <= n; ++i){
        w = i - 1;
        if(vetor[i] < vetor[w]){ //se vetor[i] < vetor[w] procurar um lugar para adicionar ele
            copia = vetor[i]; //guardar o valor do vetor[i]
            while(w >= 0 && vetor[w] > copia){ //enquanto houver elementos maior que copia passar eles para frente
                vetor[w+1] = vetor[w];
                w = w - 1;
            }
            vetor[w+1] = copia; //w+1 é a posição "vazia" que é o lugar para guardar copia
        }
    }
}

template <typename T>
//Introsort com o insertionsort
void intro_rec_insert(T *vetor, int i, int f, int nv_rest){
    if(i == f){ //Caso base: 1 elemento para ordenar
        return;
    }
    if(nv_rest < 16){ //para instacias pequenas chamar o insertionsort
        insertionsort(vetor, f);
    } else if(nv_rest < 1){ //Ainda tem níveis para descer? Caso contrario, trocar para o heapsort
        heapsort<int>(vetor, f);
    } else { //ainda tem níveis para descer, então agir como quicksort
        if(i < f){
            int p = pivo(i, f);
            int part = particionar(vetor, i, p, f);
            
            intro_rec(vetor, i, part-1, nv_rest-1);
            intro_rec(vetor, part+1, f, nv_rest-1);
        } else if(i > f && f > 0){
            int p = pivo(f, i);
            particionar(vetor, f, p, i);
        } 
    }
}    

template <typename T>
//calcula 2log(n) e passa como argumento para a função recursiva do introsort
void introsort(T *vetor, int n){
    int nv_rest = n;
    int j = 0;
    while(nv_rest > 1){
        nv_rest = (nv_rest >> 1); //deslocar um bit a direita
        j = j + 1;
    }
    nv_rest = 2*j;
    intro_rec(vetor, 0, n, nv_rest);
}

template <typename T>
//Função para determinar os tipos das instancias que serão geradas
void gerar_instancias(T *vetor, char tipo, int tam){
    random_device dar_semente; mt19937 gerador( dar_semente() );
    int n, min = 0, max = 10000;
    uniform_int_distribution<T> distribuicao(min,max);
    switch (tipo) {
    case 'A': //aleatória
        for (int i = 0; i < tam; ++i){
            vetor[i] = distribuicao(gerador);
        }
        break;
    case 'C': // ordem crescente
        n = distribuicao(gerador);
        for(int i = 0; i < tam; ++i){
            vetor[i] = n+1;
            n = n + 1;
        }
        break;
    case 'D': // ordem descrescente
        n = distribuicao(gerador);
        for(int i = 0; i < tam; ++i){
            vetor[i] = n-1;
            n = n - 1;
        }
        break;
    case 'P': //pior caso
        for(int i = 0; i < tam; ++i){
            vetor[i] = 0;
        }
        break;
    default:
        break;
    }
}

template <typename T>
void calc_tempo(int tam, int n_inst, char tipo, double *tempo){
    //indice 0: heap, indice 1: quick, indice 2: quick_pivoA, indice 3: intro, indice 4: intro_ins
    for(int i = 1; i <= n_inst; ++i){
        
        T *vetor1 = new(nothrow) int[tam]; if(vetor1 == nullptr) return;
        T *vetor2 = new(nothrow) int[tam]; if(vetor2 == nullptr) return;
        T *vetor3 = new(nothrow) int[tam]; if(vetor3 == nullptr) return; 
        T *vetor4 = new(nothrow) int[tam]; if(vetor4 == nullptr) return; 
        T *vetor5 = new(nothrow) int[tam]; if(vetor5 == nullptr) return; 
        gerar_instancias(vetor1, tipo, tam);
        gerar_instancias(vetor2, tipo, tam);
        gerar_instancias(vetor3, tipo, tam);
        gerar_instancias(vetor4, tipo, tam);
        gerar_instancias(vetor5, tipo, tam);

        auto i1 = steady_clock::now();
        heapsort(vetor1, tam);
        auto f1 = steady_clock::now(); duration<double> tempo_heapsort = f1-i1;
        tempo[0] = tempo[0] + tempo_heapsort.count();
        cout << i;

        auto i2 = steady_clock::now();
        quicksort(vetor2, 0, tam);
        auto f2 = steady_clock::now(); duration<double> tempo_quick = f2-i2;
        tempo[1] = tempo[1] + tempo_quick.count();

        auto i3 = steady_clock::now();
        quicksort_ale(vetor3, 0, tam);
        auto f3 = steady_clock::now(); duration<double> tempo_quick_a = f3-i3;
        tempo[2] = tempo[2] + tempo_quick_a.count();

        auto i4 = steady_clock::now();
        introsort(vetor4, tam);
        auto f4 = steady_clock::now(); duration<double> tempo_intro = f4-i4;
        tempo[3] = tempo[3] + tempo_intro.count();

        int nv_rest = tam;
        int j = 0;
        while(nv_rest > 1){
            nv_rest = (nv_rest >> 1); //deslocar um bit a direita
            j = j + 1;
        }
        auto i5 = steady_clock::now();
        intro_rec_insert(vetor5, 0, tam, j);
        auto f5 = steady_clock::now(); duration<double> tempo_intro_in = f5-i5;
        tempo[4] = tempo[4] + tempo_intro_in.count();

        delete[] vetor1;
        delete[] vetor2;
        delete[] vetor3;
        delete[] vetor4;
        delete[] vetor5;
    }
}

int main(){
    int tam, n_inst;
    char tipo;

    cout << "Tipo da instancia: "; cin >> tipo;
    cout << "Tamanho da instancia: "; cin >> tam;
    cout << "Numero de instacias: "; cin >> n_inst;

    double tempo[5] = {0.0, 0.0, 0.0, 0.0, 0.0}; //vetor com os tempos dos algoritmos:

    calc_tempo<int>(tam-1, n_inst, tipo, tempo);
 
    cout << "tempo Heapsort: " << tempo[0] << '\n';
    cout << "tempo Quicksort(pivo fixo): " << tempo[1] << '\n';
    cout << "tempo Quicksort(pivo aleatorio): " << tempo[2] << '\n';
    cout << "tempo Introsort sem insert: " << tempo[3] << '\n';
    cout << "tempo Introsort com insert: " << tempo[4] << '\n';
}