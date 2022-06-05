//
//  ReactorServer.hpp
//  Ex6
//
//  Created by Ofir Rubin on 02/06/2022.
//

#ifndef ReactorServer_hpp
#define ReactorServer_hpp

#include <stdio.h>

#include <stdio.h>
#include <string.h> // for memset
#include <stdlib.h>

#include <sys/ioctl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>

#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <unistd.h>

#include "Reactor.hpp"

#define SERVER_PORT  3490

#define MAXFDS 200 // This is also listen size, there is no need to create larger poll size since listen will ignore incoming requests (overflow)

int start_reactor_server();

#endif /* ReactorServer_hpp */
