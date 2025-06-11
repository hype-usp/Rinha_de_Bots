#include "jogo.h"
#include "../acoes/acoes.h"

Estatistica inicia_simulacao(Bot **bots, size_t num_bots) {
	//Estatistica estatisticas;
	//inicializa_estatistica(&estatisticas);

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
	ResultadoTurno resultado_turno = {.estado_confronto = INACABADO};
	Historico hist_bot1;
	Historico hist_bot2;
	unsigned short int turno_atual = 0;
	/**********************************************************
	 * Loop que simula os turnos do confronto até que haja
	 * alguma morte ou o confronto chege no número máximo de
	 * turnos
	 *********************************************************/ 
	while(resultado_turno.estado_confronto == INACABADO) {
		resultado_turno = simula_turno(bot1, bot2, hist_bot1, hist_bot2, turno_atual);
		hist_bot1[turno_atual] = resultado_turno.acao_bot1;
		hist_bot2[turno_atual] = resultado_turno.acao_bot2;
		turno_atual++;
	}
	if(resultado_turno.estado_confronto == BOT2_VENCEU) return bot2->id;
	if(resultado_turno.estado_confronto == BOT1_VENCEU) return bot1->id;
	return EMPATE;
}

ResultadoTurno simula_turno(Bot *bot1, Bot *bot2, Historico hist_bot1, Historico hist_bot2, unsigned short int turno) {
	ResultadoTurno resultado_turno;
	// Checando se já passamos do limite máximo de turnos por confronto
	if(turno >= MAX_TURNOS) {
		resultado_turno.estado_confronto = EXCESSO_TURNOS;
		return resultado_turno;
	}
	// Deixando os bots tomarem suas decisões, estas duas lihas são o coração do programa
	Acao acao_bot1 = bot1->tomar_decisao(bot1, hist_bot1, hist_bot2, turno);
	Acao acao_bot2 = bot2->tomar_decisao(bot2, hist_bot2, hist_bot1, turno);
	resultado_turno.acao_bot1 = acao_bot1;
	resultado_turno.acao_bot2 = acao_bot2;
	// Aplicando o efeito correspondente à ação do bot 1
	switch(acao_bot1) {
		case RECARGA:
			recarga(bot1);
			break;
		case ATAQUE:
			if(acao_bot2 == CONTRA_ATAQUE) ataque(bot1, acao_bot1); 
			else ataque(bot2, acao_bot2);
			break;
		case ATAQUE_PESADO:
			if(acao_bot2 == CONTRA_ATAQUE) ataque_pesado(bot1, acao_bot1);
			else ataque_pesado(bot2, acao_bot2);
			break;
		case CURA:
			cura(bot1);
			break;
	}
	// Aplicando o efeito correspondente à ação do bot 2
	switch(acao_bot2) {	
		case RECARGA:
			recarga(bot2);
			break;
		case ATAQUE:
			if(acao_bot1 == CONTRA_ATAQUE) ataque(bot2, acao_bot2); 
			else ataque(bot1, acao_bot1);
			break;
		case ATAQUE_PESADO:
			if(acao_bot1 == CONTRA_ATAQUE) ataque_pesado(bot2, acao_bot2);
			else ataque_pesado(bot1, acao_bot1);
			break;
		case CURA:
			cura(bot1);
			break;
	}
	// Checando as outras condições de término de confronto
	if(bot1->vida <= 0 && bot2->vida <= 0)
		resultado_turno.estado_confronto = AMBOS_MORRERAM;
	else if(bot1->vida <= 0)
		resultado_turno.estado_confronto = BOT2_VENCEU;
	else if(bot2->vida <= 0)
		resultado_turno.estado_confronto = BOT1_VENCEU;
	else
		resultado_turno.estado_confronto = INACABADO;

	return resultado_turno;
}