CFLAGS=-Wall -Werror -fPIC

all: libtab.so

libtab.so: tab.o
	gcc -shared -o libtab.so tab.o

tab.o: tab.c tab.h
	gcc -c tab.c $(CFLAGS)

clean:
	rm tab *.o
