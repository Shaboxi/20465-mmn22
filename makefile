myset: myset.o set.o
	gcc -o myset -g -Wall -ansi -pedantic myset.o set.o 

myset.o: myset.c set.h
	gcc -c  -Wall -ansi -pedantic myset.c

set.o: set.c set.h
	gcc -c -Wall -ansi -pedantic set.c

clean:
	rm myset.o set.o myset