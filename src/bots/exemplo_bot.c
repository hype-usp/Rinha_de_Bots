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
static Acao tomar_decisao(Bot bot, Historico hist_proprio, Historico hist_oponente, int turno) {
	printf("Bot \"%s\" tomando decisao;\n", bot.nome);
	if(turno % 2) return RECARGA;
	else return ATAQUE;
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
    inicializa_bot(&bot, "Pistoleiro Maluco", "Hype - Eventos", (FuncaoDecisao)&tomar_decisao);
}

