OBJS = ./src/main.c ./src/errorout.c ./src/object/mainmenu.c  ./src/object/levelone.c ./src/list/level_one_list.c ./src/list/main_menu_list.c ./src/list/destroy_list.c

OBJ_NAME = ./bin/exec

CC = gcc

DEBUG_FLAGS = -Wall -og -o0 

PROD_FLAGS = -ofast

LINKER_FLAGS = -lSDL2

all : $(OBJ)
	$(CC) $(OBJS) $(DEBUG_FLAGS) $(LINKER_FLAGS) -o $(OBJ_NAME) 
