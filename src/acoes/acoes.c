#include <stdio.h>
#include "acoes.h"

void recarga(Bot *bot) {
	bot->energia++;
}

void ataque(Bot *alvo, Acao acao_alvo) {
	if(acao_alvo != DEFESA) alvo->vida--;
}

void ataque_pesado(Bot *alvo, Acao acao_alvo) {
	if(acao_alvo != DEFESA) alvo->vida -= 3;
	else alvo->vida--;
}

void cura(Bot *bot) {
	bot->vida++;
}
