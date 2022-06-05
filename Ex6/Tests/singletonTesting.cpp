//
//  SingletonTesting.cpp
//  Ex6
//
//  Created by Ofir Rubin on 30/05/2022.
//

#include "singletonTesting.hpp"

int main(void) {
    Queue *singleton1 = Singleton<Queue>::Get();
    Queue *singleton2 = Singleton<Queue>::Get();
    (*singleton2).enQ((void *)"Hello");
    (*singleton1).enQ((void *)"World");
    (*singleton1).enQ((void *)"Removed");
    cout << (char *)(*singleton1).deQ() << endl;
    cout << (char *)(*singleton2).deQ() << endl;
    cout << "Is empty? " << ((*singleton1).IsEmpty() ? "Yes":  "No") << endl;
    cout << "Destroying..." << endl;
    Singleton<Queue>::Get()->Clear();
    Singleton<Queue>::Destroy();
    cout << "Destroyed, Queue state: " << ((*singleton1).IsEmpty() ? "Empty":  "Not empty") << endl;
    return 0;
}
