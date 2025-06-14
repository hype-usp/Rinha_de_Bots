#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "bots.h"

/**************************************************************
 * Esta é a função que os participantes da Rinha de Bots
 * deverão implementar, ela recebe como argumentos o bot que
 * está tomando a decisão, o histórico de ações do próprio bot,
 * o histórico de ações do oponente e o número do turno atual.
 * 
 * O retorno deve ser uma ação, idealmente derivada de um
 * processo decisório com base nos históricos de ação e no
 * estado atual do bot.
 *************************************************************/
static Acao tomar_decisao(const Bot *bot, const Bot *oponente, Historico hist_bot, Historico hist_oponente, unsigned short int turno) {
	if(oponente->energia >= 3)
		if(bot->contra_ataques > 0)
			return CONTRA_ATAQUE;

	if(bot->energia == 0)
		return RECARGA;

	if(bot->vida < 3)
		if(bot->curas > 0)
			return CURA;

	if(oponente->energia == 2)
		if(bot->contra_ataques > 0)
			return CONTRA_ATAQUE;

	if(oponente->vida == 1)
		return ATAQUE;

	if(oponente->energia == 1)
		return DEFESA;

	if(oponente->vida > 0) {
		if(bot->energia < 2)
			return RECARGA;
		else
			return ATAQUE_PESADO;
	}
}

// Esta é a estrutura do seu bot, não mexa nesta linha
static Bot bot __attribute__((section("bots"), used)); // Apenas declaração

static void __attribute__((constructor)) registrar_bot(void) {
	/**********************************************************
	 * Chame esta função substituindo o segundo e o terceiro
	 * argumentos pelo nome do seu bot e o nome de sua equipe,
	 * respectivamente. Por exemplo:
	 * inicializa_bot(&bot, "Crododilo Bombardilo", "Hype - Eventos", (FuncaoDecisao)&tomar_decisao);
	 * Exceto por isso, não mexa nesta linha.
	 *********************************************************/
    inicializa_bot(&bot, "Genio do Combate", "Ares", (FuncaoDecisao)&tomar_decisao);
}