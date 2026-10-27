# === Variables ===
CC       := gcc
CFLAGS   := -O0 -Wall -Wextra -nostdlib -static -fno-builtin -mstackrealign
INC_DIR  := include
SRC_DIR  := src
BLD_DIR  := build
EXE      := mystd

# === Trouve automatiquement tous les fichiers .c dans SRC_DIR ===
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BLD_DIR)/%.o,$(SRCS))

# === Règle principale ===
all: $(BLD_DIR)/$(EXE)

# === Lien final ===
$(BLD_DIR)/$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# === Compilation générique pour chaque .o ===
$(BLD_DIR)/%.o: $(SRC_DIR)/%.c | $(BLD_DIR)
	$(CC) -c $(CFLAGS) -I$(INC_DIR) $< -o $@

# === Crée le dossier build s’il n’existe pas ===
$(BLD_DIR):
	mkdir -p $(BLD_DIR)

# === Nettoyage ===
clean:
	rm -f $(BLD_DIR)/*.o
	rm -f $(BLD_DIR)/$(EXE)
	rm -f *.out
	rm -f *.txt

.PHONY: all clean