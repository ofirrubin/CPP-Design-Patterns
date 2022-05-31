//
//  ActiveObject.hpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#ifndef ActiveObject_hpp
#define ActiveObject_hpp

#include <stdio.h>
#include "Queue.hpp"
class ActivePayload
{
private:
    void (*prework)(void *payload);
    void (*afterwork)(void *payload);
    void *payload;
public:
    ActivePayload(void (*prework)(void *payload), void (*afterwork)(void *payload), void *payload);
    void PreWork();
    void PostWork();
};

class ActiveObject
{
private:
    Queue *q;
    pthread_t workerThread;
    void (*PreWorkFunc)(void *payload);
    void (*PostWorkFunc)(void *payload);
    static void* ActiveWorkerWrapper(void *This);
    void ActiveWorker(); // Background worker, wait for new objcet to

public:
    ActiveObject(void (*PreWorkFunc)(void *payload), void (*PostWorkFunc)(void *payload), Queue *queue);
    ~ActiveObject();
    void AddJob(void *payload); // Add to queue
};

#endif /* ActiveObject_hpp */
