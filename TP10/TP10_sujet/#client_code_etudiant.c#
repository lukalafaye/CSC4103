#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "client_code_etudiant.h"

/* receive a message and process it */
void receive_message(FILE* server_file) {
  /* an incoming message is available */
  char buff_in[1024];

  /* receive a message */
  if(fgets(buff_in, sizeof(buff_in), server_file) == NULL) {
    perror("fgets failed");
    abort();
  }

  /* process the message */
  process_incoming_message(server_file, buff_in);
}

/* process a received message */
void process_incoming_message(FILE*server_file, char* cmd) {
  /* first, erase the current line */
  printf("%c[2K", 27);
  printf("%s", cmd);
}

/* send a message */
void send_message(FILE* server_file, char*cmd) {
  if(strlen(cmd) > 0) {
    fwrite(cmd, sizeof(char), strlen(cmd), server_file);
  }
}

/* process and send a command */
void process_outgoing_message(FILE* server_file, char*cmd) {
  send_message(server_file, cmd);
}

void close_connection(FILE* server_file) {
  fclose(server_file);
}
