all: interface.o multi.o single.o parse.o
	gcc -o program interface.o multi.o single.o parse.o

interface.o: interface.c interface.h
	gcc -c interface.c

multi.o: multi.c multi.h
	gcc -c multi.c

single.o: single.c single.h
	gcc -c single.c

parse.o: parse.c parse.h
	gcc -c parse.c

run:
	./program

clean:
	rm *.o
	rm program
