#ifndef BOTS_H
#define BOTS_H

#include <stdbool.h>
#include "../tipos.h"

#define NUM_BOTS 25           // Número de bots na competição
#define NUM_ACOES 7           // Número de ações possíveis
#define VIDA_MAX 3            // Número máximo de vidas
#define NUM_CURAS 3           // Número inicial de curas
#define NUM_CONTRA_ATAQUES 3  // Número inicial de contra-ataques
#define ENERGIA_INICIAL 0     // Quantidade inicial de energia
#define CUSTO_ATQ_PESADO  2   // Quantas recargas custa um ataque pesado
#define NOME_TAMANHO_MAX  64  // Tamanho máximo do nome de um bot e da equipe que criou o bot

// Tipo representando um bot (jogador)
typedef struct aux{
    // Propriedades para simulação
    BotID id;                       // ID do bot
    char nome[NOME_TAMANHO_MAX];    // Nome do bot
    char equipe[NOME_TAMANHO_MAX];  // Nome da equipe que criou o bot
    short int pontuacoes[NUM_BOTS]; // Lista de pontuação por oponente
    short int vida;                 // Vida atual do bot [0, 3]
    short int energia;              // Energia atual do bot [0, inf]
    short int curas;                // Quantidade de curas restantes [0, 3]
    short int contra_ataques;       // Quantidade de contra-ataques restantes [0, 3]
    FuncaoDecisao tomar_decisao;    // Ponteiro para uma função de tomada de decisão

    // Propriedades para colheita de dados
    KD KDs[NUM_BOTS];                   // Número de abates e mortes do bot por oponente
    unsigned int num_acoes[NUM_ACOES];  // Total de vezes que cada ação foi realizada pelo bot ao longo da simulação
    unsigned int dano_tomado;           // Total de dano que o bot tomou ao longo da simulação
    unsigned short int sucesso_CA;      // Total de contra ataques bem sucedidos
    unsigned short int sucesso_defesas; // Total de defesas bem sucedidas
    unsigned int decisoes_tomadas;      // Total de decisões tomadas
    double tempo_decisao;               // Tempo médio para tomar uma decisão
} Bot;


/**************************************************************
 * Função que recebe o nome de um bot e da equipe que o criou,
 * e então retorna um bot novinho em folha
 *************************************************************/
void inicializa_bot(Bot *bot, const char *nome, const char *equipe, FuncaoDecisao f);

/**************************************************************
 * Restaura as condições do bot para o início de um novo
 * confronto. Retorna true se houver algum erro
 *************************************************************/
bool restaura_bot(Bot *bot);

#endif