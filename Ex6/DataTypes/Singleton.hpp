//
//  Singleton.hpp
//  Ex6
//
//  Created by Ofir Rubin on 01/06/2022.
//

#ifndef Singleton_hpp
#define Singleton_hpp

#include <stdio.h>
#include "pthread.h"
#include "Guard.hpp"

template <typename T> class Singleton {
private:
    static inline Mutex* mutex;
    static inline Singleton *skl;
    static inline bool removed = true;
    T *instance; // "Static" public memeber - class shared value
    Singleton(T *existing = NULL);
public:

    static Singleton<T>* Instance(T *val = NULL);
    static T* Get(); // Get value
    static void Destroy();
    // Disallow copy constructor
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&) = delete;
};

// For some reason if I move the impl. to cpp file it don't recognize the functions, I'll check it later.

template <typename T> Singleton<T>::Singleton(T *existing)
{
    if (existing)
        Singleton<T>::instance = existing;
    else
        Singleton<T>::instance = new T(); // Create new value
    Singleton<T>::mutex = new Mutex();
}

template <typename T> Singleton<T>* Singleton<T>::Instance(T *existing)
{
    static Singleton<T> *val; // Static inline
    if (removed){
        val = new Singleton<T>(existing);
        removed = false;
        skl = val;
    }
    skl->mutex->ScopeLock();
    return skl;
}

template <typename T> T* Singleton<T>::Get()
{
    if (!skl)
        Singleton<T>::Instance();
    skl->mutex->ScopeLock();
    return skl->instance;
}

template <typename T> void Singleton<T>::Destroy()
{
    // Make sure there's a value
    if (mutex)
    {
        mutex->Aquire();
        if (skl){
            skl->instance->~T(); // Force destructor - Use default.
            //skl = NULL; // Remove any connection
            removed = true;
        }
        mutex->~Mutex(); // Force destructor, will free & destroy mutex.
    }
}

#endif /* Singleton_hpp */
