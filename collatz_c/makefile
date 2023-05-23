CC = gcc
CFLAGS = -Wall -Wextra

all: collatz_proof collatz_verif

collatz_proof: collatz_proof.o
	$(CC) $(CFLAGS) -o $@ $^

collatz_verif: collatz_verif.o
	$(CC) $(CFLAGS) -o $@ $^

collatz_proof.o: collatz_proof.c
collatz_verif.o: collatz_verif.c

clean:
	rm -f *.o

fclean: clean
	rm -f collatz_proof collatz_verif

.PHONY: all clean fclean

