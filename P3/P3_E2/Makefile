########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p3_e2
########################################################
OBJECTSP3_E2 = p3_e2.o graph.o node.o queue.o functions.o types.h
########################################################

all: $(EJS) clear

p3_e2: $(OBJECTSP3_E2)
	$(CC) $(CFLAGS) -o p3_e2 $(OBJECTSP3_E2)

p3_e2.o: p3_e2.c queue.h graph.h node.h functions.h types.h
	$(CC) $(CFLAGS) -c p3_e2.c

queue.o: queue.c queue.h
	$(CC) $(CFLAGS) -c queue.c

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
	@echo ">>>>>>Running p3_e2"
	./p3_e2 datos.txt

runv:
	@echo ">>>>>>Running p3_e2 with valgrind"
	valgrind --leak-check=full ./p3_e2 datos.txt

