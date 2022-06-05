//
//  PollServer.hpp
//  Ex6
//
//  Created by Ofir Rubin on 02/06/2022.
//

#ifndef PollServer_hpp
#define PollServer_hpp

#include <stdio.h>
#include <string.h> // for memset
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>

#include <sys/types.h>
#include <netdb.h>
#define MAXFDS 200 // This is also listen size, there is no need to create larger poll size since listen will ignore incoming requests (overflow)

#define SERVER_PORT  3490

#define TRUE             1
#define FALSE            0

int start_server();

#endif /* PollServer_hpp */
