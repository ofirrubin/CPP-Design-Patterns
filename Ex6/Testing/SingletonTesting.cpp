//
//  SingletonTesting.cpp
//  Ex6
//
//  Created by Ofir Rubin on 30/05/2022.
//

#include "SingletonTesting.hpp"

int singleton_test(void) {
    Queue *singleton1 = Singleton<Queue>::Instance();
    Queue *singleton2 = Singleton<Queue>::Instance();
    (*singleton2).enQ_Copy((void *)"Hello", 6);
    (*singleton1).enQ_Copy((void *)"World", 5);
    (*singleton1).enQ_Copy((void *)"Removed", 7);
    cout << (char *)(*singleton1).deQ() << endl;
    cout << (char *)(*singleton2).deQ() << endl;
    cout << "Is empty? " << ((*singleton1).IsEmpty() ? "Yes":  "No") << endl;
    cout << "Destroying..." << endl;
    Singleton<Queue>::Destroy();
    cout << "Destroyed, Queue state: " << ((*singleton1).IsEmpty() ? "Empty":  "Not empty") << endl;
    return 0;
}
