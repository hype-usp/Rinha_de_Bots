#ifndef ESTATISTICAS_H
#define ESTATISTICAS_H

#include <stddef.h>
#include "../tipos.h"

// Função que inicializa uma estrutura de estatísticas com os valores padrão
void inicializa_estatisticas(Estatistica *estatistica);

// Mantém a contagem de número de combates da simulação
void incrementa_t_combates(Estatistica *estatistica);

// Mantém a contagem de número de confrontos da simulação
void incrementa_t_confrontos(Estatistica *estatistica);

// Mantém a contagem de número de turnos da simulação
void incrementa_t_turnos(Estatistica *estatistica);

// Calcula o número total de combates empatados
void calcula_t_empates(Estatistica *estatistica, Bot **bots, size_t num_bots);

// Calcula quantas defesas impediram dano
void calcula_p_boas_defesas(Estatistica *estatistica, Bot **bots, size_t num_bots);

// Calcula quantos contra-ataques causaram dano
void calcula_p_bons_contra_ataques(Estatistica *estatistica, Bot **bots, size_t num_bots);

// Calcula a proporção de ataques pesados em relação ao total de ataques
void calcula_p_ataques_pesados(Estatistica *estatistica, Bot **bots, size_t num_bots);

// Calcula o número médio de vezes que cada bot realizou cada ação
void calcula_m_num_acoes(Estatistica *estatistica, Bot **bots, size_t num_bots);

// Calcula o número médio de turnos por confronto
void calcula_m_turnos_por_confronto(Estatistica *estatistica);

// Cria um arquivo chamado stats_gerais.txt e escreve nele um breve relatório da simulação
void gerar_relatorio(Estatistica *estatistica);
#endif