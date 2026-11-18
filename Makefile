# Compilador e flags de aviso/depuração
CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -g -Iinclude

# Diretórios e arquivos automáticos
SRC_DIR = src
OBJ_DIR = build
BIN_DIR = bin
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))
TARGET = $(BIN_DIR)/triagem

.PHONY: all clean run memcheck help

all: $(TARGET)

# $@ = alvo (bin/triagem) | $^ = todas as dependências (.o)
$(TARGET): $(OBJS)
	@mkdir -p $(BIN_DIR)
	$(CC) $(CFLAGS) -o $@ $^

# $< = primeira dependência (o arquivo .c atual)
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

memcheck: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(TARGET)

clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)

help:
	@echo "Comandos disponíveis:"
	@echo "  make          -> Compila o projeto"
	@echo "  make run      -> Compila e executa o sistema"
	@echo "  make memcheck -> Roda com Valgrind (caça vazamentos de memória)"
	@echo "  make clean    -> Apaga arquivos compilados (build/ e bin/)"