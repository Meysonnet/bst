CC=gcc
EXEC=bst
OBJS=main.o bst.o database.o fictionalcharacter.o utils.o

all :			$(EXEC)
bst : 			
			$(CC) -o  $(EXEC) $(OBJS)
