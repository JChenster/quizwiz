all: single.o parse.o
	gcc -o program single.o parse.o

single.o: single.c single.h
	gcc -c single.c

parse.o: parse.c parse.h
	gcc -c parse.c

run:
	./program

clean:
	rm *.o
	rm program
