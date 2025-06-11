#ifndef ACOES_H
#define ACOES_H

#include "../tipos.h"
#include "../bots/bots.h"

// Recarrega 1 energia de um bot
void recarga(Bot *bot);

// Causa 1 de dano ao alvo. Assume que o caso de contra-ataque já foi tratado
void ataque(Bot *alvo, Acao acao_alvo);

// Causa 3 de dano ao alvo. Assume que o caso de contra-ataque já foi tratado
void ataque_pesado(Bot *alvo, Acao acao_alvo);

// Recupera 1 de vida de um bot
void cura(Bot *bot);

#endif