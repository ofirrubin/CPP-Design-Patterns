//
//  main.cpp
//  Ex6
//
//  Created by Ofir Rubin on 30/05/2022.
//

#include <iostream>
#include "Mutex.hpp"
#include "pthread.h"
#include <stdio.h>
#include <unistd.h>

#include "Queue.hpp"
#include "ActiveObject.hpp"
//#include "QueueTest.h"

using std::cout;
using std::endl;
using std::string;

void prework(void *payload)
{
    printf("Prework %s\n", (char *)payload);
}

void postwork(void *payload)
{
    printf("Postwork %s\n", (char *)payload);
}

int main(void) {
    //queue_test();
    Queue t = Queue(true);
    t.enQ((void *)"1");
    t.enQ((void *)"2");
    t.enQ((void *)"3");
    t.enQ((void *)"4");
    t.enQ((void *)"5");
    t.enQ((void *)"7");
    ActiveObject a = ActiveObject(&prework, &postwork, &t);
    sleep(5);
    t.enQ((void *)"afterwork");
    return 0;
}
