//
//  Mutex.hpp
//  Ex6
//
//  Created by Ofir Rubin on 31/05/2022.
//

#ifndef Mutex_hpp
#define Mutex_hpp

#include <stdio.h>
#include <pthread.h>
#include <errno.h>
#include <iostream>

class MutexException: public std::exception
{
  virtual const char* what() const throw()
  {
    return "an error occured during locking/unlocking mutex";
  }
};


class ScopeLocker
{
private:
    pthread_mutex_t *lock = NULL;
public:
    ScopeLocker(pthread_mutex_t *user_lock);
    ScopeLocker();
    ~ScopeLocker();
};

class Mutex
{
public:
    pthread_mutex_t lock;
    bool allocated = false;
public:
    Mutex(pthread_mutex_t ulock);
    Mutex();
    ScopeLocker ScopeLock();
    void CondWait(pthread_cond_t *wait);
    void CondSignal(pthread_cond_t *wait);
    int Aquire();
    int Free();
    ~Mutex();
};

#endif /* Mutex_hpp */
