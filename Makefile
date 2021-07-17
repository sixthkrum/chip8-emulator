MAKEFLAGS += --no-builtin-rules
.DEFAULT_GOAL := game

INC_PATH = include
SRC_PATH = src
LIB_PATH = lib
OBJ_PATH = obj

EXE = chip8-emulator

_SRCS = main.cpp
SRCS = $(patsubst %, $(SRC_PATH)/%, $(_SRCS))

OBJS = $(patsubst %.cpp, $(OBJ_PATH)/%.o, $(_SRCS))

CC = g++
INCLUDE_FLAGS = -I$(INC_PATH) -I$(LIB_PATH)
WARNINGS_FLAGS = -Wall
CC_FLAGS = $(INCLUDE_FLAGS) $(WARNINGS_FLAGS)

$(OBJS): $(SRCS)
	mkdir -p $(OBJ_PATH)
	$(CC) -c -o $@ $< $(CC_FLAGS)

game: $(OBJS)
	$(CC) -o $(EXE) $^ $(CC_FLAGS)

.PHONY: clean
clean:
	rm -f $(OBJS) $(EXE)