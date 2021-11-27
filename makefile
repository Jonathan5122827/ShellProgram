cc = gcc -c -Wall
major2: major2.o cd.o

	gcc -Wall major2.o cd.o -o major2

major2.o: major2.h
	$(cc) major2.c

cd.o: major2.h
	$(cc) cd.c


clean:
	rm *.o
