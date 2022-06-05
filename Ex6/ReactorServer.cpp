//
//  ReactorServer.cpp
//  Ex6
//
//  Created by Ofir Rubin on 02/06/2022.
//

#include "ReactorServer.hpp"
#include "Reactor.hpp"
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define MAXFDS 200 // This is also listen size, there is no need to create larger poll size since listen will ignore incoming requests (overflow)
#define SOCKET_READ_TIMEOUT_SEC 1

Reactor *reactor;

void ClientHandler(void *pfd){
    signed long rc;
    struct pollfd *ptr = (struct pollfd *)pfd;
    const size_t bufferSize = 80;
    char buffer[bufferSize];
    
    memset(buffer, 0, bufferSize);
    if ((rc=recv(ptr->fd, buffer, sizeof(buffer), 0)) > 0) //
    { // We got data
        rc = rc > bufferSize ? bufferSize : rc; // Make sure the size is in array bounds.
        printf("Received: %s\n", buffer);
        if (strcmp(buffer, "exit\n") == true || (rc = send(ptr->fd, buffer, rc, 0)) < 0) // Close connection or
        {
            printf("Either exit or error sending...\n");
        }
    }
    else if (rc == 0){
        printf("Closing connection since rc is 0\n");
    }
    close(ptr->fd);
    reactor->MarkHandled(ptr);
}


void AcceptClients(void *p){
    int new_sd;
    int listen_sd = ((struct pollfd *)p) -> fd;
    do
    {
        new_sd = accept(listen_sd, NULL, NULL);
        if (new_sd < 0)
        {
            if (errno != EWOULDBLOCK)
            {
                throw std::runtime_error("Error occured! EWOULDBLOCK at accept");
            }
            return;
        }
        printf("  Adding new client into handlers list... %d\n", new_sd);
        reactor->AddPullIn(new_sd, false);
    } while (new_sd != -1);
}

int start_reactor_server () // Mixed beejs idea with https://www.ibm.com/docs/en/i/7.4?topic=designs-using-poll-instead-select
{
    size_t rc;
    int    on = 1; // Enable socket reuse
    int    listen_sd = -1;
    struct sockaddr_in   addr;
    
    // IPv4
    if ((listen_sd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket() failed");
        exit(-1);
    }
    
    // Allow reusable
    if ((rc = setsockopt(listen_sd, SOL_SOCKET,  SO_REUSEADDR,
                         (char *)&on, sizeof(on))) < 0)
    {
        perror("setsockopt() failed");
        close(listen_sd);
        exit(-1);
    }
    
    // Make nonblocking accept (because we use poll)
    if ((rc = ioctl(listen_sd, FIONBIO, (char *)&on)) < 0)
    {
        perror("ioctl() failed");
        close(listen_sd);
        exit(-1);
    }
    
    // Bind socket
    memset(&addr, 0, sizeof(addr));
    addr.sin_family      = AF_INET;
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    addr.sin_port        = htons(SERVER_PORT);
    rc = bind(listen_sd, (struct sockaddr *)&addr, sizeof(addr));
    if (rc < 0)
    {
        perror("bind() failed");
        close(listen_sd);
        exit(-1);
    }
    // Start listenning..
    rc = listen(listen_sd, MAXFDS);
    if (rc < 0)
    {
        perror("listen() failed");
        close(listen_sd);
        exit(-1);
    }
    reactor = new Reactor(ClientHandler); // Default handler is client handler
    reactor->AddPullIn(listen_sd, false);
    reactor->InstallHandler(listen_sd, AcceptClients);
    reactor->EventLoop(listen_sd);
    return 0;
}
