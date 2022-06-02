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
    void Clear(bool free);
public:
    Queue(bool IsHead);
    Queue();
    ~Queue();
    bool IsEmpty();
    void enQ(void *ptr);
    void enQ_Copy(void *ptr, size_t size);
    void* deQ();
    void WaitNotEmpty(pthread_cond_t *cond);
    ScopeLocker getScopeLock();
    void Clear();
    void ClearAndFree();
};

#endif /* Queue_hpp */
