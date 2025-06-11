#include <stdio.h>
#include <stdlib.h>
#include "bots/bots.h"
#include "jogo/jogo.h"

/**************************************************************
 * Compilação - rode o comando:
 * $ make
 * 
 * Execução - rode o comando:
 * $ make run
 *************************************************************/

// Declara os símbolos de início e fim da seção "bots" que o linker irá criar.
extern Bot __start_bots;
extern Bot __stop_bots;

int compara_bots_por_id(const void* a, const void* b) {
    Bot* botA = *(Bot**)a;
    Bot* botB = *(Bot**)b;
    return (botA->id - botB->id);
}

int main(int argc, char** argv) {
    // Calcula quantos bots foram registrados na seção.
    const size_t num_bots = (size_t)(&__stop_bots - &__start_bots);
    
    // Cria nossa lista de ponteiros para os bots.
    Bot *lista_de_bots[num_bots];

    // Itera pelos bots na seção de memória e preenche a lista.
    for (size_t i = 0; i < num_bots; ++i) {
        lista_de_bots[i] = &__start_bots + i;
    }
    printf("\nTotal de %zu bots prontos para a rinha!\n", num_bots);

    qsort(lista_de_bots, num_bots, sizeof(Bot*), compara_bots_por_id);

    inicia_simulacao(lista_de_bots, num_bots);

    return 0;
}