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
#include "Mutex.hpp"

template <typename T> class Singleton {
private:
    static inline Mutex* mutex;
    static inline Singleton *skl;
    T *instance; // "Static" public memeber - class shared value
    Singleton();
public:

    static T* Instance();
    static void Destroy();
    // Disallow copy constructor
    Singleton(Singleton const&) = delete;
    void operator=(Singleton const&) = delete;
};

// Constructor
template <typename T> Singleton<T>::Singleton()
{
    Singleton<T>::instance = new T(); // Create new value
    Singleton<T>::mutex = new Mutex();
}

template <typename T> T* Singleton<T>::Instance()
{
    static Singleton<T> val = Singleton<T>();
    skl = &val;
    val.mutex->ScopeLock();
    return val.instance;
}

template <typename T> void Singleton<T>::Destroy()
{
    // Make sure there's a value
    if (mutex)
    {
        mutex->Aquire();
        if (skl)
            skl->instance->~T(); // Force destructor - Use default.
        mutex->~Mutex(); // Force destructor, will free & destroy mutex.
    }
}

#endif /* Singleton_hpp */
