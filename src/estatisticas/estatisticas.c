#include <stdio.h>
#include "estatisticas.h"
#include "../bots/bots.h"

void inicializa_estatisticas(Estatistica *estatistica) {
	estatistica->t_combates = 0;
	estatistica->t_confrontos = 0;
	estatistica->t_turnos = 0;
	estatistica->t_empates = 0;
	estatistica->p_boas_defesas = 0.0;
	estatistica->p_bons_contra_ataques = 0.0;
	estatistica->p_ataques_pesados = 0.0;
	estatistica->m_turnos_por_confronto = 0.0;
	for(int i = 0; i < NUM_ACOES; i++) {
		estatistica->m_num_acoes[i] = 0.0;
	}
}

void incrementa_t_combates(Estatistica *estatistica) {
	estatistica->t_combates++;
}

void incrementa_t_confrontos(Estatistica *estatistica) {
	estatistica->t_confrontos++;
}

void incrementa_t_turnos(Estatistica *estatistica) {
	estatistica->t_turnos++;
}

void calcula_t_empates(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	estatistica->t_empates = 0;
	for(size_t i = 0; i < num_bots; i++) {
		for(size_t j = 0; j < num_bots; j++) {
			estatistica->t_empates += bots[i]->VDEs[j].empates;
		}
	}
	estatistica->t_empates /= 2;
}

void calcula_p_boas_defesas(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	double t_defesas = 0.0;
	double t_boas_defesas = 0.0;
	for(size_t i = 0; i < num_bots; i++) {
		t_defesas += (double) bots[i]->num_acoes[DEFESA];
		t_boas_defesas += (double) bots[i]->boas_defesas;
	}
	estatistica->p_boas_defesas = t_boas_defesas / t_defesas;
}

void calcula_p_bons_contra_ataques(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	double t_contra_ataques = 0.0;
	double t_bons_contra_ataques = 0.0;
	for(size_t i = 0; i < num_bots; i++) {
		t_contra_ataques += (double) bots[i]->num_acoes[CONTRA_ATAQUE];
		t_bons_contra_ataques += (double) bots[i]->bons_contra_ataques;
	}
	estatistica->p_bons_contra_ataques = t_bons_contra_ataques / t_contra_ataques;
}

void calcula_p_ataques_pesados(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	double t_ataques = 0.0;
	double t_ataques_pesados = 0.0;
	for(size_t i = 0; i < num_bots; i++) {
		t_ataques += (double) bots[i]->num_acoes[ATAQUE];
		t_ataques_pesados += (double) bots[i]->num_acoes[ATAQUE_PESADO];
	}
	estatistica->p_ataques_pesados = t_ataques_pesados / t_ataques;
}

void calcula_m_num_acoes(Estatistica *estatistica, Bot **bots, size_t num_bots) {
	double t_acoes[NUM_ACOES] = { 0 };
	for(size_t i = 0; i < num_bots; i++) {
		for(int acao = 0; acao < NUM_ACOES; acao++) {
			t_acoes[acao] += (double) bots[i]->num_acoes[acao];

		}
	}
	for(int acao = 0; acao < NUM_ACOES; acao++) {
		estatistica->m_num_acoes[acao] = t_acoes[acao] / num_bots;
	}
}

void calcula_m_turnos_por_confronto(Estatistica *estatistica) {
	estatistica->m_turnos_por_confronto = (double)estatistica->t_turnos / estatistica->t_confrontos;
}

void gerar_relatorio(Estatistica *estatistica) {
	FILE *relatorio = fopen("stats_gerais.txt", "w");
	fputs("RELATÓRIO: ESTATÍSTICAS GERAIS DA RINHA\n", relatorio);
	fprintf(relatorio, "Número de combates: %d\n", estatistica->t_combates);
	fprintf(relatorio, "Número de confrontos: %d\n", estatistica->t_confrontos);
	fprintf(relatorio, "Número de turnos: %d\n", estatistica->t_turnos);
	fprintf(relatorio, "Número de empates: %d\n", estatistica->t_empates);
	fprintf(relatorio, "Média de turnos por confronto: %.2Lf\n", estatistica->m_turnos_por_confronto);
	fprintf(relatorio, "Proporção de boas defesas: %.2Lf%%\n", estatistica->p_boas_defesas * 100);
	fprintf(relatorio, "Proporção de bons contra-ataques: %.2Lf%%\n", estatistica->p_bons_contra_ataques * 100);
	fprintf(relatorio, "Proporção de ataques pesados: %.2Lf%%\n", estatistica->p_ataques_pesados * 100);
	fputs("\nUso médio de cada ação por confronto\n", relatorio);
	char *acoes[7] = { "RECARGA", "ATAQUE", "ATAQUE PESADO", "DEFESA", "CURA", "CONTRA ATAQUE", "VACILO"};
	for(int acao = 0; acao < NUM_ACOES; acao++) {
		fprintf(relatorio, "%s: %.2Lf\n", acoes[acao], estatistica->m_num_acoes[acao] / estatistica->t_confrontos);
	}
	fclose(relatorio);
}