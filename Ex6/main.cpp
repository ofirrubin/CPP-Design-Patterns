//
//  main.cpp
//  Ex6
//
//  Created by Ofir Rubin on 30/05/2022.
//

#include <iostream>

#include "Queue.hpp"
#include "ActiveObject.hpp"

#include <unistd.h>
#include "TCPServer.hpp"


#define BACKLOG 10
#define MAXINPUT 1024

using std::cout;
using std::endl;
using std::string;

struct MetaData{ // Who it belongs and what's its address
    int sockfd;
    char *ptr;
};

Queue socket_input = Queue();
Queue cipher_output = Queue();
Queue inverse_output = Queue();

// HELPERS
int charStatus(char c){
    if (c >= 'a' && c <= 'z') return 0;
    else if (c >= 'A' && c <= 'Z') return 1;
    return -1;
}

void caesarCipher(char *ptr){
    // CaesarCipher
    int size = 26; // NUMBER OF ALPHABET LETTERS
    char c; // first letter index (of small/capital letter)
    for (int i = 0; ptr[i] != 0; i++)
    {
        switch (charStatus(ptr[i])) {
            case 0:
                c = 'a';
                break;
            case 1:
                c = 'A';
                break;
            default:
                continue;
        }
        ptr[i] = c + (ptr[i] - c + 1) % size;
    }
}

void inverseCap(char *ptr){
    int aToA = 'A' - 'a';
    int Atoa = 'a' - 'A';
        
    for (int i = 0; ptr[i] != 0; i++)
    {
        switch (charStatus(ptr[i])) {
            case 0:
                ptr[i] += aToA;
                break;
            case 1:
                ptr[i] += Atoa;
                break;
            default:
                continue;
        }
    }
}

// END HELPERS

void caesarCipher(void *payload)
{
    struct MetaData *userInput = (struct MetaData *)payload;
    userInput->ptr = (char *)calloc(1, MAXINPUT + 1);
    if (! userInput->ptr){
        printf("Error mallocating for user input!\n");
        return; // We can't do much
    }
    size_t size;
    receive(userInput->sockfd, userInput->ptr, MAX_INPUT + 1, &size);
    if (size > 0)
        caesarCipher(userInput->ptr);
    else
    {
        free(userInput->ptr);
        userInput->ptr = NULL;
    }
}

void postCipher(void *payload)
{
    struct MetaData *userInput = (struct MetaData *)payload;
    if (userInput->ptr)
        cipher_output.enQ(userInput);
}

void inverseCap(void *payload)
{
    struct MetaData *userInput = (struct MetaData *)payload;
    inverseCap(userInput->ptr);
}
void postInverse(void *payload){
    struct MetaData *userInput = (struct MetaData *)payload;
    inverse_output.enQ(userInput);
}

void sendClient(void *payload){
    struct MetaData *userInput = (struct MetaData *)payload;
    sock_send(userInput->ptr, strlen(userInput->ptr), userInput->sockfd);
    
}
void postSend(void *payload){
    struct MetaData *userInput = (struct MetaData *)payload;
    close(userInput->sockfd); // Close connecion to the client
    free(userInput->ptr); // Free user input/output
    free(userInput); // Free struct
}
    
ActiveObject first = ActiveObject(&caesarCipher, &postCipher, &socket_input);
ActiveObject second = ActiveObject(&inverseCap, &postInverse, &cipher_output);
ActiveObject last = ActiveObject(&sendClient, &postSend, &inverse_output);

void *client_handler(void *args)
{
    int sockfd = *(int *)args;
    // Input variables
    struct MetaData *userInput = (struct MetaData *)calloc(1, sizeof(struct MetaData));
    if (!userInput) // Error allocating data
        return 0;
    userInput->sockfd = sockfd;
    socket_input.enQ(userInput);
    return 0;
}

int main(void) {
    struct sigaction *sa = (struct sigaction *)calloc(sizeof(struct sigaction), 1);
    char s[INET_ADDRSTRLEN];
    
    // Create and bind server socket
    int sockfd = create_server(sa, (char **)&s);
    if (sockfd <= 0 )
    {
        printf("Error creating socket\n");
    }
    // Listen to the server
    server_listen(sockfd, BACKLOG);
    // Reap dead processes
    reap_dead_processes(sa);

    printf("server: waiting for connections...\n");
    handle_forever(sockfd, (char **)&s, client_handler);
    sleep(5);
    
    
    first.destroyAO();
    second.destroyAO();
    free(sa);
    return 0;
}
