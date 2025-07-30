#ifndef JOGO_H
#define JOGO_H

#include <stddef.h>
#include <stdbool.h>
#include "../tipos.h"
#include "../bots/bots.h"
#include "../estatisticas/estatisticas.h"

#define CONFRONTOS_POR_COMBATE 100
#define EMPATE 255 // Um número alto que não será ID de um bot para representar empates

/**************************************************************
 * Função que roda o loop principal da simulação, recebe apenas
 * a lista de bots e o número de bots como argumento, pois
 * nenhum contexto adicional é necessário
 *************************************************************/ 
Estatistica inicia_simulacao(Bot **bots, size_t num_bots);

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
ResultadoTurno simula_turno(Bot *bot1, Bot *bot2, Historico hist_bot1, Historico hist_bot2, unsigned short int num_turno);

/**************************************************************
 * Nos retorna o estado de um confronto após um turno, o que
 * efetivamente equivale a checar quais bots morreram ou não
 *************************************************************/
EstadoConfronto estado_confronto(short int vida_bot1, short int vida_bot2);

/**************************************************************
 * Processa o resultado de um combate alterando os atributos de
 * estatística de cada bot envolvido. Ou seja, atualizando o
 * os VDEs dos dois bots de acordo com o resultado
 *************************************************************/
void processa_resultado_combate(BotID resultado, Bot *bot1, Bot *bot2);

/**************************************************************
 * Processa o resultado de um confronto alterando os atributos
 * de estatística de cada bot envolvido. Ou seja, atualizando o
 * os KDs dos dois bots de acordo com o resultado
 *************************************************************/
void processa_resultado_confronto(BotID resultado, Bot *bot1, Bot *bot2);

/**************************************************************
 * Processa as ações de um turno alterando os atributos de
 * estatística de cada bot envolvido, como o número de
 * decisões, o número de boas defesas, etc.
 *************************************************************/
void processa_turno(Bot *bot1, Acao acao_bot1, Bot *bot2, Acao acao_bot2);

#endif