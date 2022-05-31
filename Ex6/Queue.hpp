//
//  Queue.hpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#ifndef Queue_hpp
#define Queue_hpp

#include <stdio.h>

#include "Mutex.hpp"

class Queue
{
private:
    Mutex Lock;
    void *Value = NULL;
    Queue *Next = NULL;
    Queue *Last = NULL;
    pthread_cond_t *IsEmptyCond = NULL;
    int atomicSize = 0;
    
public:
    Queue(bool IsHead);
    ~Queue();
    void enQ(void *ptr);
    void* deQ();
};

#endif /* Queue_hpp */
