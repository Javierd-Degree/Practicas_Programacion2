########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p3_e4
########################################################
OBJECTSP3_E4 = graph_test.o graph.o node.o list.o functions.o types.h
########################################################

all: $(EJS) clear

p3_e4: $(OBJECTSP3_E4)
	$(CC) $(CFLAGS) -o p3_e4 $(OBJECTSP3_E4)

graph_test.o: graph_test.c list.h graph.h node.h functions.h types.h
	$(CC) $(CFLAGS) -c graph_test.c

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
	./p3_e4 datos.txt

runv:
	@echo ">>>>>>Running p3_e4 with valgrind"
	valgrind --leak-check=full ./p3_e4 datos.txt

