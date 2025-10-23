#include "../acoes/acoes.h"
#include "bots.h"
#include <stdlib.h>
int fibo(int n) {
  if (n <= 1)
    return n;
  int *dp = (int *)malloc((n + 1) * sizeof(int));
  if (!dp)
    return -1; // Allocation failed
  dp[0] = 0;
  dp[1] = 1;
  for (int i = 2; i <= n; i++)
    dp[i] = dp[i - 1] + dp[i - 2];
  int result = dp[n];
  free(dp);
  return result;
}
static Acao tomar_decisao(const Bot *bot, const Bot *oponente,
                          Historico hist_bot, Historico hist_oponente,
                          unsigned short int turno) {
  int cargaBombing = 0;
  for (int x = turno - 1; x >= 0; x--) {
    if (hist_oponente[x] == RECARGA)
      cargaBombing++;
    else
      break;
  }
  if (oponente->energia >= 3)
    if (bot->contra_ataques > 0)
      return CONTRA_ATAQUE;

  if (bot->energia == 0)
    return RECARGA;

  if (cargaBombing >= 4) {
    if (bot->energia >= 2)
      return ATAQUE_PESADO;
    if (bot->energia == 1)
      return ATAQUE;
  }

  if (bot->vida < 3) {
    if (bot->vida == 1 && oponente->energia > 1)
      if (bot->contra_ataques > 0)
        return CONTRA_ATAQUE;
    if (bot->curas > 0)
      return CURA;
  }

  if (oponente->energia == 2)
    if (bot->contra_ataques > 0)
      return CONTRA_ATAQUE;
  if (turno >= 2 && hist_oponente[turno - 1] == DEFESA &&
      hist_oponente[turno - 2] == DEFESA) {
    if (bot->energia > 1)
      return ATAQUE_PESADO;
    else if (bot->energia > 0)
      return ATAQUE;
  }
  if (oponente->vida == 1)
    if (bot->energia > 0)
      return ATAQUE;

  if (oponente->energia > 0) {
    if (valida_acao(DEFESA, bot, hist_bot, turno))
      return DEFESA;
    if (valida_acao(ATAQUE, bot, hist_bot, turno) &&
        oponente->contra_ataques < 1)
      return ATAQUE;
  }

  if (oponente->vida > 0) {
    if (bot->energia == 1)
      return ATAQUE;
    else if (bot->energia > 1)
      return ATAQUE_PESADO;
    else
      return RECARGA;
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
  inicializa_bot(&bot, "Geladeira SImples", "Raphael Augusto",
                 (FuncaoDecisao)&tomar_decisao);
}
