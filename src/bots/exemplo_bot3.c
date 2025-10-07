#include "../acoes/acoes.h"
#include "bots.h"
#include <stdlib.h>

/**************************************************************
 * Este é um bot que literalmente não pensa antes de agir,
 * ele gera um número aleatório e toma sua ação com base no
 * número gerado...
 *************************************************************/
static Acao tomar_decisao(const Bot *bot, const Bot *oponente, Historico hist_bot, Historico hist_oponente, unsigned short int turno) {
  int r = rand() % 6;
  if (r == 1) {
    if (!valida_acao(ATAQUE, bot, hist_bot, turno))
      return ATAQUE;
  } else if (r == 2) {
    if (!valida_acao(ATAQUE_PESADO, bot, hist_bot, turno))
      return ATAQUE_PESADO;
  } else if (r == 3) {
    if (!valida_acao(DEFESA, bot, hist_bot, turno))
      return DEFESA;
  } else if (r == 4) {
    if (!valida_acao(CURA, bot, hist_bot, turno))
      return CURA;
  } else if (r == 5) {
    if (!valida_acao(CONTRA_ATAQUE, bot, hist_bot, turno))
      return CONTRA_ATAQUE;
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
  inicializa_bot(&bot, "Tenta Qualquer Coisa", "Jao Bruni",
                 (FuncaoDecisao)&tomar_decisao);
}
