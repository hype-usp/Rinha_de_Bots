#ifndef JOGO_H
#define JOGO_H

#include "../bots/bots.h"

#define CONFRONTOS_POR_COMBATE 100
#define EMPATE 255 // Um número alto que não será ID de um bot para representar empates

/**************************************************************
 * Função que roda o loop principal da simulação, recebe apenas
 * a lista de bots e o número de bots como argumento, pois
 * nenhum contexto adicional é necessário
 *************************************************************/ 
Estatistica inicia_simulacao(const Bot **bots, size_t num_bots);

/**************************************************************
 * Simula um "combate" entre dois bots. Um combate é uma
 * sequência de 100 confrontos. Ao final do combate, o ID do
 * vencedor é retornado
 *************************************************************/
BotID simula_combate(Bot *bot1, Bot *bot2);

/**************************************************************
 * Simula um confronto, que é uma sequência de turnos nos quais
 * cada bot toma sua decisão. Um confronto termina quando um ou
 * ambos os bots chegam a zero de vida. Ao final do confronto,
 * o ID do vencedor é retornado
 *************************************************************/
BotID simula_confronto(Bot *bot1, Bot *bot2);

/**************************************************************
 * Simula um turno de um confronto, que se consiste em uma
 * tomada de decisão por parte de ambos os bots
 *************************************************************/
EstadoConfronto simula_turno(Bot *bot1, Bot *bot2);

#endif