#include "bots/bots.h"
#include "estatisticas/estatisticas.h"
#include "jogo/jogo.h"
#include "tipos.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**************************************************************
 * Compilação - rode o comando:
 * $ make -B all
 *
 * Execução (fora do container, funciona apenas no Linux) - rode o comando:
 * $ make run
 *
 * Execução com Docker:
 * - Se você está no Windows:
 *   $ docker run -v "C:\caminho\completo\para\a\sua\pasta\Rinha_de_Bots" rinha-de_bots
 * - Se você está no Linux ou MacOS
 *   $ docker run -v "$(pwd):/app" rinha-de-bots
 *************************************************************/

// Declara os símbolos de início e fim da seção "bots" que o linker irá criar.
extern Bot __start_bots;
extern Bot __stop_bots;

int compara_bots_por_id(const void *a, const void *b) {
  Bot *botA = *(Bot **)a;
  Bot *botB = *(Bot **)b;
  return (botA->id - botB->id);
}

int main() {
  /**********************************************************
   * Calcula o número de bots e gera uma lista com cada um
   * deles a partir do espaço reservado na memória pelo
   * linker. ![Área de alta periculosidade]!
   *********************************************************/
  const size_t num_bots =
      (size_t)(((char *)&__stop_bots - (char *)&__start_bots) / sizeof(Bot));
  Bot *lista_de_bots[num_bots];
  for (size_t i = 0; i < num_bots; i++)
    lista_de_bots[i] =
        (Bot *)((char *)&__start_bots +
                (i * (sizeof(Bot) + 16))); // Esse +16 é magia negra

  // Ordena os bots da lista para que seus índices correspondam aos seus IDs
  qsort(lista_de_bots, num_bots, sizeof(Bot *), compara_bots_por_id);

  // Exibindo infos gerais sobre os bots participando da rinha
  printf("\nTotal de %zu bots prontos para a rinha!\n", num_bots);
  for (int i = 0; i < (int)num_bots; i++) {
    Bot *b = lista_de_bots[i];
    printf("Bot #%d - %s da equipe %s\n", b->id, b->nome, b->equipe);
  }

  // Setando a seed do RNG
  srand(time(NULL));

  // Avisando que a simulação está em execução
  printf("EXECUTANDO A RINHA...");

  // Que o melhor vença!
  Estatistica estatisticas = inicia_simulacao(lista_de_bots, num_bots);

  // Calculando a pontuação de cada bot contra cada um dos outros
  calcula_pontuacoes(lista_de_bots, num_bots);
  // Mostrando as estatísticas de cada bot no terminal
  exibe_bots_stats(lista_de_bots, num_bots);
  // Gerando relatório CSV das estatísticas de cada bot em bot_stats.csv
  gerar_relatorio_bots(lista_de_bots, num_bots);
  // Calculando as estatísticas deriváveis pelos dados dos bots
  calcula_estatisticas(&estatisticas, lista_de_bots, num_bots);
  // Gerando o relatório stats_gerais.txt
  gerar_relatorio(&estatisticas, num_bots);

  return 0;
}
