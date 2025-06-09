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

	bot->dano_tomado = 0;
	bot->sucesso_CA = 0;
	bot->sucesso_defesas = 0;
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