#include "bots.h"

static Acao tomar_decisao(const Bot *bot, const Bot *oponente,
                          Historico hist_bot, Historico hist_oponente,
                          unsigned short int turno) {
  if (turno < 4)
    return RECARGA;
  if (bot->vida <= 2) {
    if (oponente->energia >= 1 && bot->contra_ataques > 0) {
      return CONTRA_ATAQUE;
    }
    if (oponente->energia == 1 && bot->curas == 0) {
      return DEFESA;
    }
    if (bot->curas > 0) {
      return CURA;
    }
  }
  if (bot->energia >= 2) {
    return ATAQUE_PESADO;
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
  inicializa_bot(&bot, "Bombot", "Forkbomb", (FuncaoDecisao)&tomar_decisao);
}
