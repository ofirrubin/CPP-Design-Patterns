//
//  Mutex.cpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#include "Mutex.hpp"


// ScopeLock
ScopeLocker::ScopeLocker(pthread_mutex_t *user_lock):lock(user_lock) //lock=user_lock
    {
        if (pthread_mutex_lock(user_lock) != 0)
            return;
            //throw MutexException();
    }
ScopeLocker::ScopeLocker()
    {
        lock = NULL;
    }
ScopeLocker:: ~ScopeLocker()
    {
    if (pthread_mutex_unlock(lock) != 0) return;
                //throw MutexException();
    }
// End ScopeLock


// Mutex
Mutex::Mutex(pthread_mutex_t ulock)
    {
        lock = ulock;
    }
Mutex::Mutex()
    {
        lock = PTHREAD_MUTEX_INITIALIZER;
    }

Mutex::~Mutex()
    {
        try {
            pthread_mutex_unlock(&lock); // Try unlock (only if required)
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
