MAKEFLAGS += --no-builtin-rules
.DEFAULT_GOAL := all

INC_PATH = include
INC_DIRS = drawing hardware instructions
SRC_PATH = src
LIB_PATH = lib
OBJ_PATH = obj

EXE = chip8-emulator
LIBS = imgui

_IMGUI_PATH = imgui
_IMGUI_SRCS = imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp backends/imgui_impl_opengl3.cpp backends/imgui_impl_sdl.cpp

_LIB_SRCS = $(addprefix $(_IMGUI_PATH)/, $(_IMGUI_SRCS)) 
LIB_SRCS = $(addprefix $(LIB_PATH)/, $(_LIB_SRCS))

SRCS = $(wildcard $(SRC_PATH)/*.cpp)
SRCS += $(wildcard $(SRC_PATH)/hardware/*.cpp)
SRCS += $(wildcard $(SRC_PATH)/instructions/*.cpp)
SRCS += $(wildcard $(SRC_PATH)/drawing/*.cpp)

LIB_OBJS = $(addprefix $(OBJ_PATH)/, $(LIB_SRCS:.cpp=.o))
SRC_OBJS = $(addprefix $(OBJ_PATH)/, $(SRCS:.cpp=.o))
OBJS = $(SRC_OBJS) $(LIB_OBJS)

CC = g++
INCLUDE_FLAGS = $(addprefix -I$(INC_PATH)/, $(INC_DIRS)) \
				$(addprefix -I$(LIB_PATH)/, $(LIBS)) \
				-I/usr/include/SDL2
WARNINGS_FLAGS = -Wall
LINKER_FLAGS = -lSDL2 -lGL -lGLEW
LIB_FLAGS = -DIMGUI_IMPL_OPENGL_LOADER_GLEW
STD_FLAG = -std=c++2a
CC_FLAGS = $(INCLUDE_FLAGS) $(WARNINGS_FLAGS) $(LINKER_FLAGS) $(LIB_FLAGS) $(STD_FLAG)

$(OBJS): $(OBJ_PATH)/%.o: %.cpp
	mkdir -p $(dir $@) 
	$(CC) -c -o $@ $< $(CC_FLAGS)

.PHONY: all clean cleansrc fresh freshsrc

all: $(OBJS)
	$(CC) -o $(EXE) $^ $(CC_FLAGS)

clean:
	rm -f $(SRC_OBJS) $(EXE)

cleanlibs:
	rm -f $(OBJS) $(EXE)

fresh: clean all

freshlibs: cleanlibs all