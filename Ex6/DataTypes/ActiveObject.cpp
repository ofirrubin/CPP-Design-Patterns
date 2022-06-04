//
//  ActiveObject.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include "ActiveObject.hpp"

void ActiveObject::ActiveWorker(){
    printf("DEBUG: ActiveObject Running: %s\n", (this->description? this->description: "Unknown"));
    while(true)
    {
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
                           Queue *queue, char *description)
{
    this -> description = description;
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
        printf("[Warning: Memory is not free'd, Use destoryAO to free()] Removing %s\n", (char *)q->deQ());
    }
    //q->~Queue(); // Explicitly tear apart q;
}
void ActiveObject::AddJob(void *payload){
    q->enQ(payload);
} // Add to queue


void ActiveObject::destroyAO() // USE ONLY IF ALL QUEUE ELEMENTS CAN BE FREED BY free() FUNCTION
{
    pthread_cancel(workerThread);
    while (! q->IsEmpty())
    {
        free(q->deQ()); // Free memory
        printf("DEBUG: destoryAO() free() called\n");
    }
}
