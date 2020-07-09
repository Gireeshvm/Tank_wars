OBJS=*.cpp  

CC=g++

COMPILER_FLAGS=-w

LINKER_FLAGS=-lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

OUT=run

all:$(OBJS)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o build/$(OUT) $(OBJS) 

