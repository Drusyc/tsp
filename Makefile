CC = gcc

CFLAGS= -std=c99 -g -Wall -Werror -Wextra 
LDFLAGS= -lm
EXEC=tsp
SRC=$(wildcard *.c)
OBJ=$(SRC:.c=.o)


all: $(EXEC)

tsp: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

dynamique: FloydWarshall.o generateur_connexe.o dynamique.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

enum: FloydWarshall.o generateur_connexe.o enum.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

clean:
	rm -rf *.o 
