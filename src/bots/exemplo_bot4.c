#include <stdio.h>
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
	// Quantas vezes seguidas o oponente recarregou
	int cargaBombing = 0;
	for (int x = turno - 1; x >= 0; x--){
		if(hist_oponente[x] == RECARGA)
			cargaBombing ++;
		else break;
	}
	// Fluxo de decisão
	if(turno == 0){
		return RECARGA;
	}
	else if(turno == 1){
		return DEFESA;
	}
	else if(bot->vida == 1){
		if(bot->curas > 0) return CURA;
	}
	else if(oponente->energia >= 2){
		if(bot->contra_ataques > 0) return CONTRA_ATAQUE;
	}
	else if(cargaBombing >= 4) {
		if(bot->energia >= 2)
			return ATAQUE_PESADO;
		else
			return RECARGA;
	}
	else if(hist_oponente[turno - 1] == ATAQUE || hist_oponente[turno - 1] == ATAQUE_PESADO) {
		if(bot->energia >= 2)
			return ATAQUE_PESADO;
		else if(bot->energia == 1)
			return ATAQUE;
	}
	return RECARGA;
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
    inicializa_bot(&bot, "Javascript e Maconha", "Sei lá porra", (FuncaoDecisao)&tomar_decisao);
}

