#ifndef TIPOS_H
#define TIPOS_H

#define MAX_TURNOS 25 // Número máximo de turnos por confronto
#define NUM_ACOES 7   // Número de ações possíveis

typedef unsigned short int BotID;

// Tipo representando a AÇÃO de um bot
typedef enum {
    RECARGA = 0,   // Recupera 1 energia de um bot
    ATAQUE,        // Causa 1 de dano ao bot inimigo
    ATAQUE_PESADO, // Causa 3 de dano ao bot inimigo
    DEFESA,        // Anula ataques e reduz dano de ataques pesados
    CURA,          // Regenera 1 de vida de um bot
    CONTRA_ATAQUE, // Redireciona o ataque de um inimigo para ele mesmo
    VACILO         // Não faz nada (caso um bot tente uma ação ilegal)
} Acao;

// Tipo representando o número de abates e mortes (Kills/Deaths) de um bot
typedef struct {
    unsigned int abates;
    unsigned int mortes;
} KD;

// Tipo representando o número de combates vencidos, perdidos e empatados de um bot 
typedef struct {
    unsigned int vitorias;
    unsigned int derrotas;
    unsigned int empates;
} VDE;

// Tipo representando o historico de ações de um bot
typedef Acao Historico[MAX_TURNOS];

typedef struct Bot Bot;

// Tipo representando um ponteiro para uma função de tomada de decisão de um bot
typedef Acao (*FuncaoDecisao)(const Bot *, const Bot *, Historico, Historico, int);

// Tipo representando os estados possíveis de um confronto após um dado turno
typedef enum {
    INACABADO,      // Nenhum bot morreu ainda
    BOT1_VENCEU,    // O bot 2 morreu
    BOT2_VENCEU,    // O bot 1 morreu
    AMBOS_MORRERAM, // ... Ambos morreram
    EXCESSO_TURNOS  // O número de turnos máximo por combate foi excedido
} EstadoConfronto;

typedef struct {
    Acao acao_bot1;
    Acao acao_bot2;
    EstadoConfronto estado_confronto;
} ResultadoTurno;

/**************************************************************
 * Tipo que representa as estatísticas gerais da simulação, os
 * atributos possuem os seguintes prefixos com os seguintes
 * significados:
 * t = "total de"
 * p = "proporção de"
 * m = "média de"
 *************************************************************/
typedef struct {
    int t_combates;
	int t_confrontos;
    int t_turnos;
	int t_empates;
	long double p_boas_defesas;
    long double p_bons_contra_ataques;
    long double p_ataques_pesados;
    long double m_acoes_usadas;
    long double m_turnos_por_confronto;
    long double m_num_acoes[NUM_ACOES];
} Estatistica;

#endif