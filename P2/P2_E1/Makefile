########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p2_e1
########################################################
OBJECTSP2_E1 = p2_e1.o stack.o element.o types.h
########################################################

all: $(EJS) clear

p2_e1: $(OBJECTSP2_E1)
	$(CC) $(CFLAGS) -o p2_e1 $(OBJECTSP2_E1)

p2_e1.o: p2_e1.c element.h stack.h types.h
	$(CC) $(CFLAGS) -c p2_e1.c

element.o: element.c element.h
	$(CC) $(CFLAGS) -c element.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c



clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e1"
	./p2_e1 grafo1.txt

runv:
	@echo ">>>>>>Running p2_e1 with valgrind"
	valgrind --leak-check=full ./p2_e1

