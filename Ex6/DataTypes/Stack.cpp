//
//  Stack.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include "Stack.hpp"

Stack::Stack(){
        value = NULL;
        this->next = NULL;
    }
Stack Stack::CreateThreadSafe()
    {
        Stack s = Stack();
        s.SetThreadSafe();
        return s;
}
Stack::~Stack(){
        pthread_cond_destroy(IsEmptyCond);
}
void Stack::SetThreadSafe()
    {
        lock = Mutex();
        // Set pthread cond
        IsEmptyCond = (pthread_cond_t *)malloc(sizeof(pthread_cond_t));
        pthread_cond_init(IsEmptyCond, NULL);
}

void* Stack::Top()
    {
        lock.ScopeLock();
        return value;
}
bool Stack::IsEmpty()
    {
        lock.ScopeLock();
        return value == NULL;
}
void Stack::Pop(int free_memory)
    {
        lock.Aquire();
        if (atomicIsEmpty) // Has it's own scope lock
        {
            lock.CondWait(IsEmptyCond);
        }
        atomicIsEmpty = false;
        if (free_memory)
            free(value);
        if (this->next != NULL){
            this->value = this->next->value;
            this->next = this->next->next;
        }
        else
            atomicIsEmpty = true;
        lock.Free();
}

void Stack::Pop()
{
    Pop(0);
}
void Stack::PopFree()
{
    Pop(1);
}

bool Stack::Push(void *value)
{
    lock.ScopeLock();
    Stack *s = new Stack();
    s->value = this->value;
    s->next = this->next;
    this->value = value;
    this->next = s;
    this->atomicIsEmpty = false;
    pthread_cond_signal(IsEmptyCond);
    return true ;
}
