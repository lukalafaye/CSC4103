BIN=mysh
LDFLAGS=-lreadline
CFLAGS=-g -Wall

all:$(BIN)

mysh: mysh.o
	$(CC) -o mysh mysh.o $(LDFLAGS)
clean:
	rm -f $(BIN) *.o
