//
//  Mutex.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include "Mutex.hpp"


// ScopeLock
ScopeLocker::ScopeLocker(pthread_mutex_t *user_lock)
    {
        lock = user_lock;
        int temp = pthread_mutex_lock(user_lock);
        if (temp != 0)
            std::cout << "ERROR: Locking mutex using ScopeLocker [" << temp << "]" << std::endl;
    }
ScopeLocker::ScopeLocker()
    {
        lock = NULL;
    }
ScopeLocker:: ~ScopeLocker()
    {
        if (lock)
            pthread_mutex_unlock(lock);
    }
// End ScopeLock


// Mutex
Mutex::Mutex(pthread_mutex_t ulock)
    {
        lock = ulock;
    }
Mutex::Mutex(bool setEmpty) // Either empty for dummy usage or default
    {
        if (!setEmpty)
        {
            lock = PTHREAD_MUTEX_INITIALIZER;
        }
    }

Mutex::~Mutex()
    {
        try {
            pthread_mutex_destroy(&lock);
        } catch (const std::system_error& e) {
            std::cout << "ERROR: destroying mutex: " << e.what() << std::endl;
        }
    }

ScopeLocker Mutex::ScopeLock()
    {
        return ScopeLocker(&lock);
    }

void Mutex::CondWait(pthread_cond_t *wait)
    {
        pthread_cond_wait(wait, &lock);
    }
void Mutex::CondSignal(pthread_cond_t *wait)
    {
        pthread_cond_signal(wait);
    }

int Mutex::Aquire()
    {
        return pthread_mutex_lock(&lock);
    }
int Mutex::Free()
    {
        return pthread_mutex_unlock(&lock);
    }
// End Mutex
