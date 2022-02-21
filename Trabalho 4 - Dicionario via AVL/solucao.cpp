// -----------------------------------------------------------------------------
// Universidade Federal do Ceará, Centro de Ciências, Departamento de Computação
// Disciplina: Laboratório de Programação - CK0215 2021.1 T01A
// Professor: Pablo Mayckon Silva Farias
// Trabalho 4
// Interface para a Implementação de Dicionário baseado em Árvore AVL.
// Autor: Pablo Mayckon Silva Farias, em 18/08/2021.

// Nome: Matheus do Vale Almeida
// -----------------------------------------------------------------------------

#include <new>
using std::nothrow;

#include <iostream>
using std::cout;

template <typename TC, typename TV>
class DicioAVL {
    public: // ------------------------------------------------------------------

    // Representação Interna da Árvore ------------------------------------------

    // Numa implementação típica de dicionário,
    // a representação interna normalmente fica inacessível ao usuário;
    // neste trabalho, porém,
    // o professor precisa avaliar se a árvore está correta,
    // e por isso a estrutura do nó é exposta ao usuário ("public"):

    // Nó ==========================================================================
    struct Noh {
        TC chave;  TV valor;
        Noh *esq, *dir, *pai;
        int altura = 0;

        // Retorna ponteiro para filho direito.
        Noh* obter_dir () { return this->dir; }

        // Retorna ponteiro para o filho esquerdo.
        Noh* obter_esq () { return this->esq; }

        // Retorna ponteiro para o pai.
        Noh* obter_pai () { return this->pai; }

        // Retorna o valor da altura do nó.
        int obter_altura () { 
            if(this == nullptr) return 0;

            return this->altura; 
        }
    }; // ==========================================================================

    // Retorna um ponteiro para a raiz, ou nullptr, se a árvore estiver vazia.
    Noh* obter_raiz () { return raiz; }

    private: // -----------------------------------------------------------------

    // Nó que aponta para a raiz da árvore.
    Noh *raiz;
    
    // Você pode incluir campos e métodos que importem para a implementação
    // mas que fiquem inacessíveis ao usuário da classe DicioAVL ("private").

    public: // ------------------------------------------------------------------

    // Tudo o que está abaixo deve ser mantido público em DicioAVL,
    // pois será utilizado nos testes do professor.

    // Operações de Dicionário: -------------------------------------------------

    //Cria um dicionário vazio.
    DicioAVL () : raiz(nullptr) { }

    // Desaloca o nó passado e seus filhos, caso houver.
    void delete_noh(Noh *noh) {
        if(noh == nullptr) return;

        delete_noh(noh->esq);
        delete_noh(noh->dir);
        delete noh;
    }

    // Desaloca toda a memória dinamicamente alocada pelo dicionário - no caso, basicamente a árvore AVL.
    ~DicioAVL () {
        if(raiz == nullptr) return;

        delete_noh(raiz);
        delete raiz;
    }

    // Iterador =====================================================================
    class Iterador {
        private: // --------------------------------------------------------------
        
        Noh *p;

        public: // ---------------------------------------------------------------

        // Tudo o que está abaixo deve ser mantido público em Iterador,
        // pois será utilizado nos testes do professor.

        // Os operadores "!=" e "==" abaixo podem ser chamados mesmo caso
        // o iterador esteja no "fim" do dicionário ("posição" em que o iterador
        // não se refere a nenhum elemento propriamente dito).
        
        // "p" é inicializado com o argumento pnt.
        Iterador(Noh *pnt) : p(pnt) { }

        // Retorna "true" se e somente se o iterador atual e "j" NÃO SE REFEREM ao mesmo elemento ou posição do dicionário.
        bool operator != (Iterador j) { return p != j.p; }

        // Retorna "true" se e somente se o iterador atual e "j" SE REFEREM ao mesmo elemento ou posição do dicionário.
        bool operator == (Iterador j) { return p == j.p; }

        // Os métodos abaixo possuem como PRÉ-CONDIÇÃO o fato de que o iterador
        // aponta para um elemento propriamente dito do dicionário
        // (será responsabilidade do usuário garantir que esse será o caso,
        // e portanto que os métodos abaixo NÃO SERÃO CHAMADOS caso o iterador
        // aponte para o "fim" do dicionário).
        // Portanto, esses métodos NÃO PRECISAM TESTAR se o iterador aponta
        // para o "fim" do dicionário.

        // Retorna a chave do elemento em questão.
        TC chave () { return p->chave; }

        // Retorna o valor do elemento em questão.
        TV valor () { return p->valor; }

        Noh* esquerdo () { return p->esq; }

        Noh* direito () { return p->dir; }

        Noh* pai () { return p->pai; }

        // Retorna a altura do elemento em questão.
        int altura() { return p->altura; }

        // Faz o iterador passar ao próximo elemento do dicionário (isto é, ao elemento da CHAVE SUCESSORA, na ordem 
        // crescente das chaves), ou então ao "fim" do dicionário, caso não haja um próximo elemento.
        void operator ++ () {
            // Se o nó tem filho direito, fazer:
            if(p->dir != nullptr) {
                // O possível sucessor vira o seu filho direito.
                p = p->dir;

                // Enquanto ele tiver filho esquerdo atribui ele para "p". Ao final vou ter "p" como o sucessor.
                while(p->esq != nullptr) {
                    p = p->esq;
                }
                return;
            
            // Se não tem filho direito, o sucessor vai está subindo a árvore.
            } else{
                // Enquanto a chave de "p" maior que a de seu pai e seu pai não é a raiz da árvore.
                while(p->chave > p->pai->chave && p->pai->pai != nullptr) {
                    p = p->pai;
                }
                // Se a chave de "p" for menor que a chave de seu pai - o sucessor é o nó pai.
                if(p->chave < p->pai->chave) {
                    p = p->pai;
                    return;
                }
                // Se não entrou no último "if" logo "p" não tem sucessor. Então passar ao "fim" do dicionario.
                p = nullptr;
                return;
            }
        }
    }; // ===========================================================================

    // Retorna um iterador para o elemento de menor chave, caso exista um, ou então um iterador para o "fim", se o dicionário estiver vazio.
    Iterador inicio () {
        // Nó para percorrer a árvore.
        Noh* noh = new(nothrow) Noh; if(noh == nullptr) return fim();
        noh = raiz;
        
        // Se raiz vazia, retorna um iterador para o "fim".
        if(noh == nullptr) {
            return fim();
        }

        // Descer até o elemento de menor chave;
        while(noh->esq != nullptr) {
            noh = noh->esq;
        }

        Iterador i(noh);
        return i;
    }

    // Retorna um iterador num estado especial, que seja diferente do estado de um iterador que aponte para um elemento propriamente dito,
    // e que dessa forma sirva para caracterizar a situação em que o iterador tenha atingido o "fim" do dicionário.
    Iterador fim () {
        Iterador i(nullptr);
        return i;
    }

    // Retorna o balanceamento do nó.
    int balanceamento(Noh* noh) {
        if(noh == nullptr) return 0;

        return noh->esq->obter_altura() - noh->dir->obter_altura();
    }

    // Retorna o valor máximo entre as duas alturas.
    int altura_maxima(int h1, int h2) { return (h1 > h2)? h1 : h2; }

    // Rotaciona a árvore a direita e retorna "noh" como a raiz dessa árvore.
    Noh* rotacionar_dir(Noh* noh) {
        // "y" vai receber o nó direto de "noh" e "x" o filho esquerdo de "y".
        Noh* y = noh->esq;
        Noh* x = y->dir;

        // Direito de "y" vai receber "noh" e vai virar a raiz da árvore.
        y->dir = noh;
        y->pai = noh->pai;

        // Esquerdo do "noh" vai receber o filho direito de "y", "x".
        noh->esq = x;
        noh->pai = y;

        // se tem um filho esquerdo então atualiza o pai dele para ele.
        if(noh->esq != nullptr) {
            noh->esq->pai = noh;
        }
        
        // Atualizar alturas
        noh->altura = 1 + altura_maxima(noh->esq->obter_altura(), noh->dir->obter_altura());
        y->altura = 1 + altura_maxima(y->esq->obter_altura(), y->dir->obter_altura());

        return y;
    }
    
    // Rotaciona a árvore a esquerda e retorna "noh" como a raiz dessa árvore.
    Noh* rotacionar_esq(Noh* noh) {   
        // "y" vai receber o nó direto de "noh" e "x" o filho esquerdo de "y".
        Noh* y = noh->dir;
        Noh* x = y->esq;
        
        // Esquerdo de "y" vai receber "noh" e vai virar a raiz da árvore.
        y->esq = noh;
        y->pai = noh->pai;

        // Direito do "noh" vai receber o filho esquerdo de "y", "x".
        noh->dir = x;
        noh->pai = y;

        // se tem um filho direito então atualiza o pai dele para ele.
        if(noh->dir != nullptr) {
            noh->dir->pai = noh;
        }
        
        // Atualizar alturas
        noh->altura = 1 + altura_maxima(noh->esq->obter_altura(), noh->dir->obter_altura());
        y->altura = 1 + altura_maxima(y->esq->obter_altura(), y->dir->obter_altura());

        return y;
    }

    // Função para adicionar o nó na árvore e verificar o balanceamento da árvore.
    // "noh" é o nó a ser adicionado, "pai" é nó pai de "noh" e "r" o nó que corre pela árvore.
    Noh* inserir(Noh* noh, Noh* pai, Noh* r, TC c){
        // Árvore vazia.
        if(r == nullptr) {
            noh->pai = pai;
            noh->altura = 1;
            return noh;
        }
        
        // Anda pela árvore recursivamente para adicionar o nó.
        if(c > r->chave) {
            r->dir = inserir(noh, r, r->dir, c);
        } else {
            r->esq = inserir(noh, r, r->esq, c);
        }

        // Atualiza a altura do nó.
        r->altura = 1 + altura_maxima(r->esq->obter_altura(), r->dir->obter_altura());

        // Calcula o balanceamento da árvore para balancear ela, se necessário.
        int balanco = balanceamento(r);

        // Caso 1 - desbalanceada na esquerda a esquerda da árvore.
        if(balanco > 1 && c < r->esq->chave){ 
            return rotacionar_dir(r); 
        }

        // Caso 2 - desbalanceada na esquerda a direita da árvore.
        if(balanco > 1 && c > r->esq->chave) {
            r->esq = rotacionar_esq(r->esq);
            return rotacionar_dir(r);
        }

        // Caso 3 - desbalanceada na direita a direita da árvore.
        if(balanco < -1 && c > r->dir->chave) {
            return rotacionar_esq(r);
        }
        
        // Caso 4 - desbalanceada na direita a esquerda da árvore.
        if(balanco < -1 && c < r->dir->chave) {
            r->dir = rotacionar_dir(r->dir);
            return rotacionar_esq(r);
        }

        return r;
    }

    /* Insere a chave "c" e o valor "v" no dicionário, partindo da PRÉ-CONDIÇÃO de que a chave "c" não existe no dicionário -- ou seja,
     * a função não precisa nem deve fazer esse teste. 
     * 
     * Em caso de falha de alocação de memória, deve retornar um iterador para o "fim". */
    Iterador inserir (TC c, TV v) {
        //Nó alocado dinamicamente para perdurar.
        Noh* noh = new(nothrow) Noh; if(noh == nullptr) return fim();

        // preenchendo o novo nó
        noh->chave = c; noh->valor = v;
        noh->esq = nullptr; noh->dir = nullptr;

        Iterador i(noh);

        // Caso inicial.
        if(raiz == nullptr) {
            noh->pai = nullptr;
            noh->altura = 1;
            raiz = noh;
            return i;
        }
        
        // Tentei fazer pelo iterador, mas acabei tendo um pouco de dificuldade, então decidi criar mais uma função de inserir

        // Adiciona o nó na árvore e atualiza a raiz.
        raiz = inserir(noh, nullptr, raiz, c);

        return i;
    }

    // Retorna um iterador para o elemento de chave "c", caso essa chave exista no dicionário;
    // Caso a chave não esteja presente, deve ser retornado um iterador para o "fim".
    Iterador buscar (TC c) {
        // O iterador começa na raiz da árvore
        Iterador i(raiz);

        // Enquanto a chave do iterador for diferente de "c" e o iterador não vazio, buscar a chave no dicionário.
        while(i != nullptr && i.chave() != c) {
            // "c" menor que a chave de "i", então buscar no lado esquerdo.
            if(i.chave() > c) {
                i = i.esquerdo();
            } else {
                // buscar no lado direito.
                i = i.direito();
            }
        }

        // Ao final retorna "i", se foi encontrado "c" igual a chave de i temos um iterador para o elemento da chave;
        // Caso a chave ainda seja diferente, veja que "i" será vazio por receber algum filho vazio, então retorna para o "fim".
        return i;
    }

    // Se o iterador apontar para o "fim", então a função deve simplesmente retornar, deixando o dicionário inalterado. Em caso contário,
    // então é PRÉ-CONDIÇÃO da função que o iterador estará apontando para algum elemento do dicionário, o qual deverá ser removido.
    void remover (Iterador i) {

    }

}; // DicioAVL  --------------------------------------------------------------

//int main() { }