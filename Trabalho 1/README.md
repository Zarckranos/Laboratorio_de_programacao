## Implementação de algoritmos de Ordenação em C++:
1. Heapsort
2. Quicksort com Pivô Fixo
3. Quicksort com Pivô Aleatório
4. Introsort sem Insertion Sort
5. Introsort com Insertion Sort 

## O Trabalho também deve gera algumas instâncias:
1. Aleatorias
2. Pior Caso 
3. Ordem Crescente
4. Ordem Decrescente

>Também deve ter uma função para aferir o tempo de ordenação de um dado vetor por um dado algoritmo.
>É importante que a contagem de tempo realizada pela função seja relativa apenas ao tempo efetivamente
>gasto na ordenação, não incluindo o tempo gasto em procedimentos auxiliares.

## Compilação e execução do programa:
`g++ -Wall -Wextra -std=c++17 -pedantic -o programa main.cpp`

### Durante a execução deve ser passado argumentos:
1. **Tipo de instância:** A (aleatoria), C (ordem crescente), D(ordem decrescente) ou P (pior caso).
2. **Tamanho do vetor:** número natural positivo informando o tamanho das instâncias a serem geradas 
   pelo programa.
3. **Número de instâncias:** também será um número natural positivo e informará o número de instâncias a
   serem geradas e ordenadas por cada algoritmo implementado.

## Comentario do Professor a respeito da minha solução:
>Nota: 8,2 Heapsort executando em tempo O(n²). Introsort para "i > f"? Idem para quicksort. Condição errada para chamada do insertionsort no introsort. Instâncias de pior caso todas zeradas, e não construídas conforme o enunciado. Não confere se os vetores estão ordenados. Uso errado do gerador de aleatórios de C++, repetindo criação do gerador (deveria criar só uma vez).
