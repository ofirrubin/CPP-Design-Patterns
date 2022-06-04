//
//  main.cpp
//  Ex6
//
//  Created by Ofir Rubin on 30/05/2022.
//

//#include "main1.hpp"
//#include "Reactor.hpp"
//#include "SingletonTesting.hpp"
//#include "Singleton_Mmap.hpp"
#include "ReactorServer.hpp"
#include "PollServer.hpp"

int main(void){
    //singleton_test();
    //main1();
    //queue_test();
    //Reactor r = Reactor();
    //r.InstallHandler(stdin, <#void (*Handler)()#>)
    //main2();
    start_reactor_server();
    //start_server();
    return 0;
}
