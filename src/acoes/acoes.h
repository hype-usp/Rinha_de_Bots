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

// Gasta a quantidade de energia de um bot correspondente à sua ação
void gasta_energia(Bot *bot, Acao acao);

/**************************************************************
 * Valida a ação de um bot para que ela corresponda com as
 * regras do jogo:
 * - não se pode defender mais do que duas vezes seguidas
 * - não se pode curar mais do que 3 vezes
 * - não se pode contra-atacar mais do que 3 vezes
 * - não se pode atacar sem 1 energia
 * - não se pode atacar pesado sem 2 energias
 * Retorna true se alguma regra tiver sido violada
 *************************************************************/
bool valida_acao(Acao acao, const Bot *bot, Historico hist, unsigned short int turno);

#endif