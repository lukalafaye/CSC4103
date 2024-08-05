CFLAGS = -Wall -Werror
LIBRARY_PATH = ../libtab

executable: main.o foo.o | libtab.so
	gcc -o executable main.o foo.o

main.o: main.c | libtab.so
	make -C ../libtab
	gcc $(CFLAGS) -c main.c -I$(LIBRARY_PATH)

foo.o: foo.c
	gcc $(CFLAGS) -c foo.c

libtab.so:
	make -C $(LIBRARY_PATH)

clean:
	rm -f executable *.o
