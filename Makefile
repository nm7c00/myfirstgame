OBJS = ./src/main.c ./src/errorout.c ./src/methods/mainmenu.c  ./src/methods/levelone.c  

OBJ_NAME = ./bin/exec

CC = gcc

DEBUG_FLAGS = -Wall -og -o0 

PROD_FLAGS = -ofast

LINKER_FLAGS = -lSDL2

all : $(OBJ)
	$(CC) $(OBJS) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 
