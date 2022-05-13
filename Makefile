CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror
EXEC = pruebas
CC = gcc

VFLAGS = --leak-check=full --track-origins=yes --show-reachable=yes
CFILES = *.c

all:
	$(CC) $(CFLAGS) -o $(EXEC) $(CFILES)

run: all
	clear
	./$(EXEC)

valgrind: all
	valgrind $(VFLAGS) ./$(EXEC)
