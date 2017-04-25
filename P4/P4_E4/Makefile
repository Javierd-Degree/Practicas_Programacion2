########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p4_e4
########################################################
OBJECTSP4_E4 = p4_e4.o tree.o node_p4.o list.o functions.o types.h
########################################################

all: $(EJS) clear

p4_e4: $(OBJECTSP4_E4)
	$(CC) $(CFLAGS) -o p4_e4 $(OBJECTSP4_E4)

p4_e4.o: p4_e4.c tree.h list.h node.h functions.h types.h
	$(CC) $(CFLAGS) -c p4_e4.c

tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

node_p4.o: node_p4.c node.h
	$(CC) $(CFLAGS) -c node_p4.c

graph.o: graph.c graph.h
	$(CC) $(CFLAGS) -c graph.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c


clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p4_e4"
	./p4_e4 cadenas.txt

runv:
	@echo ">>>>>>Running p4_e4 with valgrind"
	valgrind --leak-check=full ./p4_e4 cadenas.txt

