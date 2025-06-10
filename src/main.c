#include <stdio.h>
#include <stdlib.h>
#include "bots/bots.h"
#include "jogo/jogo.h"

/***********************
 * Compilação do código principal:
 * gcc -c src/main.c -o build/main.o
 * gcc -c src/bots/bots.c -o build/bots.o
 *
 * Compilação do código de cada bot participante
 * gcc -c src/bots/exemplo_bot.c -o build/exemplo_bot.o
 * gcc -c src/bots/outro_bot.c -o build/outro_bot.o # E assim por diante...
 *
 * Linkagem de todos os arquivos objeto em um único executável
 * gcc build/*.o -o rinha_de_bots
 *
 * Execução
 * ./rinha_de_bots
******************************************************/

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
        printf("Bot #%zu encontrado: %s da equipe %s\n", i, lista_de_bots[i]->nome, lista_de_bots[i]->equipe);
    }
    printf("\nTotal de %zu bots prontos para a rinha!\n", num_bots);

    qsort(lista_de_bots, num_bots, sizeof(Bot*), compara_bots_por_id);
    printf("\nBots após ordenação por ID:\n");
        for(size_t i = 0; i < num_bots; i++) {
            printf("  ID: %d, Nome: %s\n", lista_de_bots[i]->id, lista_de_bots[i]->nome);
    }

    inicia_simulacao(lista_de_bots, num_bots);

    return 0;
}