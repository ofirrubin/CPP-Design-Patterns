//
//  Queue.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include "Queue.hpp"

Queue::Queue(bool IsHead)
{
    Lock = Mutex(); // If head set default header, otherwise set NULL mutex.
    // Set IsEmpty
    if (IsHead)
    {
        IsEmptyCond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
        pthread_cond_init(IsEmptyCond, NULL);
    }
    else
        IsEmptyCond = NULL;
}

Queue::Queue()
{
    Lock = Mutex(); // If head set default header, otherwise set NULL mutex.
    IsEmptyCond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
    pthread_cond_init(IsEmptyCond, NULL);
}


void Queue::Clear(bool toFree){
    while (!IsEmpty())
    {
        void *ptr = deQ();
        if (toFree)
            free(ptr);
    }
}

void Queue::Clear(){
    Clear(false);
}

void Queue::ClearAndFree(){
    Clear(true);
}

Queue::~Queue()
{
    ClearAndFree();
    if (IsEmptyCond != NULL)
    {
        std::cout << "DEBUG: [IsEmptyCond] pthread_cond_destroy returned [" << pthread_cond_destroy(IsEmptyCond) << "]\n";
        free(IsEmptyCond);
    }
}

void Queue::enQ_Copy(void *ptr, size_t size)
{
    void *mem = calloc(1, size);
    if (!mem)
        throw std::runtime_error("Error allocating memory with enQ_copy");
    memcpy(mem, ptr, size);
    enQ(mem);
    Lock.Aquire();
    Lock.Free();
}

void Queue::enQ(void *ptr)
{
    Lock.ScopeLock();
    if (Value == NULL) // If the queue is empty
    {
        Value = ptr;
        Lock.CondSignal(IsEmptyCond);
    }
    else
    {
        Queue *tmp = new Queue(false); // This value is not head.
        tmp->Value = ptr;
        if (Last != NULL)
            Last->Next = tmp;
        Last = tmp;
        if (Next == NULL)
            Next = tmp; // The next element is also the last one.
    }
}

void Queue::WaitNotEmpty(pthread_cond_t *cond)
{
    while (Value == NULL) // The thread is instructed to wait to deQ if empty.
    {
        Lock.CondWait(cond);
    }
}

void* Queue::deQ()
{
    Lock.Aquire();
    WaitNotEmpty(IsEmptyCond);
    void *ptr = Value; // Save value for return
    this->Value = NULL; // Reset current value (We can't be sure there's next value yet)
    if (Next != NULL) // If last value
    {
        Value = Next->Value; // Skip this node
        Next = Next->Next;
    }
    Lock.Free();
    return ptr;
}

bool Queue::IsEmpty()
{
    Lock.ScopeLock();
    return Value == NULL;
}

ScopeLocker Queue::getScopeLock()
{
    return Lock.ScopeLock();
}
