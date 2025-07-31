#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stddef.h>
#include "../tipos.h"

// Função que inicializa uma estrutura de estatísticas com os valores padrão
void inicializa_estatisticas(Estatistica *estatistica);

void incrementa_t_combates(Estatistica *estatistica);

void incrementa_t_confrontos(Estatistica *estatistica);

void incrementa_t_turnos(Estatistica *estatistica);

void calcula_t_empates(Estatistica *estatistica, Bot **bots, size_t num_bots);

void calcula_p_boas_defesas(Estatistica *estatistica, Bot **bots, size_t num_bots);

void calcula_p_bons_contra_ataques(Estatistica *estatistica, Bot **bots, size_t num_bots);

void calcula_p_ataques_pesados(Estatistica *estatistica, Bot **bots, size_t num_bots);

void calcula_m_num_acoes(Estatistica *estatistica, Bot **bots, size_t num_bots);

void calcula_m_turnos_por_confronto(Estatistica *estatistica);

void gerar_relatorio(Estatistica *estatistica);
#endif