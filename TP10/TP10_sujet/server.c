/*
 * Copyright 2014
 *
 * Author: 		Dinux
 * Description:		Simple chatroom in C
 * Version:		1.0
 *
 * Code adapted by François TRAHAY <francois.trahay@telecom-sudparis.eu>
 * (TELECOM SudParis) for CSC4103 2016 lab
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <poll.h>

#include "server_code_etudiant.h"

/* next client identifier */
static int uid = 10;
int cli_count = 0;

/* Print ip address */
void print_client_addr(struct sockaddr_in addr){
  printf("%d.%d.%d.%d",
	 addr.sin_addr.s_addr & 0xFF,
	 (addr.sin_addr.s_addr & 0xFF00)>>8,
	 (addr.sin_addr.s_addr & 0xFF0000)>>16,
	 (addr.sin_addr.s_addr & 0xFF000000)>>24);
}


client_t* handle_accept(int listenfd) {
  struct sockaddr_in cli_addr;
  socklen_t clilen = sizeof(cli_addr);

  int connfd = accept(listenfd, (struct sockaddr*)&cli_addr, &clilen);

  /* Check if max clients is reached */
  if((cli_count+1) == MAX_CLIENTS){
    printf("<<MAX CLIENTS REACHED\n");
    printf("<<REJECT ");
    print_client_addr(cli_addr);
    printf("\n");
    close(connfd);
    return NULL;
  }

  /* Client settings */
  client_t *cli = (client_t *)malloc(sizeof(client_t));
  cli->addr = cli_addr;
  cli->fd = connfd;
  cli->client_conn = fdopen(cli->fd, "w+");
  if(cli->client_conn == NULL) {
    perror("fdopen failed");
    abort();
  }
  /* disable buffering on this file handle */
  setbuf(cli->client_conn, NULL);

  cli->uid = uid++;
  sprintf(cli->name, "%d", cli->uid);

  read(cli->fd, &cli->pid, sizeof(pid_t));

  /* Add client to the queue and fork thread */
  queue_add(cli);
  return cli;
}


int main(int argc, char**argv) {
  int listenfd = 0;
  struct sockaddr_in serv_addr;

  server_init();

  srand(time(NULL));
  /* Socket settings */
  listenfd = socket(AF_INET, SOCK_STREAM, 0);
  if(listenfd < 0) {
    perror("socket failed");
    abort();
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
  serv_addr.sin_port = htons(5000);

  int on = 1;
  if(setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0) {
    perror("setsockopt failed");
    return 1;
  }

  /* Bind */
  if(bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0){
    perror("Socket binding failed");
    return 1;
  }

  /* Listen */
  if(listen(listenfd, 10) < 0){
    perror("Socket listening failed");
    return 1;
  }

  printf("<[SERVER STARTED]>\n");
  printf("To connect to this server, run:\n\tclient 127.0.0.1 5000\n");
  /* Accept clients */
  struct pollfd *fds = malloc(sizeof(struct pollfd)*(cli_count+1));
  fds[0].fd = listenfd;
  fds[0].events = POLLIN;

  while(1){

    int poll_res = poll( fds, cli_count+1, -1);
    if(poll_res < 0) {
      perror("poll failed");
      abort();
    }
    int i;
    for(i=0; i<cli_count+1; i++) {
      if(fds[i].revents != 0) {
	if(fds[i].fd == listenfd) {
	  printf("New connection\n");
	  /* this is a new connection */
	  client_t*cli = handle_accept(listenfd);
	  if(!cli) {
	    perror("accept failed");
	    abort();
	  }
	  cli_count++;
	  fds = realloc(fds, sizeof(struct pollfd)*(cli_count+1));
	  fds[cli_count].fd = cli->fd;
	  fds[cli_count].events = POLLIN;

	  say_hello(cli);
	} else {
	  if(fds[i].revents & POLLHUP) {
	    /* client disconnect */
	    printf("HUP bit is set\n");
	    /* ignore this fd from now on */
	    fds[i].fd = -1;
	  } else {
	    if(fds[i].revents & POLLERR) {
	      printf("ERR bit is set\n");
	    }
	    if(fds[i].revents & POLLNVAL) {
	      printf("NVAL bit is set\n");
	    }

	    client_t* client = get_client_from_fd(fds[i].fd);
	    if(client) {
	      handle_incoming_cmd(client);
	    } else {
	      /* probably a disconnected client */
	      fds[i].fd = -1;
	    }
	  }
	}
      }
    }
  }
}
