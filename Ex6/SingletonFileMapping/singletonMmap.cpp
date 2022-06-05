//
//  Singleton_Mmap.cpp
//  Ex6
//
//  Created by Ofir Rubin on 02/06/2022.
//

#include "singletonMmap.hpp"


class FileMapped{
public:
    size_t allocated_size;
    void *ptr;
    FileMapped(int mem_size=4096){
        allocated_size = mem_size;
        ptr = mmap(NULL, mem_size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
        if (!ptr)
            throw std::runtime_error("ERROR: while allocating memory using mmap!");
    }
    
    ~FileMapped(){
        if (munmap(ptr, allocated_size) == -1)
            printf("ERROR: while using munmap to de-allocate in FileMapped destructor");
        ptr = NULL;
        allocated_size = 0;
    }
};


int main(void){
    auto *a = Singleton<FileMapped>::Instance(new FileMapped(1000));
    auto *b = Singleton<FileMapped>::Instance(new FileMapped(3000)); // trying to override won't mather
    auto *c = Singleton<FileMapped>::Instance(new FileMapped(4000)); // ...

    printf("Expected results: 1000 | 1000 | 1000 | 5000 | 5000 | 4096 | 4096\n");
    std::cout << a->Get()->allocated_size << std::endl;
    std::cout << b->Get()->allocated_size << std::endl;
    std::cout << c->Get()->allocated_size << std::endl;

    Singleton<FileMapped>::Destroy(); // After destroying we can recreate /override the singleton
    
    c = Singleton<FileMapped>::Instance(new FileMapped(5000));
    b = Singleton<FileMapped>::Instance(); // By default the constructur will set 4096
    std::cout << c->Get()->allocated_size << std::endl;
    std::cout << b->Get()->allocated_size << std::endl;
    Singleton<FileMapped>::Destroy(); // After destroying we can recreate /override the singleton
    a = Singleton<FileMapped>::Instance();
    std::cout << b->Get()->allocated_size << std::endl;
    std::cout << Singleton<FileMapped>::Get()->allocated_size << std::endl; // In real case we won't actualy want to save the singleton but rather chain call
    
    return 0;
}
