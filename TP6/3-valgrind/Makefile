CC	= gcc
CFLAGS	= -g -Wall -O0
LDFLAGS = -lm
BIN	= nbody overflow

all: $(BIN)

nbody: nbody.o
	$(CC) -o $@ $< $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(BIN)
