#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include "tipos.h"
#include "bots/bots.h"
#include "jogo/jogo.h"
#include "estatisticas/estatisticas.h"

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

int main() {
    // Calcula quantos bots foram registrados na seção.
    const size_t num_bots = (size_t)(((char *)&__stop_bots - (char *)&__start_bots) / sizeof(Bot));
    
    // Cria nossa lista de ponteiros para os bots.
    Bot *lista_de_bots[num_bots];

    for (size_t i = 0; i < num_bots; i++) {
        lista_de_bots[i] = (Bot *)((char *)&__start_bots + (i * (sizeof(Bot) + 16)));
    }

    printf("\nTotal de %zu bots prontos para a rinha!\n", num_bots);


    // Ordena os bots da lista para que seus índices correspondam aos seus IDs
    qsort(lista_de_bots, num_bots, sizeof(Bot *), compara_bots_por_id);

    for(int i = 0; i < (int)num_bots; i++) {
        Bot *b = lista_de_bots[i];
        printf("Bot #%d - %s da equipe %s\n", b->id, b->nome, b->equipe);
    }

    // Setando a seed do RNG
    srand(time(NULL));
    // Que o melhor vença!
    Estatistica estatisticas = inicia_simulacao(lista_de_bots, num_bots);
    
    // Mostrando as estatísticas de cada bot
    exibe_bots_stats(lista_de_bots, num_bots);
    
    // Mostrando as estatísticas gerais da rinha
    calcula_t_empates(&estatisticas, lista_de_bots, num_bots);
    calcula_p_boas_defesas(&estatisticas, lista_de_bots, num_bots);
    calcula_p_bons_contra_ataques(&estatisticas, lista_de_bots, num_bots);
    calcula_p_ataques_pesados(&estatisticas, lista_de_bots, num_bots);
    calcula_p_boas_defesas(&estatisticas, lista_de_bots, num_bots);
    calcula_m_num_acoes(&estatisticas, lista_de_bots, num_bots);
    calcula_m_turnos_por_confronto(&estatisticas);
    gerar_relatorio(&estatisticas, num_bots);

    return 0;
}