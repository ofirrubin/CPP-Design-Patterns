//
//  PollServer.cpp
//  Ex6
//
//  Created by Ofir Rubin on 02/06/2022.
//

#include "pollServer.hpp"

bool endServer = false;

void AcceptClients(int listen_sd, int *nfds, struct pollfd fds[MAXFDS]){
    int new_sd;
    do
    {
        new_sd = accept(listen_sd, NULL, NULL);
        if (new_sd < 0)
        {
            if (errno != EWOULDBLOCK)
            {
                perror("accept() failed");
                endServer = true;
            }
            break;
        }

        printf("  New incoming connection - %d\n", new_sd);
        fds[*nfds].fd = new_sd;
        fds[*nfds].events = POLLIN;
        (*nfds)++;
    } while (new_sd != -1);
}

bool ClientHandler(struct pollfd *current){
    signed long rc, len;
    bool close_conn = false;
    const size_t bufferSize = 1024;
    char buffer[bufferSize];
    memset(buffer, 0, bufferSize);
    do
    {
        rc = recv(current->fd, buffer, sizeof(buffer), 0);
        if (rc <= 0)
        {
            if (rc == 0)
                printf("ERROR: Receive error\n");
            close_conn = true;
            break;
        }
        // We got data
        len = rc;
        if (len > bufferSize)
            len = bufferSize;
        printf("  %zu bytes received: %s\n", len, buffer);
        // Echo back the data
        rc = send(current->fd, buffer, len, 0);
        if (rc < 0)
        {
            perror("  send() failed");
            close_conn = true;
        }
        
    } while(!close_conn);
    
    close(current->fd);
    current->fd = -1;
    return true;
}

void compress_arr(struct pollfd fds[MAXFDS], int nfds){
    for (int i = 0; i < nfds; i++)
    {
        if (fds[i].fd == -1)
        {
            for(int j = i; j < nfds-1; j++)
            {
                fds[j].fd = fds[j+1].fd;
            }
            i--;
            nfds--;
        }
    }

}

int start_server () // Mixed beejs idea with https://www.ibm.com/docs/en/i/7.4?topic=designs-using-poll-instead-select
{
    size_t rc;
    int    on = 1; // Enable socket reuse
    int    listen_sd = -1; // Server socket
    int    end_server = false, compress_array = false;
    struct sockaddr_in   addr;
    struct pollfd fds[MAXFDS];
    int    nfds = 1, current_size = 0, i;
    
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

    //Initialize poll
    memset(fds, 0 , sizeof(fds));
    // Set first element in poll so we will start accepting clients (it will update the list of fds)
    fds[0].fd = listen_sd;
    fds[0].events = POLLIN; // Input
    do
    {
        printf("Waiting on poll()...\n");
        rc = poll(fds, nfds, -1);
        // Check if poll failed
        if (rc < 0)
        {
            perror("  poll() failed");
            break;
        }
        // Check if timed out... (we are not suppose to get it as -1 is no timeout.
        if (rc == 0)
        {
            printf("  poll() timed out.  End program.\n");
            break;
        }
        
        current_size = nfds;
        for (i = 0; i < current_size; i++)
        {
            
            if(fds[i].revents == 0) // Skip unset
                continue;
            
            if(fds[i].revents != POLLIN) // Unkown value (unexpected)
            {
                printf("  Error! revents = %d\n", fds[i].revents);
                end_server = true;
                break;
                
            }
            if (fds[i].fd == listen_sd) // This is the first element we entered so we will accept clients; Reminder: inner acept() is non blocking!
            {
                printf("  Listening socket is readable\n");
                AcceptClients(listen_sd, &nfds, fds);
            }
            else
            {
                printf("  Descriptor %d is readable\n", fds[i].fd);
                // Client handling
                compress_array = ClientHandler(&fds[i]);
            }
        }
        
        // Remove handled users from the array
        if (compress_array)
        {
            compress_array = false;
            compress_arr(fds, nfds);
        }
        
    } while (end_server == FALSE); /* End of serving running.    */
   
    for (i = 0; i < nfds; i++)
    {
        if(fds[i].fd >= 0)
            close(fds[i].fd);
    }
    return 0;
}
