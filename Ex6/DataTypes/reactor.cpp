//
//  Reactor.cpp
//  Ex6
//
//  Created by Ofir Rubin on 01/06/2022.
//

#include "reactor.hpp"
#include <sys/socket.h>
bool end_server = false;

Reactor::Reactor(void (*defaultHandler)(void *)){
    mutex = new Mutex();
    if (defaultHandler)
        this->defaultHandler = defaultHandler;
    memset(fds, 0 , sizeof(fds)); // Set poll
}


bool Reactor::InstallHandler(int fd, void (*Handler)(void *)){
    if (handlers.count(fd) > 0)
        return false;
    else
        handlers.insert(std::pair<int, void (*)(void *)>(fd, Handler));
    return true;
}

bool Reactor::RemoveHandler(int fd){
    return handlers.erase(fd);
}


void Reactor::EventLoop(int listen_sd){
    int current_size, i;
    do
    {
        printf("Waiting on poll()...\n");
        if (poll(fds, numPolls, -1) < 0)
            throw std::runtime_error("poll() returned value is lower than 0!");
        mutex->Aquire();
        current_size = numPolls > MAXPOLL ? MAXPOLL: numPolls;
        mutex->Free();
        for (i = 0; i < current_size; i++)
        {
            
            if(fds[i].revents == 0) // Skip unset
                continue;
            
            if(fds[i].revents != POLLIN) // Unkown value (unexpected)
            {
                printf("ERROR: Reactor got revents = %d\n", fds[i].revents);
                end_server = true;
                break;
                
            }
            if (handlers.count(fds[i].fd) > 0) // Going to outer accept
                handlers.find(fds[i].fd)->second(&fds[i]);
            else if (defaultHandler)
                defaultHandler(&fds[i]);
        }
        
    } while (end_server == false); /* End of serving running.    */
}


struct pollfd *Reactor::AddPullIn(int fd, bool isRequest){
    mutex->ScopeLock();
    if (numPolls > MAXPOLL)
        return NULL;
    SetPullIn(&fds[numPolls], fd, isRequest);
    numPolls += 1;
    return &fds[numPolls - 1]; // lazy me
}

void Reactor::SetPullIn(struct pollfd* ptr, int fd, bool isRequest){
    ptr->fd = fd;
    if (isRequest) // I know it might be both but for this server case I only need events
        ptr->revents = POLLIN;
    else
        ptr->events = POLLIN;
}

void Reactor::MarkHandled(struct pollfd *ptr){
    mutex->ScopeLock();
    ptr->fd = 0;
    numPolls --;
}
