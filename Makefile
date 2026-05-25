CC := gcc
CFLAGS := -Wall -Wextra

BIN_DIR := bins
SRC_DIR := src

SRCS := $(wildcard $(SRC_DIR)/*.c)

BINS := $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%, $(SRCS))

all: $(BIN_DIR) $(BINS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

$(BIN_DIR)/%: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -rf $(BIN_DIR)

.PHONY: clean all
