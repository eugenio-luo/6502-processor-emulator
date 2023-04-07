SRC_DIR := src
TEST_DIR := test 
INCLUDE_DIR := src/include
TEST_INCLUDE_DIR := test/include
LOG_DIR := logs/
OUT_FILE := NES-emulator.out

CFILES := $(shell find $(SRC_DIR) -type f -name "*.c")
TEST_CFILES := $(shell find $(TEST_DIR) -type f -name "*.c")
W_FLAGS := -std=c99 -Wpedantic -pedantic-errors -Werror -Wall -Wextra \
	   -Waggregate-return -Wbad-function-cast -Wcast-align -Wcast-qual \
	   -Wfloat-equal -Wformat=2 -Wlogical-op \
	   -Wmissing-declarations -Wmissing-include-dirs -Wmissing-prototypes \
	   -Wnested-externs -Wpointer-arith -Wredundant-decls -Wsequence-point -Wshadow \
	   -Wstrict-prototypes -Wswitch -Wundef -Wunreachable-code \
	   -Wunused-but-set-parameter -Wwrite-strings
CFLAGS := -I$(INCLUDE_DIR) $(W_FLAGS) -D_DEFAULT_SOURCE -DLOG_DIR_PATH='"$(LOG_DIR)"'
#SDL_FLAGS := -lSDL2 -lSDL2_ttf
SDL_FLAGS := 
TEST_CFLAGS := -DTEST -I$(TEST_INCLUDE_DIR) $(CFLAGS) 

.PHONY: all test clean

all: compile

clean:
	@ rm $(OUT_FILE)

compile:
	@ gcc $(CFLAGS) $(CFILES) $(SDL_FLAGS) -o $(OUT_FILE)

test:
	@ gcc $(TEST_CFLAGS) $(CFILES) $(TEST_CFILES) $(SDL_FLAGS) -o $(OUT_FILE)
