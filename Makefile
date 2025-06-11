# =============================================================================
# Variáveis do Compilador e Flags
# =============================================================================

# O compilador C que será usado
CC = gcc

# Flags para o compilador:
# -Wall -Wextra: Ativa a maioria dos avisos úteis.
# -g: Inclui informações de debug no executável (para usar com gdb).
# -O2: Nível de otimização 2.
# -Isrc: Adiciona a pasta 'src' aos caminhos de busca por headers.
#        Isso permite usar #include "bots/bots.h" em vez de #include "src/bots/bots.h".
CFLAGS = -Wall -Wextra -g -O2 -Isrc

# Flags para o linker (se necessário no futuro)
LDFLAGS =


# =============================================================================
# Variáveis do Projeto
# =============================================================================

# Nome do executável final
TARGET = rinha_de_bots

# Pastas do projeto
SRC_DIR = src
OBJ_DIR = build


# =============================================================================
# Descoberta Automática de Arquivos
# =============================================================================

# Encontra todos os arquivos .c recursivamente dentro da pasta de fontes (src)
# Ex: src/main.c, src/bots/bots.c, src/bots/exemplo_bot.c
SOURCES := $(shell find $(SRC_DIR) -name '*.c')

# Gera a lista de arquivos-objeto correspondentes, colocando-os na pasta de build
# Ex: build/main.o, build/bots.o, build/exemplo_bot.o
# A função 'notdir' remove o caminho do diretório antes de adicionar o novo.
OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(notdir $(SOURCES)))

# Adiciona ao VPATH todos os subdiretórios de 'src' para que o 'make' possa
# encontrar os fontes dos arquivos-objeto.
VPATH = $(shell find $(SRC_DIR) -type d)


# =============================================================================
# Regras de Compilação
# =============================================================================

# A primeira regra é a padrão, executada quando 'make' é chamado sem argumentos.
all: $(TARGET)

# Regra para linkar o executável final
# Depende de todos os arquivos-objeto.
# '$^' é uma variável automática que significa "todos os pré-requisitos".
$(TARGET): $(OBJECTS)
	@echo "LD   $@"
	$(CC) $^ $(LDFLAGS) -o $@

# Regra de padrão para compilar arquivos .c em .o
# Esta regra ensina ao 'make' como criar um arquivo em 'build/' a partir de
# um arquivo em 'src/' (encontrado via VPATH).
$(OBJ_DIR)/%.o: %.c
	@# Garante que o diretório de build existe.
	@mkdir -p $(OBJ_DIR)
	@echo "CC   $<"
	$(CC) $(CFLAGS) -c $< -o $@


# =============================================================================
# Comandos Adicionais
# =============================================================================

# Roda o programa
run: $(TARGET)
	./$(TARGET)

# Limpa os arquivos gerados (pasta de build e executável)
clean:
	@echo "CLEAN"
	@rm -rf $(OBJ_DIR) $(TARGET)

# Reconstrói o projeto do zero
re: clean all


# =============================================================================
# Alvos Falsos (Phony Targets)
# =============================================================================

# Declara alvos que não representam arquivos reais.
.PHONY: all clean re run