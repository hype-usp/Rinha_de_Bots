#include "bots.h"

/**************************************************************
 * Este bot também é bem mínimo, ele apenas alterna entre
 * recarregar a energia duas vezes e dar um ataque pesado
 *************************************************************/
static Acao tomar_decisao(const Bot *bot, const Bot *oponente, Historico hist_bot, Historico hist_oponente, unsigned short int turno) {
	if((turno + 1) % 3) return RECARGA;
	else return ATAQUE_PESADO;
}

// Esta é a estrutura do seu bot, não mexa nesta linha
static Bot bot __attribute__((section("bots"), used)); // Apenas declaração

static void __attribute__((constructor)) registrar_bot(void) {
	/**********************************************************
	 * Chame esta função substituindo o segundo e o terceiro
	 * argumentos pelo nome do seu bot e o nome de sua equipe,
	 * respectivamente. Por exemplo:
	 * inicializa_bot(&bot, "Crododilo Bombardilo", "Hype - Eventos", (FuncaoDecisao)&tomar_decisao);
	 * Exceto por isso, não mexa nesta linha.
	 *********************************************************/
    inicializa_bot(&bot, "Crododilo Bombardilo", "Hype - Eventos", (FuncaoDecisao)&tomar_decisao);
}
