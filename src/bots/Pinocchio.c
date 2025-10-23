#include "../acoes/acoes.h"
#include "bots.h"

/**************************************************************
 * Pinocchio
 * Estratégias:
 * - Condições de vitória imediata (finalizar oponente)
 * - Previsão de ação do oponente com base em energia e padrão
 * - Gerenciamento otimizado de energia, cura e contra-ataque
 * - Uso estratégico de defesa contra ataques esperados
 *************************************************************/
// Conta ocorrências da ação nos últimos N turnos
static int count_recent_actions(const Historico hist, unsigned short int turno,
                                Acao action, int N) {
  int count = 0;
  int start = (turno >= N) ? turno - N : 0;
  for (int i = start; i < turno && i < MAX_TURNOS; i++) {
    if (hist[i] == action)
      count++;
  }
  return count;
}

// Prediz a próxima ação provável do oponente
static Acao predict_opponent_action(const Bot *oponente,
                                    const Historico hist_oponente,
                                    unsigned short int turno) {
  // Prioriza ataque pesado se possível
  if (oponente->energia >= 2)
    return ATAQUE_PESADO;
  // Ataque normal se tiver energia
  if (oponente->energia >= 1)
    return ATAQUE;
  // Se recarregou no último turno, pode atacar agora
  if (turno > 0 && hist_oponente[turno - 1] == RECARGA)
    return ATAQUE;
  // Caso contrário, recarrega
  return RECARGA;
}

static Acao tomar_decisao(const Bot *bot, const Bot *oponente,
                          Historico hist_bot, Historico hist_oponente,
                          unsigned short int turno) {
  if (oponente->vida <= 1 && bot->energia >= 1 &&
      !valida_acao(ATAQUE, bot, hist_bot, turno)) {
    return ATAQUE;
  }
  if (oponente->vida <= 2 && bot->energia >= 2 &&
      !valida_acao(ATAQUE_PESADO, bot, hist_bot, turno)) {
    return ATAQUE_PESADO;
  }

  if (bot->vida <= 1 && bot->curas > 0) {
    Acao pred = predict_opponent_action(oponente, hist_oponente, turno);
    if ((pred == ATAQUE || pred == ATAQUE_PESADO) &&
        !valida_acao(CURA, bot, hist_bot, turno)) {
      return CURA;
    }
  }

  if (bot->contra_ataques > 0) {
    Acao pred = predict_opponent_action(oponente, hist_oponente, turno);
    if ((pred == ATAQUE || pred == ATAQUE_PESADO) &&
        !valida_acao(CONTRA_ATAQUE, bot, hist_bot, turno)) {
      return CONTRA_ATAQUE;
    }
  }

  Acao pred = predict_opponent_action(oponente, hist_oponente, turno);
  if ((pred == ATAQUE || pred == ATAQUE_PESADO) && bot->vida <= 2 &&
      !valida_acao(DEFESA, bot, hist_bot, turno)) {
    return DEFESA;
  }

  if (bot->energia >= 2 &&
      count_recent_actions(hist_oponente, turno, DEFESA, 2) == 0 &&
      !valida_acao(ATAQUE_PESADO, bot, hist_bot, turno)) {
    return ATAQUE_PESADO;
  }
  if (bot->energia >= 1 && !valida_acao(ATAQUE, bot, hist_bot, turno)) {
    return ATAQUE;
  }

  if (bot->vida < VIDA_MAX && bot->curas > 0 && oponente->energia == 0 &&
      !valida_acao(CURA, bot, hist_bot, turno)) {
    return CURA;
  }

  if (!valida_acao(RECARGA, bot, hist_bot, turno)) {
    return RECARGA;
  }

  return VACILO;
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
  inicializa_bot(&bot, "Pinocchio", "Caixa Preta",
                 (FuncaoDecisao)&tomar_decisao);
}
