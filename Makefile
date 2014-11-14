CC = gcc
CFLAGS= -std=c99 -g -Wall -Werror -Wextra 
LDFLAGS= -lm
EXEC=tsp
#SRC=$(wildcard *.c)
SRC=dynamique.c FloydWarshall.c main.c sortirMinLocaux.c bb.c enum.c \
    generateur_connexe.c glouton.c RechercheLocale.c approx.c
OBJ=$(SRC:.c=.o)


all: $(EXEC)

tsp: $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

approx: approx.o FloydWarshall.o generateur_connexe.o
	$(CC) -o $@ $^ $(LDFLAGS)

test: FloydWarshall.o generateur_connexe.o dynamique.o enum.o glouton.o bb.o gen_graph.o RechercheLocale.o approx.o sortirMinLocaux.o
	$(CC) -o $@ $^ $(LDFLAGS)

dynamique: FloydWarshall.o generateur_connexe.o dynamique.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

enum: FloydWarshall.o generateur_connexe.o enum.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -o $@ -c $< $(LDFLAGS)

clean:
	@rm -rf *.o enum.txt
