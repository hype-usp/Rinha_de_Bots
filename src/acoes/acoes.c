#include <stdio.h>
#include "acoes.h"

void recarga(Bot *bot) {
	printf("Bot %d recarrega\n", bot->id);
	bot->energia++;
}

void ataque(Bot *alvo, Acao acao_alvo) {
	printf("Bot %d é atacado\n", alvo->id);
	if(acao_alvo != DEFESA) alvo->vida--;
}

void ataque_pesado(Bot *alvo, Acao acao_alvo) {
	printf("Bot %d é atacado pesado\n", alvo->id);
	if(acao_alvo != DEFESA) alvo->vida -= 3;
	else alvo->vida--;
}

void cura(Bot *bot) {
	printf("Bot %d se cura\n", bot->id);
	bot->vida++;
}
