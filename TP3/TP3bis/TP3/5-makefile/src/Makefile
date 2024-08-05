CFLAGS=-Wall -Werror
LIBRARY_PATH = ../libtab

all: main

main: main.o foo.o
	make -C $(LIBRARY_PATH)
	gcc -o main main.o foo.o -L$(LIBRARY_PATH) -ltab

main.o: main.c
	make -C $(LIBRARY_PATH)
	gcc -c main.c $(CFLAGS) -I$(LIBRARY_PATH)

foo.o: foo.c foo.h
	gcc -c foo.c $(CFLAGS)

clean:
	rm main *.o

