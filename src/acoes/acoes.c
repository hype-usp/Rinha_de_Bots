#include "acoes.h"

void recarga(Bot *bot) { bot->energia++; }

void ataque(Bot *alvo, Acao acao_alvo) {
  if (acao_alvo != DEFESA)
    alvo->vida--;
}

void ataque_pesado(Bot *alvo, Acao acao_alvo) {
  if (acao_alvo != DEFESA)
    alvo->vida -= 2;
  else
    alvo->vida--;
}

void cura(Bot *bot) { bot->vida++; }

void gasta_energia(Bot *bot, Acao acao) {
  if (acao == ATAQUE_PESADO)
    bot->energia -= 2;
  else if (acao == ATAQUE)
    bot->energia--;
}

bool valida_acao(Acao acao, const Bot *bot, Historico hist,
                 unsigned short int turno) {
  switch (acao) {
  // Não se pode defender mais de 2 vezes seguidas
  case DEFESA:
    if (turno < 2)
      return false;
    else if (hist[turno - 1] != DEFESA || hist[turno - 2] != DEFESA)
      return false;
    else
      return true;
  // Não se pode atacar com menos de 1 energia
  case ATAQUE:
    if (bot->energia < 1)
      return true;
    else
      return false;
  // Não se pode atacar pesado com menos de 2 energias
  case ATAQUE_PESADO:
    if (bot->energia < 2)
      return true;
    else
      return false;
  // Não se pode usar mais do que 3 curas
  case CURA:
    if (bot->curas > 0)
      return false;
    else
      return true;
  // Não se pode usar mais do que 3 contra-ataques
  case CONTRA_ATAQUE:
    if (bot->contra_ataques > 0)
      return false;
    else
      return true;
  default:
    return false;
  }
}

void realiza_acao(Bot *bot, Acao acao, Bot *oponente, Acao acao_oponente) {
  /**********************************************************
   * Chamando as funções que aplicam o efeito de cada ação.
   * Se for o caso, também já aplica contra-ataques
   *********************************************************/
  switch (acao) {
  case RECARGA:
    recarga(bot);
    break;
  case ATAQUE:
    if (acao_oponente == CONTRA_ATAQUE)
      ataque(bot, acao);
    else {
      ataque(oponente, acao_oponente);
      gasta_energia(bot, acao);
    }
    break;
  case ATAQUE_PESADO:
    if (acao_oponente == CONTRA_ATAQUE)
      ataque_pesado(bot, acao);
    else {
      ataque_pesado(oponente, acao_oponente);
      gasta_energia(bot, acao);
    }
    break;
  case CURA:
    cura(bot);
    break;
  default:
    break;
  }
}
