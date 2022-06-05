//
//  Queue.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include "queue.hpp"

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
    if (IsEmptyCond != NULL)
    {
        int c = pthread_cond_destroy(IsEmptyCond);
        std::cout << "DEBUG: [IsEmptyCond] pthread_cond_destroy returned [" << c << "]\n";
        if (!c){ // We can free only if we are not using it/ allocated it. if destory was failed we can't free.
            free(IsEmptyCond);
            IsEmptyCond = NULL;
        }
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
        Queue *next = Next->Next;
        Value = Next->Value;
        delete Next;
        Next = next;
        
    }
    Lock.Free();
    return ptr;
}



bool Queue::IsEmpty()
{
    Lock.ScopeLock();
    return Value == NULL;
}

// Ban / Kick / Remove is useful in cases such in Reactor.
bool Queue::RemoveFromQueue(void *other, size_t size, bool free_val){ // Comparing using memcmp
    Lock.ScopeLock();
    Queue *current = this;
    Queue *before = NULL;
    while(current->Value){
        if (memcmp(current->Value, other, size)){
            if (free_val)
                free(current->Value);
            this->Value = NULL;

            if (current->Next != NULL)
            {
                current->Value = Next->Value;
                current->Next = Next->Next;
            }
            if (before){  // Make sure the element before is updated
                before->Next = current;
            }
            // the removed object will be free'd by garbage collector.
            return true;
        }
        else
        {
            before = current;
            current = current->Next;
        }
        
    }
    return false;
}



// ALIAS FUNCTIONS: To make functions signatures as requested
Queue *createQ(){
    return new Queue();
}

void destroyQ(Queue *q, bool freeValues){
    if (freeValues)
    	q->ClearAndFree();
    else
    	q->Clear();
    q->~Queue();
    delete q;
}

void enQ(Queue *q, void *ptr){
    q->enQ(ptr);
}

void *deQ(Queue *q){
    return q->deQ();
}
