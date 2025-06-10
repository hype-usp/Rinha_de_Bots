#ifndef TIPOS_H
#define TIPOS_H

#define TURNOS_MAX 30

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
    unsigned short int abates;
    unsigned short int mortes;
} KD;

// Tipo representando o historico de ações de um bot
typedef Acao Historico[TURNOS_MAX];

// Tipo representando um ponteiro para uma função de tomada de decisão de um bot
typedef Acao (*FuncaoDecisao)(struct aux, Historico, Historico, int);

// Tipo representando os estados possíveis de um confronto após um dado turno
typedef enum {
    INACABADO,     // Nenhum bot morreu ainda
    BOT1_VENCEU,   // O bot 2 morreu
    BOT2_VENCEU,   // O bot 1 morreu
    AMBOS_MORRERAM // ... Ambos morreram
} EstadoConfronto;

/**************************************************************
 * Tipo que representa as estatísticas gerais da simulação, os
 * atributos possuem os seguintes sufixos com os seguintes
 * significados:
 * m = "média de"
 * p = "proporção de"
 * t = "total de"
 *************************************************************/
typedef struct {
	long double m_turnos_por_confronto;
	long double p_boas_defesas;
	int t_empates;
} Estatistica;

#endif