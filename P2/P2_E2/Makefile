########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p2_e2
########################################################
OBJECTSP2_E2 = p2_e2.o node.o graph.o stack.o element.o types.h
########################################################

all: $(EJS) clear

p2_e2: $(OBJECTSP2_E2)
	$(CC) $(CFLAGS) -o p2_e2 $(OBJECTSP2_E2)

p2_e2.o: p2_e2.c graph.h node.h element.h stack.h types.h
	$(CC) $(CFLAGS) -c p2_e2.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

element.o: element.c element.h
	$(CC) $(CFLAGS) -c element.c

stack.o: stack.c stack.h
	$(CC) $(CFLAGS) -c stack.c



clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e2"
	./p2_e2 grafo1.txt

runv:
	@echo ">>>>>>Running p2_e2 with valgrind"
	valgrind --leak-check=full ./p2_e2

