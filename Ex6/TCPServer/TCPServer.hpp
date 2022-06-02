
#ifndef TCPServer_hpp
#define TCPServer_hpp

int INET_ADDRSTRLEN;

int create_server(struct sigaction *sa, char *s[INET_ADDRSTRLEN]);

void reap_dead_processes(struct sigaction *sa);
 
void server_listen(int sockfd, int backlog);

void handle_forever(int sockfd, char *s[INET_ADDRSTRLEN], void *(* f)(void *));

int sock_send(const char *respond, size_t size, int sockfd);

int receive(int sockfd, char *buffer, int size_p1, size_t *input_size);

#endif
