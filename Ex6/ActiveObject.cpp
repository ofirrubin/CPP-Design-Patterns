//
//  ActiveObject.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include "ActiveObject.hpp"

ActivePayload::ActivePayload(void (*prework_func)(void *payload), void (*afterwork_func)(void *payload), void *payload)
{
    this->prework = prework_func;
    this->afterwork = afterwork_func;
    this->payload = payload;
}

void ActivePayload::PreWork()
{
    (*prework)(payload);
}

void ActivePayload::PostWork()
{
    (*afterwork)(payload);
}


void ActiveObject::ActiveWorker(){
    printf("Active worker is up at background...\n");
    pthread_cond_t waiter = PTHREAD_COND_INITIALIZER;
    while(true)
    {
        q->getScopeLock();
        q->WaitNotEmpty(&waiter);
        void *ptr = q->deQ();
        PreWorkFunc(ptr);
        PostWorkFunc(ptr);
    }
} // Background worker, wait for new objcet to

void *ActiveObject::ActiveWorkerWrapper(void *This)
{
    ((ActiveObject *)This)->ActiveWorker();
    return NULL;
}

ActiveObject::ActiveObject(void (*PreWork)(void *payload),
                           void (*PostWork)(void *payload),
                           Queue *queue)
{
    this -> q = queue;
    this -> PreWorkFunc = PreWork;
    this -> PostWorkFunc = PostWork;
    pthread_create(&workerThread, NULL, ActiveWorkerWrapper, (void *)this);
}
ActiveObject::~ActiveObject()
{
    pthread_cancel(workerThread);
    while (! q->IsEmpty())
    {
        //free(q->deQ()); // Free memory
        printf("Deleting... removing %s\n", (char *)q->deQ());
    }
    //q->~Queue(); // Explicitly tear apart q;
}
void ActiveObject::AddJob(void *payload){
    q->enQ(payload);
} // Add to queue


