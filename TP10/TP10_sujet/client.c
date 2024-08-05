#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <poll.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#include "client_code_etudiant.h"

/* connect to a server */
FILE* connect_to_server(char* ip_addr, int port){
  FILE*server_file = NULL;
  struct sockaddr_in serv_addr;
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if( sock < 0){
    perror("socket failed");
    abort();
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(port);
  if(inet_pton(AF_INET, ip_addr, &serv_addr.sin_addr)<=0) {
      perror("inet_pton failed\n");
      abort();
  }

  if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
    perror("connect failed");
    abort();
  }

  server_file = fdopen(sock, "r+");
  if(!server_file) {
    perror("fdopen failed");
    abort();
  }
  setbuf(server_file, NULL);

  pid_t pid = getpid();
  write(sock, &pid, sizeof(pid_t));

  /* the server should say hello */
  receive_message(server_file);

  return server_file;
}

int main(int argc, char**argv) {

  if(argc != 3) {
    fprintf(stderr, "Usage: %s IP_ADDRESS PORT\n", argv[0]);
    return EXIT_FAILURE;
  }

  FILE* server_file = connect_to_server(argv[1], atoi(argv[2]));

  struct pollfd *fds=malloc(sizeof(struct pollfd)*2);
  fds[0].fd = fileno(server_file);
  fds[0].events = POLLIN;

  fds[1].fd = STDIN_FILENO;
  fds[1].events = POLLIN;

  while(1){
    /* wait for any event (from stdin, or from the server) */
    printf("(chatroom) $ ");
    fflush(stdout);
    int poll_res = poll( fds, 2, -1);
    if(poll_res < 0) {
      perror("poll failed");
      abort();
    }
    if(fds[0].revents != 0) {
      /* message from the server */
      printf("\r");
      receive_message(server_file);

    } else if (fds[1].revents != 0) {
      /* command from the keyboard */
      char cmd[1024];
      memset(cmd, 0, 1024*sizeof(char));
      if(fgets(cmd, 1024, stdin) == NULL) {
	perror("fgets failed");
	abort();
      }
      process_outgoing_message(server_file, cmd);
    }
  }

  close_connection(server_file);
  return EXIT_SUCCESS;
}


