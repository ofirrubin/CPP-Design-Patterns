//
//  stackTesting.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include <stdio.h>

#include <iostream>
#include "Guard.hpp"
#include "pthread.h"
#include <stdio.h>
#include <unistd.h>

#include "Stack.hpp"

using std::cout;
using std::endl;
using std::string;
static Stack s1 = Stack::CreateThreadSafe();

void *threadfunc(void *parm)
{
    s1.Pop();
    s1.Push((void *)"New Value");
    return (void *)0;
}

int test(void) {
    int rc=0;
    int i;
    int numThreads=  2;
    pthread_t threadid[numThreads];

    printf("Create %d threads\n", numThreads);
    for(i=0; i<numThreads; ++i) {
        rc = pthread_create(&threadid[i], NULL, threadfunc, NULL);
        if (rc != 0)
            cout << "pthread_create() "<<  rc;
    }

    sleep(5); // Push is actually signalling
    cout << s1.Push((void *)"Hi") << endl;
    
    printf("Wait for threads\n");
    for (i=0; i<numThreads; ++i) {
        rc = pthread_join(threadid[i], NULL);
        if (rc != 0)
            cout <<  "pthread_join()\n" <<  rc;
    }
    cout << (char *)s1.Top() << endl;
    s1.Pop();
    
    cout << (s1.IsEmpty() ? "Stack is empty" : "Stack is not empty") << endl;

    return 0;
}
