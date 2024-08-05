#ifndef SERVER_CODE_ETUDIANT_H
#define SERVER_CODE_ETUDIANT_H

#include <arpa/inet.h>
#include <stdio.h>

#define MAX_CLIENTS 100
#define NAME_MAX_LENGTH 32
/* Client structure */
typedef struct {
  struct sockaddr_in addr;	/* Client remote address */
  FILE *client_conn;		/* Connection file handle */
  int uid;			/* Client unique identifier */
  char name[NAME_MAX_LENGTH];		/* Client name */
  pid_t pid;			/* PID of the client */
  int fd;			/* Client file descriptor */
} client_t;

/* number of connected clients */
extern int cli_count;

/* initialize stuff */
void server_init();
/* finalize stuff */
void server_finalize(int signo);

/* return the connected client whose fd is fd */
client_t *get_client_from_fd(int fd);
/* add a client to the list of connected clients */
void queue_add(client_t *cl);
/* remove a client from the list of connected clients */
void queue_delete(client_t *cl);

/* Send a message to a client */
void send_message(char *s, client_t *client);
/* send a message to all clients */
void send_message_all(char *s);

/* Send message to sender */
//void send_message_self(const char *s, FILE* client_conn);
/* Send message to client */
void send_message_client(char *s, int uid);
/* Send list of active clients */
void send_active_clients(client_t*client);

/* initiate a connexion */
void say_hello(client_t *cli);
/* process an incoming message from a client */
void handle_incoming_cmd(client_t *cli);

#endif	/* SERVER_CODE_ETUDIANT_H */
