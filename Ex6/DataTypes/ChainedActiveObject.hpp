////
////  ChainedActiveObject.hpp
////  Ex6
////
////  Created by Ofir Rubin on 01/06/2022.
////
//
//#ifndef ChainedActiveObject_hpp
//#define ChainedActiveObject_hpp
//
//#include <stdio.h>
//#include "ActiveObject.hpp"
//
//class AOServer// 3 layers active objects
//{
//private:
//    Queue *sockinput; // int Queue
//    Queue *caesarinput; // struct UserInput <sockfd, char *>
//    Queue *inverseinput; // struct UserInput <sockfd, char *>
//    Queue *output; // struct UserInput <sockfd, char *>
//    
//    ActiveObject *inputParser; // Got <sockfd> in queue, send <sockfd, userinput> to inputProcess
//    ActiveObject *caesarProcess; // Process input to hist of +1 => <sockfd, processed_input>
//    ActiveObject *inverseCapProces; // Change caesarInput to inverse capital letters => <sockfd, process_input>
//    ActiveObject *outputPipe;
//    void AOServer::postParse(void *payload);
//public:
//    AOServer(); // Create Active object
//    void Start(); // Start server
//};
//
//#endif /* ChainedActiveObject_hpp */
