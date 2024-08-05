BIN=client server

CFLAGS=-Wall -Werror -g

all: $(BIN)

client: client.o server_code_etudiant.o
	gcc -o client client.o server_code_etudiant.o $(LDFLAGS)

server:
	gcc -o server server.o server_code_etudiant.o $(LDFLAGS)

client.o: client.c
	gcc -c client.c $(CFLAGS) 

server.o: server.c
	gcc -c server.c $(CFLAGS)

client_code_etudiant.o: client_code_etudiant.c
	gcc -c client_code_etudiant.c $(CFLAGS)

server_code_etudiant.o: server_code_etudiant.c
	gcc -c server_code_etudiant.c $(CFLAGS)

clean:
	rm -rf $(BIN) *.o

