//
//  ActiveObjectTesting.cpp
//  Ex6
//
//  Created by Ofir Rubin on 04/06/2022.
//

#include "ActiveObjectTesting.hpp"

void PreWork(void *payload){
    printf("<PREWORK> %s\n", (char *)payload);
}

void PostWork(void *payload){
    printf("<POSTWORK> %s\n", (char *)payload);
}

void active_object_test(void){
    Queue *q = new Queue();
    q->enQ_Copy((void *)"hello world", 11);
    ActiveObject active = ActiveObject(&PreWork, &PostWork, q, (char *)"Active object test");
    q->enQ_Copy((void *)"HELLO WORLD", 11);
    q->enQ_Copy((void *)"HELLO WORLD", 11);
    while(!q->IsEmpty())
        sleep(1); // Sleep for 1 sec
    active.destroyAO();
    q->ClearAndFree();
}
