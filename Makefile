MAKEFLAGS += --no-builtin-rules
.DEFAULT_GOAL := all

INC_PATH = include
SRC_PATH = src
LIB_PATH = lib
OBJ_PATH = obj

EXE = chip8-emulator
LIBS = imgui

_IMGUI_PATH = imgui
_IMGUI_SRCS = imgui.cpp imgui_draw.cpp imgui_tables.cpp imgui_widgets.cpp backends/imgui_impl_opengl3.cpp backends/imgui_impl_sdl.cpp

_LIB_SRCS = $(patsubst %, $(_IMGUI_PATH)/%, $(_IMGUI_SRCS)) 
LIB_SRCS = $(patsubst %, $(LIB_PATH)/%, $(_LIB_SRCS))

_SRCS = main.cpp
SRCS = $(patsubst %, $(SRC_PATH)/%, $(_SRCS))

LIB_OBJS = $(patsubst %.cpp, $(OBJ_PATH)/%.o, $(LIB_SRCS))
SRC_OBJS = $(patsubst %.cpp, $(OBJ_PATH)/%.o, $(SRCS))
OBJS = $(SRC_OBJS) $(LIB_OBJS)

CC = g++
INCLUDE_FLAGS = -I$(INC_PATH) $(addprefix -I$(LIB_PATH)/, $(LIBS)) -I/usr/include/SDL2
WARNINGS_FLAGS = -Wall
LINKER_FLAGS = -lSDL2 -lGL -lGLEW
LIB_FLAGS = -DIMGUI_IMPL_OPENGL_LOADER_GLEW
CC_FLAGS = $(INCLUDE_FLAGS) $(WARNINGS_FLAGS) $(LINKER_FLAGS) $(LIB_FLAGS)

$(OBJS):
	mkdir -p $(dir $@)
	$(CC) -c -o $@ $(patsubst $(OBJ_PATH)/%.o, %.cpp, $@) $(CC_FLAGS)


.PHONY: all clean cleansrc fresh freshsrc

all: $(OBJS)
	$(CC) -o $(EXE) $^ $(CC_FLAGS)

clean:
	rm -f $(SRC_OBJS) $(EXE)

cleanlibs:
	rm -f $(OBJS) $(EXE)

fresh: clean all

freshlibs: cleanlibs all