#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "server_code_etudiant.h"

int cli_count = 0;

#ifdef CLIENT_LIST
/* use a linked list to store clients */
struct list {
  client_t* client;
  struct list*next;
};

struct list* clients = NULL;
#else
/* use an array to store clients */
client_t *clients[MAX_CLIENTS];
#endif

/* Strip CRLF */
void strip_newline(char *s) {
  while(*s != '\0'){
    if(*s == '\r' || *s == '\n'){
      *s = '\0';
    }
    s++;
  }
}

client_t *get_client_from_fd(int fd) {
#ifdef CLIENT_LIST
  struct list* l = clients;
  while(l) {
    if(l->client->fd == fd)
      return l->client;
    l = l->next;
  }
#else
  int i;
  for(i=0; i<MAX_CLIENTS; i++) {
    if(clients[i]->fd == fd)
      return clients[i];
  }
#endif
  return NULL;
}

client_t *get_client_from_name(char* name) {
#ifdef CLIENT_LIST
    struct list* l = clients;
  while(l) {
    if(strcmp(l->client->name, name) == 0)
      return l->client;
    l = l->next;
  }
#else
  int i;
  for(i=0; i<MAX_CLIENTS; i++) {
    if(clients[i]) {
      if(strcmp(clients[i]->name, name) == 0) {
	return clients[i];
      }
    }
  }
#endif
  return NULL;
}

void server_init() {
#ifdef CLIENT_LIST
  clients = NULL;
#else
  memset(clients, 0, sizeof(client_t*)*MAX_CLIENTS);
#endif
}

/* Add client to queue */
void queue_add(client_t *cl){
#ifdef CLIENT_LIST
  struct list* l = malloc(sizeof(struct list));
  l->next = clients;
  l->client = cl;
  clients = l;
#else
  int i;
  for(i=0;i<MAX_CLIENTS;i++){
    if(!clients[i]){
      clients[i] = cl;
      return;
    }
  }
#endif
}

/* Delete client from queue */
void queue_delete(client_t *client){
#ifdef LINKED_LIST
  struct list**l = &clients;
  while(*l  && (*l)->client != client) {
    l = &((*l)->next);
  }
  struct list* p_client = *l;
  *l = p_client->next;
  free(p_client);
#else
  int i;
  for(i=0;i<MAX_CLIENTS;i++){
    if(clients[i]){
      if(clients[i]->uid == client->uid){
	clients[i] = NULL;
	return;
      }
    }
  }
#endif
}

/* Send a message to a client */
void send_message(char *s, client_t *client){
  fwrite(s, sizeof(char), strlen(s), client->client_conn);
}

/* Send message to all clients */
void send_message_all(char *s){
#ifdef CLIENT_LIST
  struct list* l = clients;
  while(l) {
    send_message(s, l->client);
    l = l->next;
  }
#else
  int i;
  for(i=0;i<MAX_CLIENTS;i++){
    if(clients[i]){
      send_message(s, clients[i]);
    }
  }
#endif
  log_message(s);
}

void assign_default_name(client_t* cli) {
  sprintf(cli->name, "Anonymous_%d", cli->uid);
}

void say_hello(client_t *cli) {
  char buff_out[1024];
  /* choose a default name */
  assign_default_name(cli);
  sprintf(buff_out, "* %s joins the chatroom\n", cli->name);
  send_message_all(buff_out);
}


void process_cmd_msg(client_t*client,
		     char*param) {
  char*dest = strsep(&param, " ");
  if(!dest){
    send_message("* to who ?\n", client);
    return;
  }

  char buffer[1024];
  sprintf(buffer, "[PM][%s --> %s] %s\n", client->name, dest, param);
  client_t* to = get_client_from_name(dest);
  if(!to ){
    send_message("* %s does not exist!\n", client);
  } else {
    send_message(buffer, to);
    send_message(buffer, client);
  }
}

void process_cmd_help(client_t* client) {
  char buff_out[1024];
  sprintf(buff_out, "/help     Show help\n");
  strcat(buff_out, "/msg      <name> <message> Send private message\n");
  strcat(buff_out, "/ping     Server test\n");
  strcat(buff_out, "/quit     Quit chatroom\n");
  send_message(buff_out, client);
}

void process_cmd_ping(client_t* client,
		      char* param) {
  send_message("* pong\n", client);
}

void handle_incoming_cmd(client_t *cli) {
  char buff_out[1024];
  char buff_in[1024];

  if(fgets(buff_in, 1024*sizeof(char), cli->client_conn) == 0) {
    if(!feof(cli->client_conn)) {
      perror("read failed");
      abort();
    } else {
      printf("Client %s disconnected\n", cli->name);
      queue_delete(cli);
      return;
    }
  }

  strip_newline(buff_in);

  /* Ignore empty buffer */
  if(!strlen(buff_in)){
    printf("Empty message\n");
  }

  /* Special options */
  char *cmd_line = buff_in;
  if(buff_in[0] == '/'){
    char *command;
    command = strsep(&cmd_line," ");
    if(!strcmp(command, "/quit")){
      return;
    } else if(!strcmp(command, "/ping")) {
      process_cmd_ping(cli, cmd_line);
    } else if(!strcmp(command, "/msg")) {
      process_cmd_msg(cli, cmd_line);
    } else {
      /* /help or unknown command */
      process_cmd_help(cli);
    }
  }else{
    /* Send message */
    sprintf(buff_out, "[%s] %s\n", cli->name, cmd_line);
    send_message_all(buff_out);
  }
}
