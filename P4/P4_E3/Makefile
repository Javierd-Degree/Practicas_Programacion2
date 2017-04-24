########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e3
########################################################
OBJECTSP4_E3 = p4_e3.o tree.o node.o list.o functions.o types.h
########################################################

all: $(EJS) clear

p4_e3: $(OBJECTSP4_E3)
	$(CC) $(CFLAGS) -o p4_e3 $(OBJECTSP4_E3)

p4_e3.o: p4_e3.c tree.h list.h node.h functions.h types.h
	$(CC) $(CFLAGS) -c p4_e3.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

node.o: node.c node.h
	$(CC) $(CFLAGS) -c node.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c


clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p3_e4"
	./p4_e3 numeros.txt

runv:
	@echo ">>>>>>Running p3_e4 with valgrind"
	valgrind --leak-check=full ./p4_e3 datos.txt

