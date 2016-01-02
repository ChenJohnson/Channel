/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.cpp
 * Author: ustcjohnson
 * Email: johnson.chen0204@gmail.com
 * Created on 2015年12月31日, 下午9:18
 */

//#include <cstdlib>
#include "CChannelQueue.h"
#include <iostream>

//using namespace std;

/*
 * 
 */
static CChannelQueue<int>* myQueue = new CChannelQueue<int>(10, 0);

static void* readThread(void* arg){
    //int i = 0;
    while(true){
        int k = myQueue->readElem();
        std::cout << "elem: " << k << std::endl;
        //i++;
    }
}

static void* writeThread2(void* arg){
    int i = 100;
    while(i < 200){
        //std::cout << "input elem: " << i << std::endl; 
        myQueue->writeElem(i);
        i++;
        
    }
}

static void* writeThread1(void* arg){
    int i = 0;
    while(i < 100){
        //std::cout << "input elem: " << i << std::endl; 
        myQueue->writeElem(i);
        i++;
        
    }
}

int main(int argc, char** argv) {
    pthread_t tRead;
    pthread_t tWrite1;
    pthread_t tWrite2;

    int r;

    //void* res;

    pthread_create(&tWrite1, NULL, writeThread1, NULL);
    pthread_create(&tWrite2, NULL, writeThread2, NULL);
    pthread_create(&tRead, NULL, readThread, NULL);
    

    //pthread_join(tRead, &res);
    //pthread_join(tWrite, &res);
    std::cin >> r;
    return 0;
}

