#include <stdio.h>
#include "bots.h"

unsigned short int id_atual = 0;

void inicializa_bot(Bot *bot, const char *nome, const char *equipe, FuncaoDecisao f) {
	bot->id = id_atual++;
	snprintf(bot->nome, sizeof(bot->nome), "%s", nome);
	snprintf(bot->equipe, sizeof(bot->equipe), "%s", equipe);
	bot->vida = VIDA_MAX,
	bot->energia = ENERGIA_INICIAL,
	bot->curas = NUM_CURAS,
	bot->contra_ataques = NUM_CONTRA_ATAQUES,
	bot->tomar_decisao = f;

	for(int i = 0; i < NUM_BOTS; i++) {
		bot->KDs[i].abates = 0;
		bot->KDs[i].mortes = 0;
		bot->VDEs[i].vitorias = 0;
		bot->VDEs[i].derrotas = 0;
		bot->VDEs[i].empates = 0;

		if(i < NUM_ACOES)
			bot->num_acoes[i] = 0;
	}

	bot->dano_tomado = 0;
	bot->bons_contra_ataques = 0;
	bot->boas_defesas = 0;
	bot->decisoes_tomadas = 0;
	bot->tempo_decisao = 0.0;	
}

bool restaura_bot(Bot *bot) {
	if(bot == NULL) return true;
	
	bot->vida = VIDA_MAX;
	bot->energia = ENERGIA_INICIAL;
	bot->curas = NUM_CURAS;
	bot->contra_ataques = NUM_CONTRA_ATAQUES;
	
	return false;
}

void processa_acao(Bot *bot, Acao acao, Acao acao_oponente) {
	bot->num_acoes[acao]++;
	bot->decisoes_tomadas++;

	if(acao_oponente == ATAQUE) {
		if(acao != DEFESA && acao != CONTRA_ATAQUE)
			bot->dano_tomado += 1;
	} else if(acao_oponente == ATAQUE_PESADO) {
		if(acao == DEFESA) bot->dano_tomado += 1;
		else if(acao != CONTRA_ATAQUE) bot->dano_tomado += 3;
	}

	if(acao_oponente == ATAQUE || acao_oponente == ATAQUE_PESADO) {
		if(acao == CONTRA_ATAQUE)
			bot->bons_contra_ataques++;
		if(acao == DEFESA)
			bot->boas_defesas++;
	}
}

void exibe_bots_stats(Bot **bots, size_t num_bots) {
		printf("\n");
	for(size_t i = 0; i < num_bots; i++) {
		printf("--------- Estatísticas do %s -----------\n", bots[i]->nome);
		printf("dano tomado: %d\n", bots[i]->dano_tomado);
		printf("bons contra-ataques: %d\n", bots[i]->bons_contra_ataques);
		printf("boas defesas: %d\n", bots[i]->boas_defesas);
		printf("decisoes tomadas: %d\n", bots[i]->decisoes_tomadas);
		for(size_t j = 0; j < num_bots; j++) {
			if(i == j) continue;
			printf("KD contra %s: %d/%d\n", bots[j]->nome, bots[i]->KDs[j].abates, bots[i]->KDs[j].mortes);
			printf("VDE contra %s: %d/%d/%d\n", bots[j]->nome, bots[i]->VDEs[j].vitorias, bots[i]->VDEs[j].derrotas, bots[i]->VDEs[j].empates);
		}
	}
}