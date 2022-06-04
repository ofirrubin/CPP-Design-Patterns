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


#define SERVER_PORT  12345

#define TRUE             1
#define FALSE            0

int start_server();

#endif /* PollServer_hpp */
