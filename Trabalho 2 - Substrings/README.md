## Resumo:
Um programa em C++ que apresente os tempos de execução do algoritmo de busca por subsequências de caracteres (substrings) por **força bruta**
e do algoritmo **Knuth-Morris-Pratt (KMP)** em diferentes tipos de instâncias.

## Compilação e execução do programa:
`g++ -Wall -Wextra -std=c++17 -pedantic -o programa main.cpp`

A entrada do programa será necessariamente informada através dos argumentos fornecidos emsua chamada. O primeiro argumento determinará 
o tipo das instâncias a serem fornecidas aos dois algoritmos. Caso esse argumento seja um A, então as instâncias serão (pseudo)aleatórias
e a chamada terá o formato:
`./programa A [l] [m] [n] [I]`

### Onde:
1. **l** é uma letra de *a* a *z* 
2. **m** é o tamanho do pradrão (neste trabalho, o tamanho de uma string é o seu numero de símbolos, sem contar o '\0')
3. **n** é o tamanho do texto
4. **I** é o número de instâncias a serem fornecidas aos algoritmos

>**m**, **n** e **I** são números naturais positivos (este trabalho não faz exigências sobre o comportamento do programa nos casos em que a 
>chamada não estiver no formato esperado).

## Instâncias aleatórias e de Pior Caso:
Criar a instância aleatória número 1, isto é, criar um padrão e um texto aleatórios, de tamanhos m e n, respectivamente, e contendo letras aleatórias
de *a* a **l** (assim, por exemplo, se **l** for a letra *e*, então o padrão e o texto deverão conter letras aleatórias de *a* a *e*). Em particular,
observe que, caso **l** seja a letra *a*, então o padrão será necessariamente uma sequência de **m** a's e o texto uma sequência de **n** a's, o que 
é justamente uma instância de pior caso para o algoritmo de força bruta.

## Instâncias Reiais:
A chamada do programa para as inst^ancias reais terá a seguinte forma:
`./programa R [x] [y]`

Sendo x e y números naturais tais que 0 <= x <= y <= 35129.
1. Para cada índice i de x a y, o programa fornecerá como entrada para os dois algoritmos a instância real de índice i, composta pelo padrão Padroes_Palavras[i]
e o texto Texto_Livros, sendo Padroes_Palavras e Texto_Livros variáveis definidas no arquivo instancias_Reais_Trabalho_2.hpp, que é fornecido pelo professor (com
base no conteúdo de um livro de domínio público).
2. O tempo total exibido ao final do programa para cada um dos algoritmos será então aquele necessário para resolver as y - x + 1 instâncias reais indexadas de
   x a y, conforme definido no item anterior.
   
## Comentário do professor a respeito da minha solução:
Nota: 8,5. Os testes de instâncias aleatórias levaram a erro de execução.
