//
//  Reactor.hpp
//  Ex6
//
//  Created by Ofir Rubin on 01/06/2022.
//

#ifndef Reactor_hpp
#define Reactor_hpp

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

#include "Guard.hpp"
#include "Queue.hpp"
#include "Guard.hpp"

#include <sys/poll.h>
#include <map>

#define MAXPOLL 200

// The idea is based on: http://www.dre.vanderbilt.edu/~schmidt/PDF/reactor-siemens.pdf
// But handler is'nt an object here, we use fd & void functions as handlers.
// In addition we also allow multithreading by protecting with mutex.


class Reactor{
private:
    int numPolls = 0;
    struct pollfd fds[MAXPOLL];
    Mutex *mutex;
    
    std::map<int, void (*)(void *)> handlers; // Handlers map
    void (*defaultHandler)(void *pointer);
    
public:
    Reactor(void (*defaultHandler)(void *ptr) = NULL);
    bool InstallHandler(int fd, void (*Handler)(void *pollfd_ptr));
    bool RemoveHandler(int fd);
    void SetPullIn(struct pollfd *ptr, int fd, bool isRequest);
    struct pollfd * AddPullIn(int fd, bool isRequest);
    void MarkHandled(struct pollfd *ptr);
    void EventLoop(int listen_sd);
};

#endif /* Reactor_hpp */
