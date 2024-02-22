# DEFINITION OF PROGRAMS TO USE
CC := clang

SRC_DIR := src
BIN_DIR := bin
OBJ_DIR := obj

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

EXEC := $(BIN_DIR)/run

CPPFLAGS := -Iinclude -MD -MP
CFLAGS := -Wall -g -O0 
LDFLAGS := -Llib
LDLIBS := -lxcb

.PHONY: all clean

all: $(EXEC)

$(EXEC): $(OBJ)
	@mkdir -p $(@D)
	@$(CC) $(LDFLAGS) $(LDLIBS) $^ -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CPPFLAGS) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) -rf $(BIN_DIR) $(OBJ_DIR)

-include $(patsubst %.o, %.d, $(OBJ))
