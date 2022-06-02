////
////  ChainedActiveObject.cpp
////  Ex6
////
////  Created by Ofir Rubin on 01/06/2022.
////
//
//#include "ChainedActiveObject.hpp"
//
//struct Package
//{
//    int sockfd;
//    void *ptr;
//};
//
//
//void parseInput(void *payload){
//    int sockfd = *(int *)payload;
//    // Get input
//    uInput->sockfd = sockfd;
//    
//    // Parse input
//    
//    // Sending input to post Parse (add to hist queue)
//    
//}
//void AOServer::postParse(void *payload){
//    
//}
//void histOnce(void *payload){}
//void inverseCap(void *payload){}
//void outputHandler(void *payload){}
//
//
//void postHist(void *payload){}
//void postInverse(void *payload){}
//void outputHandlerCleanup(void *payload){}
//
//AOServer::AOServer(){ // Create Active object
//    this->sockinput = new Queue(true);
//    this->caesarinput = new Queue(true);
//    this->inverseinput = new Queue(true);
//    this->output = new Queue(true);
//    
//    this->inputParser = new ActiveObject(&parseInput, &(AOServer::postParse), sockinput);
//    this->caesarProcess = new ActiveObject(&histOnce, &postHist, caesarinput);
//    this->inverseCapProces = new ActiveObject(&inverseCap, &postInverse, inverseinput);
//    this->outputPipe = new ActiveObject(&outputHandler, &outputHandlerCleanup, output);
//}
//
//void Start()
//{
//    // Create server
//    
//    // Bind
//    
//    //Listen
//    
//    while (true)
//    {
//        // Accept client
//        struct Package *client = (struct Package *)calloc(1, sizeof(struct Package));
//        
//    }
//}// Start server
