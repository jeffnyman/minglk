.DELETE_ON_ERROR:

CC := gcc

SRC_DIR ?= src
OBJ_DIR ?= obj
BIN_DIR ?= bin

ifeq ($(CC), gcc)
CFLAGS += -std=c11 -Wall
endif

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ := $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRC))

TARGET := $(BIN_DIR)/libminglk.a

ifeq ($(OS), Windows_NT)
	MKDIR = if not exist $(subst /,\\,$(1)) mkdir $(subst /,\\,$(1))
else
	MKDIR = mkdir -p $(1)
endif

ifeq ($(OS), Windows_NT)
	RMDIR = if exist $(subst /,\\,$(1)) rmdir /S /Q $(subst /,\\,$(1))
else
	RMDIR = rm -rf $(1)
endif

all: $(TARGET)

$(TARGET): $(OBJ)
	@$(call MKDIR, $(BIN_DIR))
	ar rcs $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@$(call MKDIR, $(OBJ_DIR))
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(call RMDIR, $(OBJ_DIR))
	@$(call RMDIR, $(BIN_DIR))

.PHONY: all clean
