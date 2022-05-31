//
//  Queue.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include "Queue.hpp"

Queue::Queue(bool IsHead)
{
    Lock = Mutex(false); // If head set default header, otherwise set NULL mutex.
    // Set IsEmpty
    if (IsHead)
    {
        IsEmptyCond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
        pthread_cond_init(IsEmptyCond, NULL);
        atomicSize = 0;
    }
    else
        IsEmptyCond = NULL;
}

Queue::~Queue()
{
    if (IsEmptyCond != NULL)
    {
        std::cout << "DEBUG: pthread_cond_destroy returned [" << pthread_cond_destroy(IsEmptyCond) << "]\n";
        free(IsEmptyCond);
    }
    if (atomicSize > 0)
    {
        
    }
}

void Queue::enQ(void *ptr)
{
    Lock.ScopeLock();
    if (atomicSize == 0) // If the queue is empty
    {
        Value = ptr;
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
    atomicSize ++;
    if (atomicSize == 1)
        Lock.CondSignal(IsEmptyCond);
}

void* Queue::deQ()
{
    Lock.Aquire();
    std::cout << "Waiting to deQ...\n";
    if (atomicSize == 0) // The thread is instructed to wait to deQ if empty.
    {
        Lock.CondWait(IsEmptyCond);
    }
    atomicSize --;
    std::cout << "There's an element we can deQ...\n";

    void *ptr = Value; // Save value for return
    if (ptr == NULL)
    {
        printf("IM HERE");
    }
    printf("DEBUG: WeakPointCheck[0] %d\n", ptr);
    this->Value = NULL; // Reset current value (We can't be sure there's next value yet)
    if (Next != NULL) // If last value
    {
        Value = Next->Value; // Skip this node
        Next = Next->Next;
    }
    Lock.Free();
    printf("DEBUG: WeakPointCheck[0] %d\n", ptr); // At the beginning I was getting NULL pointer, after a few times I ran it (to debug it) I was no longer getting this exception.
    return ptr;
}
