//
//  Queue.cpp
//  Ex6
//
//  Created by Ofir Rubin on 30/05/2022.
//
#include "QueueTest.h"


static Queue t = new Queue(true);

void *tFunc(void *parm)
{
    printf("deQ element: %s\n", (char *)t.deQ());
    return (void *)0;
}

int queue_test(void) {
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

    sleep(0.1); // Push is actually signalling
    t.enQ((void *)"6");
    sleep(0.2); // Push is actually signalling
    t.enQ((void *)"Last item!");
    
    printf("Wait for threads\n");
    for (i=0; i<numThreads; ++i) {
        rc = pthread_join(threadid[i], NULL);
        if (rc != 0)
            cout <<  "pthread_join()\n" <<  rc;
    }
    
    return 0;
}
