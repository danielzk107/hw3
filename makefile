CC=gcc
AR=ar
FLAGS= -Wall -g

all: stringProg
	
stringProg: hw3.o
	$(CC) $(FLAGS) -o stringProg hw3.o
	
hw3.o: hw3.c
	$(CC) $(FLAGS) -c hw3.c
	
.PHONY: all clean

clean:
	rm -f *.o *.a *.so *.gch‬‬ stringProg
