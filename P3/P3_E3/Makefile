########################################################
CC=gcc
CFLAGS= -g -Wall -pedantic -ansi
EJS = p3_e3
########################################################
OBJECTSP3_E3 = p3_e3.o node.o list.o functions.o types.h
########################################################

all: $(EJS) clear

p3_e3: $(OBJECTSP3_E3)
	$(CC) $(CFLAGS) -o p3_e3 $(OBJECTSP3_E3)

p3_e3.o: p3_e3.c list.h node.h functions.h types.h
	$(CC) $(CFLAGS) -c p3_e3.c

list.o: list.c list.h
	$(CC) $(CFLAGS) -c list.c

functions.o: functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c


clear:
	rm -rf *.o 

clean:
	rm -rf *.o $(EJS)

run:
	@echo ">>>>>>Running p2_e3"
	./p3_e3 datos.txt

runv:
	@echo ">>>>>>Running p1_e1 with valgrind"
	valgrind --leak-check=full ./p3_e3 datos.txt

