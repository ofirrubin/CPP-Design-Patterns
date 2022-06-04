//
//  main1.cpp
//  Ex6
//
//  Created by Ofir Rubin on 02/06/2022.
//

#include "main1.hpp"

Queue *socket_input;
Queue *cipher_output;
Queue *inverse_output;

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
        cipher_output->enQ(userInput);
}

void inverseCap(void *payload)
{
    struct MetaData *userInput = (struct MetaData *)payload;
    inverseCap(userInput->ptr);
}
void postInverse(void *payload){
    struct MetaData *userInput = (struct MetaData *)payload;
    inverse_output->enQ(userInput);
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
    
ActiveObject *first;
ActiveObject *second;
ActiveObject *last;

void *client_handler(void *args)
{
    int sockfd = *(int *)args;
    // Input variables
    struct MetaData *userInput = (struct MetaData *)calloc(1, sizeof(struct MetaData));
    if (!userInput) // Error allocating data
        return 0;
    userInput->sockfd = sockfd;
    socket_input->enQ(userInput);
    return 0;
}

int main(void) {
    socket_input = new Queue();
    cipher_output = new Queue();
    inverse_output = new Queue();
    
    first = new ActiveObject(&caesarCipher, &postCipher, socket_input,
                                      (char *)"Socket input & Cipher");
    second = new ActiveObject(&inverseCap, &postInverse, cipher_output,
                                       (char *)"Inverse Capital Letters");
    last = new ActiveObject(&sendClient, &postSend, inverse_output,
                                     (char *)"Send to client");
    
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

    printf("DEBUG: Server is waiting for connections...\n");
    handle_forever(sockfd, (char **)&s, client_handler);
    sleep(5);
    
    
    first->destroyAO();
    second->destroyAO();
    free(sa);
    return 0;
}

