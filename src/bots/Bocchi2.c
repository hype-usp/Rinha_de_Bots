#include "../acoes/acoes.h"
#include "bots.h"

#define MAX_ENERGIA 10

static int tabela_estatisticas[VIDA_MAX + 1][MAX_ENERGIA + 1][NUM_ACOES] = {
    {{0}}};

// Reconstrói a vida e energia do oponente ao longo do histórico
static void reconstruir_estados(const Historico hist_oponente,
                                const Historico hist_bot,
                                unsigned short int turno, int vidas[],
                                int energias[]) {
  int vida = 3;
  int energia = 0;
  int minha_vida = 3;
  int minha_energia = 0;

  for (int i = 0; i < turno; i++) {
    // Salvar estado do oponente antes da ação
    vidas[i] = vida;
    energias[i] = energia;

    Acao acao_op = hist_oponente[i];
    Acao acao_bot = hist_bot[i];

    // --- Oponente (ação afeta o bot) ---
    switch (acao_op) {
    case RECARGA:
      energia++;
      break;

    case ATAQUE:
      energia--;
      // Se o bot usou DEFESA, bloqueia o dano
      if (acao_bot != DEFESA)
        minha_vida--;
      break;

    case ATAQUE_PESADO:
      energia -= 2;
      // Se o bot usou CONTRA_ATAQUE, reflete 1 de dano
      if (acao_bot == CONTRA_ATAQUE) {
        vida--; // oponente sofre 1 de dano
      } else {
        minha_vida -= 2;
      }
      break;

    case CURA:
      if (vida < 3)
        vida++;
      break;

    case DEFESA:
      // Defesa não afeta diretamente o bot
      break;

    case CONTRA_ATAQUE:
      // Contra-ataque não afeta diretamente o bot
      break;

    default:
      break;
    }

    // --- Bot (nós) — ação afeta o oponente ---
    switch (acao_bot) {
    case ATAQUE:
      minha_energia--;
      // Se o oponente defendeu, bloqueia o dano
      if (acao_op != DEFESA)
        vida--;
      break;

    case ATAQUE_PESADO:
      minha_energia -= 2;
      // Se o oponente usou CONTRA_ATAQUE, reflete 1 de dano
      if (acao_op == CONTRA_ATAQUE) {
        minha_vida--; // bot sofre 1 de dano
      } else {
        vida -= 2;
      }
      break;

    case RECARGA:
      minha_energia++;
      break;

    case CURA:
      if (minha_vida < 3)
        minha_vida++;
      break;

    case DEFESA:
      // Defesa não afeta diretamente o oponente
      break;

    case CONTRA_ATAQUE:
      // Contra-ataque não afeta diretamente o oponente
      break;

    default:
      break;
    }

    // Extremos nos valores
    if (vida < 0)
      vida = 0;
    if (vida > 3)
      vida = 3;
    if (energia < 0)
      energia = 0;
    if (energia > MAX_ENERGIA)
      energia = MAX_ENERGIA;

    if (minha_vida < 0)
      minha_vida = 0;
    if (minha_vida > 3)
      minha_vida = 3;
    if (minha_energia < 0)
      minha_energia = 0;
    if (minha_energia > MAX_ENERGIA)
      minha_energia = MAX_ENERGIA;
  }
}

// Prever a próxima ação do oponente baseado em Bayes simples
static Acao prever_acao_oponente(const Bot *oponente) {
  int vida = oponente->vida;
  int energia = oponente->energia;

  Acao mais_provavel = RECARGA;
  int max = -1;
  for (int a = 0; a < NUM_ACOES; a++) {
    int freq = tabela_estatisticas[vida][energia][a];
    if (freq > max) {
      max = freq;
      mais_provavel = (Acao)a;
    }
  }

  return mais_provavel;
}

static Acao tomar_decisao(const Bot *bot, const Bot *oponente,
                          Historico hist_bot, Historico hist_oponente,
                          unsigned short int turno) {
  for (int i = 0; i < VIDA_MAX + 1; i++)
    for (int j = 0; j < MAX_ENERGIA + 1; j++)
      for (int k = 0; k < NUM_ACOES; k++)
        tabela_estatisticas[i][j][k] = 0;
  // Atualizar estatísticas com estados reais do oponente
  int vidas[turno];
  int energias[turno];
  reconstruir_estados(hist_oponente, hist_bot, turno, vidas, energias);

  for (int i = 0; i < turno; i++) {
    int v = vidas[i];
    int e = energias[i];
    Acao a = hist_oponente[i];

    if (v >= 0 && v <= VIDA_MAX && e >= 0 && e <= MAX_ENERGIA) {
      tabela_estatisticas[v][e][a]++;
    }
  }

  // Prever próxima ação do oponente
  Acao previsao = prever_acao_oponente(oponente);

  // Estratégia baseada na previsão
  if (previsao == ATAQUE_PESADO) {
    if (!valida_acao(CONTRA_ATAQUE, bot, hist_bot, turno))
      return CONTRA_ATAQUE;
    if (!valida_acao(ATAQUE_PESADO, bot, hist_bot, turno))
      return ATAQUE_PESADO;
    // if (!valida_acao(ATAQUE, bot, hist_bot, turno)) return ATAQUE;
    if (!valida_acao(DEFESA, bot, hist_bot, turno))
      return DEFESA;
  }
  if (previsao == ATAQUE) {
    if (!valida_acao(ATAQUE_PESADO, bot, hist_bot, turno))
      return ATAQUE_PESADO;
    if (!valida_acao(DEFESA, bot, hist_bot, turno))
      return DEFESA;
    if (bot->vida < 3 && !valida_acao(CURA, bot, hist_bot, turno))
      return CURA;
  }
  if (previsao == RECARGA) {
    if (valida_acao(CONTRA_ATAQUE, oponente, hist_oponente, turno))
      if (!valida_acao(ATAQUE_PESADO, bot, hist_bot, turno))
        return ATAQUE_PESADO;
  }
  if (previsao == CONTRA_ATAQUE) {
    return RECARGA;
  }
  if (valida_acao(CONTRA_ATAQUE, oponente, hist_oponente, turno)) {
    if (!valida_acao(ATAQUE_PESADO, bot, hist_bot, turno))
      return ATAQUE_PESADO;
    if (valida_acao(DEFESA, oponente, hist_oponente, turno) &&
        !valida_acao(ATAQUE, bot, hist_bot, turno))
      return ATAQUE;
  }
  if (!valida_acao(ATAQUE_PESADO, oponente, hist_oponente, turno)) {
    if (!valida_acao(CONTRA_ATAQUE, bot, hist_bot, turno))
      return CONTRA_ATAQUE;
    if (!valida_acao(ATAQUE_PESADO, bot, hist_bot, turno))
      return ATAQUE_PESADO;
    // if (!valida_acao(ATAQUE, bot, hist_bot, turno)) return ATAQUE;
    if (!valida_acao(DEFESA, bot, hist_bot, turno))
      return DEFESA;
  }
  if (bot->vida < 3 && !valida_acao(CURA, bot, hist_bot, turno))
    return CURA;
  if (bot->energia >= 2 && !valida_acao(ATAQUE, bot, hist_bot, turno))
    return ATAQUE;
  return RECARGA;
}

// Estrutura do bot
static Bot bot __attribute__((section("bots"), used));

static void __attribute__((constructor)) registrar_bot(void) {
  inicializa_bot(&bot, "Bocchi", "NHK", (FuncaoDecisao)&tomar_decisao);
}
