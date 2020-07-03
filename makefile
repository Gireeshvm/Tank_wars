OBJS=*.cpp  

CC=g++

COMPILER_FLAGS=-w

LINKER_FLAGS=-lSDL2 

OUT=run

all:$(OBJS)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o build/$(OUT) $(OBJS) 

