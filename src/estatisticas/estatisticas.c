#include "estatisticas.h"

void inicializa_estatisticas(Estatistica *estatistica) {
	estatistica->t_combates = 0;
	estatistica->t_confrontos = 0;
	estatistica->t_turnos = 0;
	estatistica->t_empates = 0;
	estatistica->p_boas_defesas = 0.0;
	estatistica->p_bons_contra_ataques = 0.0;
	estatistica->p_ataques_pesados = 0.0;
	estatistica->m_num_acoes = 0.0;
	estatistica->m_turnos_por_confronto = 0.0;
}

void incrementa_t_combates(Estatistica *estatistica) {
	estatistica->t_combates++;
}

void incrementa_t_embates(Estatistica *estatistica) {
	estatistica->t_embates++;
}

void incrementa_t_turnos(Estatistica *estatistica) {
	estatistica->t_turnos++;
}

void calcula_t_empates(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	// TODO
}

void calcula_p_boas_defesas(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	// TODO
}

void calcula_p_bons_contra_ataques(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	// TODO
}

void calcula_p_ataques_pesados(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	// TODO
}

void calcula_m_num_acoes(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	// TODO
}

void calcula_m_turnos_por_confronto(Estatistica *estatistica) {
	// TODO
}