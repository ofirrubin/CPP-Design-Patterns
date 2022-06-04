
#ifndef TCPServer_hpp
#define TCPServer_hpp

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <pthread.h> // Used for threads

#define PORT "3490"  // the port users will be connecting to


int create_server(struct sigaction *sa, char *s[INET_ADDRSTRLEN]);

void reap_dead_processes(struct sigaction *sa);
 
void server_listen(int sockfd, int backlog);

void handle_forever(int sockfd, char *s[INET_ADDRSTRLEN], void *(* f)(void *));

size_t sock_send(const char *respond, size_t size, int sockfd);

void receive(int sockfd, char *buffer, int size_p1, size_t *input_size);

#endif
