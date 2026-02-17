# Usage: make to build, make run to run, make clean to remove build and binary files
# Optional Arguments: you can set release=1, sanitize=1 to build in release profile, or with address sanitizer

# Colours for outputs
GREEN := \033[0;32m
NC := \033[0m

# Use the gcc compiler by default
CC ?= gcc

# A bunch of flags to enforce code safety and best practices
CFLAGS := -Wall -Wextra -Wpedantic -Wshadow -Wconversion -Wpointer-arith -Wformat=2 -Wundef -Wcast-align -Wswitch-enum -Wuninitialized -Wfloat-equal -fstack-protector-strong -D_FORTIFY_SOURCE=2
DEVFLAGS := -g -O
LDFLAGS :=
ASFLAGS := -fsanitize=address,undefined,leak

#For header dependancy tracking
CFLAGS += -MMD -MP

# if release=1 is set, don't include extra debug info
release ?= 0
ifeq ($(release), 0)
	CFLAGS += $(DEVFLAGS)
endif

# If sanitize=1 is set, run with address sanitizer
sanitize ?= 1
ifeq ($(sanitize), 1)
	CFLAGS += $(ASFLAGS)
	LDFLAGS += $(ASFLAGS)
endif

# Output locations
SRC_DIR := src
BUILD_DIR := build
BIN_DIR := bin
TARGET := shell

# List of files to include in build
SRCS := $(wildcard $(SRC_DIR)/*.c)
OBJS := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o, $(SRCS))
DEPS := $(OBJS:.o=.d)
# Ensure these targets are not mistaken as files to make
.PHONY: all run clean format

all: $(BIN_DIR)/$(TARGET)

$(BIN_DIR)/$(TARGET): $(OBJS) | $(BIN_DIR)
	@printf "$(GREEN)Compiling binary...\n$(NC)"
	@$(CC) $(OBJS) $(LDFLAGS) -o $@

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	@printf "$(GREEN)Compiling $< ...\n$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

# create build & bin directories if not present
$(BUILD_DIR) $(BIN_DIR):
	@printf "$(GREEN)Creating $@ directory...\n$(NC)"
	@mkdir -p $@

# make format - format all c files
format:
	@printf "$(GREEN)Formatting files...\n$(NC)"
	@clang-format -i $(SRC_DIR)/*.c include/*.h

# make run - Run program
run: all
	@printf "$(GREEN)Running $(BIN_DIR)/$(TARGET)...\n$(NC)"
	@./$(BIN_DIR)/$(TARGET)

# make clean - remove all output files
clean:
	rm -rf $(BUILD_DIR) $(BIN_DIR)

# For dependancy tracking
-include $(DEPS)
.PRECIOUS: $(DEPS)
