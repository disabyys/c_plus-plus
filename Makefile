test.o: test.c
	gcc -c test.c 

test: test.o
	gcc -Wall -Werror -Wextra -o test test.o

clean:
	rm test.o test

run:
	./test