make: random-walk.c
	gcc -Wall -Werror -o random-walk random-walk.c -lm

clean:
	rm random-walk random-walk.c
