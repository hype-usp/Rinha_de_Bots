#include "jogo.h"
#include "../tipos.h"
#include "../estatisticas/estatisticas.h"

Estatistica inicia_simulacao(const Bot **bots, size_t num_bots) {
	Estatistica estatisticas;
	inicializa_estatistica(&estatisticas);

	/**********************************************************
	 * Loop externo: b1 é o ID do primeiro bot no combate.
	 * b1 varia de 0 a num_bots
	 *********************************************************/
	for(int b1 = 0; b1 < num_bots; b1++) {
		/******************************************************
		 * Loop interno: b2 é o ID do segundo bot no combate,
		 * depende de b1 para não parearmos os mesmos bots duas
		 * vezes. Por exemplo, não queremos dois combates como:
		 * bot12 x bot15 E bot15 x bot12
		 * pois os dois são idênticos
		 *****************************************************/
		for(int b2 = b1 + 1; b2 < num_bots; b2++) {
			BotID resultado_combate;
			resultado_combate = simula_combate(bots[b1], bots[b2]);
		}
	}
}

BotID simula_combate(Bot *bot1, Bot *bot2) {
	/**********************************************************
	 * O saldo resultante acabará:
	 * positivo se o bot 1 vencer
	 * negativo se o bot 1 perder
	 * igual a 0 se os bots empatarem
	 *********************************************************/
	short int saldo_resultante = 0;
	for(int turno = 1; turno <= CONFRONTOS_POR_COMBATE; turno++) {
		// o resultado pode ser o ID do bot1, o ID do bot2 ou EMPATE
		BotID resultado_confronto;
		resultado_confronto = simula_confronto(bot1, bot2);
		if(resultado_confronto == bot1->id) saldo_resultante++;
		if(resultado_confronto == bot2->id) saldo_resultante--;
	}
	if(saldo_resultante > 0) return bot1->id;
	if(saldo_resultante < 0) return bot2->id;
	return EMPATE;
}

BotID simula_confronto(Bot *bot1, Bot *bot2) {
	EstadoConfronto estado_confronto;
	while((estado_confronto = simula_turno(bot1, bot2)) == INACABADO) {}
	if(estado_confronto == BOT1_VENCEU) return bot1->id;
	if(estado_confronto == BOT2_VENCEU) return bot2->id;
	return EMPATE;
}

EstadoConfronto simula_turno(Bot *bot1, Bot *bot2) {
	// To-do: implementar
}