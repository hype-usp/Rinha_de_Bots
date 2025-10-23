#include "../acoes/acoes.h"
#include "bots.h"
#include <stdlib.h>

#define MAX_LIFE 3
#define MAX_CA 3

static int contar_acoes(const Historico hist, unsigned short int turno,
                        Acao acao, int window) {
  int count = 0, start = turno - window;
  if (start < 0)
    start = 0;

  for (int i = start; i < turno; i++) {
    if (hist[i] == acao)
      count++;
  }

  return count;
}

static Acao tomar_decisao(const Bot *bot, const Bot *oponente,
                          Historico hist_bot, Historico hist_oponente,
                          unsigned short int turno) {
  if (turno == 0)
    return RECARGA;

  double score;
  int SPAN_ATAQUES = 3;

  int oponenteDefesas = contar_acoes(hist_oponente, turno, DEFESA, 3);
  int oponenteContraAtaques =
      contar_acoes(hist_oponente, turno, CONTRA_ATAQUE, 3);
  int oponenteAtaques =
      contar_acoes(hist_oponente, turno, ATAQUE, SPAN_ATAQUES) +
      contar_acoes(hist_oponente, turno, ATAQUE_PESADO, SPAN_ATAQUES);
  int oponenteRecargas = contar_acoes(hist_oponente, turno, RECARGA, 5);

  int random = rand() % 100;

  // Estágio 1: pouca vida
  if (bot->vida < 3) {
    if (!valida_acao(CURA, bot, hist_bot, turno))
      return CURA;
  }

  // Estágio 2: ofensivo
  if (bot->energia >= 2) {
    int wEnergiaBot = 14;
    int wVidaOponente = 25;
    int wContraAtaquesOponente = -30;
    int wHistContraAtaquesOponente = -20;

    score = 0;

    score += bot->energia * wEnergiaBot;
    score +=
        (MAX_LIFE - oponente->vida + 1) * wVidaOponente * (oponente->vida < 3);
    score += oponente->contra_ataques * wContraAtaquesOponente;
    score += oponenteContraAtaques * wHistContraAtaquesOponente;
    if (oponente->energia == 0)
      score += 20;
    if (oponenteRecargas >= 3)
      score += 30;
    if (oponenteDefesas == 2)
      score *= 1.5;

    if (random < score) {
      if (!valida_acao(ATAQUE_PESADO, bot, hist_bot, turno))
        return ATAQUE_PESADO;
      if (!valida_acao(ATAQUE, bot, hist_bot, turno))
        return ATAQUE;
    }
  }

  // Estágio 3: defensivo
  if (oponente->energia >= 1) {
    int wEnergiaOponente = 25;
    int wVidaOponente = -35;
    int wAtaquesInimigo = 35;

    score = 25;

    score += oponente->energia * wEnergiaOponente * (oponente->energia > 1);
    score += oponenteAtaques * wAtaquesInimigo;
    score += (MAX_LIFE - oponente->vida) * wVidaOponente;
    if (turno == 1)
      score -= 50;

    if (random < score) {
      if (!valida_acao(CONTRA_ATAQUE, bot, hist_bot, turno))
        return CONTRA_ATAQUE;
    }

    score += (oponente->energia == 1) * wEnergiaOponente;

    if (random < score) {
      if (!valida_acao(DEFESA, bot, hist_bot, turno))
        return DEFESA;
    }
  }

  return RECARGA;
}

// Esta é a estrutura do seu bot, não mexa nesta linha
static Bot bot __attribute__((section("bots"), used)); // Apenas declaração

static void __attribute__((constructor)) registrar_bot(void) {
  /**********************************************************
   * Chame esta função substituindo o segundo e o terceiro
   * argumentos pelo nome do seu bot e o nome de sua equipe,
   * respectivamente. Por exemplo:
   * inicializa_bot(&bot, "Crododilo Bombardilo", "Hype - Eventos",
   *(FuncaoDecisao)&tomar_decisao); Exceto por isso, não mexa nesta linha.
   *********************************************************/
  inicializa_bot(&bot, "Capitão Nascimento", "Tarzan no CS",
                 (FuncaoDecisao)&tomar_decisao);
}
