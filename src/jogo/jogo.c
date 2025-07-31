#include <stdio.h>
#include "jogo.h"
#include "../acoes/acoes.h"
#include "../estatisticas/estatisticas.h"

Estatistica inicia_simulacao(Bot **bots, size_t num_bots) {
	Estatistica estatisticas;
	inicializa_estatisticas(&estatisticas);

	/**********************************************************
	 * Loop externo: b1 é o ID do primeiro bot no combate.
	 * b1 varia de 0 a num_bots
	 *********************************************************/
	for(BotID b1 = 0; b1 < (BotID)num_bots; b1++) {
		/******************************************************
		 * Loop interno: b2 é o ID do segundo bot no combate,
		 * depende de b1 para não parearmos os mesmos bots duas
		 * vezes. Por exemplo, não queremos dois combates como:
		 * bot12 x bot15 E bot15 x bot12
		 * pois os dois são idênticos
		 *****************************************************/
		for(BotID b2 = b1 + 1; b2 < (BotID)num_bots; b2++) {
			incrementa_t_combates(&estatisticas);
			BotID resultado_combate;
			printf("--------------------------------------------\n");
			printf("%s VS %s\n", bots[b1]->nome, bots[b2]->nome);
			resultado_combate = simula_combate(bots[b1], bots[b2], &estatisticas);
			processa_resultado_combate(resultado_combate, bots[b1], bots[b2]);
		}
	}

	return estatisticas;
}

BotID simula_combate(Bot *bot1, Bot *bot2, Estatistica *estatisticas) {
	/**********************************************************
	 * O saldo resultante acabará:
	 * positivo se o bot 1 vencer
	 * negativo se o bot 1 perder
	 * igual a 0 se os bots empatarem
	 *********************************************************/
	short int saldo_resultante = 0;
	for(int confronto = 1; confronto <= CONFRONTOS_POR_COMBATE; confronto++) {
		incrementa_t_confrontos(estatisticas);
		// o resultado pode ser o ID do bot1, o ID do bot2 ou EMPATE
		BotID resultado_confronto;
		resultado_confronto = simula_confronto(bot1, bot2, estatisticas);
		processa_resultado_confronto(resultado_confronto, bot1, bot2);
		if(resultado_confronto == bot1->id) saldo_resultante++;
		if(resultado_confronto == bot2->id) saldo_resultante--;
	}
	if(saldo_resultante > 0) {
		printf("%s VENCEU O COMBATE\n", bot1->nome);
		return bot1->id;
	}
	if(saldo_resultante < 0) {
		printf("%s VENCEU O COMBATE\n", bot2->nome);
		return bot2->id;
	}
	printf("EMPATE\n");
	return EMPATE;
}

BotID simula_confronto(Bot *bot1, Bot *bot2, Estatistica *estatisticas) {
	//iniciando as variáveis de controle do confronto
	ResultadoTurno resultado_turno = {.estado_confronto = INACABADO};
	Historico hist_bot1;
	Historico hist_bot2;
	unsigned short int turno_atual = 0;
	/**********************************************************
	 * Loop que simula os turnos do confronto até que haja
	 * alguma morte ou o confronto chegue no número máximo de
	 * turnos
	 *********************************************************/
	while(resultado_turno.estado_confronto == INACABADO) {
		incrementa_t_turnos(estatisticas);
		resultado_turno = simula_turno(bot1, bot2, hist_bot1, hist_bot2, turno_atual);
		hist_bot1[turno_atual] = resultado_turno.acao_bot1;
		hist_bot2[turno_atual] = resultado_turno.acao_bot2;
		turno_atual++;
	}
	/**********************************************************
	 * Restaurando o estado de cada bot para que eles fiquem
	 * prontos para o próximo confronto
	 *********************************************************/
	restaura_bot(bot1);
	restaura_bot(bot2);
	// Devolvendo o resultado final do confronto
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
	/**********************************************************
	 * Deixando os bots tomarem suas decisões, estas duas
	 * próximas linhas são o coração do programa
	 *********************************************************/
	Acao acao_bot1 = bot1->tomar_decisao(bot1, bot2, hist_bot1, hist_bot2, turno);
	Acao acao_bot2 = bot2->tomar_decisao(bot2, bot1, hist_bot2, hist_bot1, turno);
	/**********************************************************
	 * Validando as ações dos bots para ter certeza de que eles
	 * não trapaceiem (mesmo que sem querer) e armazenando o
	 * resultado.
	 *********************************************************/
	bool acao1_invalida = valida_acao(acao_bot1, bot1, hist_bot1, turno);
	bool acao2_invalida = valida_acao(acao_bot2, bot2, hist_bot2, turno);
	if(acao1_invalida) resultado_turno.acao_bot1 = VACILO;
	else resultado_turno.acao_bot1 = acao_bot1;
	if(acao2_invalida) resultado_turno.acao_bot2 = VACILO;
	else resultado_turno.acao_bot2 = acao_bot2;
	processa_turno(bot1, acao_bot1, bot2, acao_bot2);
	/**********************************************************
	 * Aplicando os efeitos correspondentes às ações de cada
	 * bot, a ordem não é relevante
	 *********************************************************/
	realiza_acao(bot1, acao_bot1, bot2, acao_bot2);
	realiza_acao(bot2, acao_bot2, bot1, acao_bot1);
	/**********************************************************
	 * Checando as condições padrão de término de confronto. O
	 * confronto apenas continua se o resultado for INACABADO
	 *********************************************************/
	resultado_turno.estado_confronto = estado_confronto(bot1->vida, bot2->vida);
	return resultado_turno;
}

EstadoConfronto estado_confronto(short int vida_bot1, short int vida_bot2) {
	if(vida_bot1 <= 0 && vida_bot2 <= 0)
		return AMBOS_MORRERAM;
	else if(vida_bot1 <= 0)
		return BOT2_VENCEU;
	else if(vida_bot2 <= 0)
		return BOT1_VENCEU;
	else
		return INACABADO;
}

void processa_resultado_combate(BotID resultado, Bot *bot1, Bot *bot2) {
	if(resultado == EMPATE) {
		bot1->VDEs[bot2->id].empates++;
		bot2->VDEs[bot1->id].empates++;
	} else if(resultado == bot1->id) {
		bot1->VDEs[bot2->id].vitorias++;
		bot2->VDEs[bot1->id].derrotas++;
	} else {
		bot2->VDEs[bot1->id].vitorias++;
		bot1->VDEs[bot2->id].derrotas++;
	}
}

void processa_resultado_confronto(BotID resultado, Bot *bot1, Bot *bot2) {
	if(resultado == EMPATE) {
		bot1->KDs[bot2->id].mortes++;
		bot2->KDs[bot1->id].mortes++;
	} else if(resultado == bot1->id) {
		bot1->KDs[bot2->id].abates++;
		bot2->KDs[bot1->id].mortes++;
	} else {
		bot2->KDs[bot1->id].abates++;
		bot1->KDs[bot2->id].mortes++;
	}
}

void processa_turno(Bot *bot1, Acao acao_bot1, Bot *bot2, Acao acao_bot2) {
	processa_acao(bot1, acao_bot1, acao_bot2);
	processa_acao(bot2, acao_bot2, acao_bot1);
}