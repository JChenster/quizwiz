all: single.o multi.o parse.o
	gcc -o program single.o multi.o parse.o

main.o: main.c single.h multi.h parse.h
	gcc -c main.c

single.o: single.c single.h
	gcc -c single.c

multi.o: multi.c multi.h
	gcc -c multi.c

parse.o: parse.c parse.h
	gcc -c parse.c

run:
	./program

clean:
	rm *.o
	rm program
