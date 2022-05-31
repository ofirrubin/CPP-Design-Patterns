//
//  Stack.hpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#ifndef Stack_hpp
#define Stack_hpp

#include <stdio.h>
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

#include "Mutex.hpp"

//
//  Stack.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include "Stack.hpp"

class Stack {
public:
    void *value;
    Stack *next;
    Mutex lock = Mutex(); // Dummy for non-thread safe
    pthread_cond_t *IsEmptyCond = NULL;
    bool atomicIsEmpty = true;
public:
    Stack();
    static Stack CreateThreadSafe();
    ~Stack();
    void SetThreadSafe();
    void *Top();
    bool IsEmpty();
    void Pop();
    void PopFree();
    bool Push(void *value);
private:
    void Pop(int free_memory);
};

#endif /* Stack_hpp */
