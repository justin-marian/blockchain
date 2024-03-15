CFLAGS := -c -g -Wall -Wextra -Werror -Wpedantic \
          -Wshadow -Wwrite-strings -Wstrict-prototypes \
          -Wold-style-definition -Wredundant-decls \
          -Wnested-externs -Wmissing-include-dirs \
          -Wjump-misses-init -Wlogical-op -O \
          -Wformat=2 -Wno-unused-parameter \
          -D_POSIX_C_SOURCE=200809L -std=c99

# Object direcoty files
BIN_DIR := ./bin/
# C Source directory files
LIBS := ../src/libs/utils/
BLOCKCHAIN := ../src/blockchain/
CHAIN_UTILS := ../src/blockchain/chains/

# List of source files
FILES := $(BLOCKCHAIN)/block_dag.c $(CHAIN_UTILS)/evolve.c\
         $(CHAIN_UTILS)/chain_graph.c $(CHAIN_UTILS)/chain_list.c \
         $(LIBS)/list.c $(LIBS)/stack.c $(LIBS)/queue.c $(LIBS)/graph.c

# Create a list of object files in the "bin" directory by replacing .c with .o
OBJ_FILES := $(addprefix $(BIN_DIR)/, $(notdir $(FILES:.c=.o)))

.PHONY: build bin clean

# Default target
build: bin blockdag

bin: $(BIN_DIR)

# Create the "bin" directory if it doesn't exist
$(BIN_DIR):
	@mkdir -p $(BIN_DIR)

# Compile source files into object files in the "bin" directory
$(BIN_DIR)/%.o: $(LIBS)/%.c | $(BIN_DIR)
	@gcc $(CFLAGS) -o $@ $<

$(BIN_DIR)/%.o: $(BLOCKCHAIN)/%.c | $(BIN_DIR)
	@gcc $(CFLAGS) -o $@ $<

$(BIN_DIR)/%.o: $(CHAIN_UTILS)/%.c | $(BIN_DIR)
	@gcc $(CFLAGS) -o $@ $<

# Link the object files to build the final executable
blockdag: $(OBJ_FILES)
	@gcc $(OBJ_FILES) -o blockdag

clean:
	@rm -rf blockdag blockdag.in blockdag.out

clean_all:
	@rm -rf blockdag blockdag.in blockdag.out log_valgrind.txt $(BIN_DIR)

