#ifndef TIPOS_H
#define TIPOS_H

#define TURNOS_MAX 30

// Tipo representando a AÇÃO de um bot
typedef enum {
    RECARGA = 0,
    ATAQUE,
    ATAQUE_PESADO,
    DEFESA,
    CURA,
    CONTRA_ATAQUE,
    VACILO
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

#endif