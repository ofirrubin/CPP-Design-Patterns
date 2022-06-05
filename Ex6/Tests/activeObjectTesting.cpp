//
//  ActiveObjectTesting.cpp
//  Ex6
//
//  Created by Ofir Rubin on 04/06/2022.
//

#include "activeObjectTesting.hpp"

void PreWork(void *payload){
    printf("<PREWORK> %s\n", (char *)payload);
}

void PostWork(void *payload){
    char *ptr = (char *)payload; // we have to free the memory since we used enQCopy (and deQ'd them with the activeObject)
    printf("<POSTWORK> %s\n", ptr);
    free(ptr);
}

int main(void){
    Queue *q = new Queue();
    q->enQ_Copy((void *)"hello world", 12);
    ActiveObject active = ActiveObject(&PreWork, &PostWork, q, (char *)"Active object test");
    q->enQ_Copy((void *)"HELLO WORLD", 12);
    q->enQ_Copy((void *)"HELLO world", 12);
    while(!q->IsEmpty())
        sleep(1); // Sleep for 1 sec
    active.destroyAO(); // Assuming that active will clear its inner structures as requested in the question.
    return 0;
}
