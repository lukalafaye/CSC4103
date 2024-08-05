#ifndef CLIENT_CODE_ETUDIANT_H
#define CLIENT_CODE_ETUDIANT_H
#include <stdio.h>

void receive_message(FILE* server_file);
void process_incoming_message(FILE*server_file, char* cmd);

void send_message(FILE* server_file, char*cmd);
void process_outgoing_message(FILE* server_file, char*cmd);
void close_connection(FILE* server_file);

#endif	/* CLIENT_CODE_ETUDIANT_H */
