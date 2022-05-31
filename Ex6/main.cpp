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

using std::cout;
using std::endl;
using std::string;

static Queue t = new Queue(true);

void *tFunc(void *parm)
{
    cout << (char *)t.deQ() << endl;
    return (void *)0;
}

int main(void) {
    t.enQ((void *)"1");
    t.enQ((void *)"2");
    t.enQ((void *)"3");
    t.enQ((void *)"4");
    t.enQ((void *)"5");
    t.enQ((void *)"7");
    int i, rc, numThreads = 8;
    pthread_t threadid[numThreads];

    printf("Create %d threads\n", numThreads);
    for(i=0; i<numThreads; ++i) {
        rc = pthread_create(&threadid[i], NULL, tFunc, NULL);
        if (rc != 0)
            cout << "pthread_create() "<<  rc;
    }

    sleep(5); // Push is actually signalling
    t.enQ((void *)"6");
    t.enQ((void *)"Last item!");
    
    printf("Wait for threads\n");
    for (i=0; i<numThreads; ++i) {
        rc = pthread_join(threadid[i], NULL);
        if (rc != 0)
            cout <<  "pthread_join()\n" <<  rc;
    }
    
    return 0;
}
