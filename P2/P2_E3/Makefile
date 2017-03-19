########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p2_e3
########################################################
OBJECTSP2_E3 = p2_e3.o node.o graph.o stack.o element.o types.h
########################################################

all: $(EJS) clear

p2_e3: $(OBJECTSP2_E3)
	$(CC) $(CFLAGS) -o p2_e3 $(OBJECTSP2_E3)

p2_e3.o: p2_e3.c graph.h node.h element.h stack.h types.h
	$(CC) $(CFLAGS) -c p2_e3.c

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
	@echo ">>>>>>Running p2_e3"
	./p2_e3 grafo1.txt

runv:
	@echo ">>>>>>Running p1_e1 with valgrind"
	valgrind --leak-check=full ./p2_e3

