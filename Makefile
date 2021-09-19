SRC_DIR = src
ENTRY = $(SRC_DIR)/main.c
SRCS = $(filter-out $(ENTRY),$(wildcard $(SRC_DIR)/*.c)) ./dep/gl.c
INC =
LIB =
BIN_DIR = ./bin
BIN_NAME = main.out

ifeq ($(OS),Windows_NT)
	$(BIN_NAME) := $(BIN_NAME:.out=.exe)
else
	$(BIN_NAME) := $(BIN_NAME:.out=.out)
endif

BIN = $(BIN_DIR)/$(BIN_NAME)
LDFLAGS = -lglfw -lGL -lm
CC = gcc
CFLAGS = -Wall -Wextra -Werror -pedantic -pedantic-errors -std=c99


.PHONY: clean debug release all

all: clean debug release

release:
	$(CC) -O3 $(ENTRY) $(SRCS) $(LIB) $(INC) $(CFLAGS) -o $(BIN) $(LDFLAGS)

debug:
	$(CC) -ggdb $(ENTRY) $(SRCS) $(LIB) $(INC) $(CFLAGS) -o $(BIN_DIR)/d$(BIN_NAME) $(LDFLAGS)

clean:
	rm -rf *.out
