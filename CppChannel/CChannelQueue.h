/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CChannelQueue.h
 * Author: ustcjohnson
 * Email: johnson.chen0204@gmail.com
 * Created on 2015年12月31日, 下午9:25
 */

#ifndef CCHANNELQUEUE_H
#define CCHANNELQUEUE_H

//#include <iostream>
#include <list>
#include <pthread.h>
#include "elemItem.h"

template <class T> 
class CChannelQueue {
public:
    CChannelQueue(){};
    
    CChannelQueue(int iSize, T elem);
    //CChannelQueue(const CChannelQueue& orig);
    virtual ~CChannelQueue();
    
    // write elem to the queue
    void writeElem(T elem);
    
    // read elem from the queue
    T readElem();
    
private:
    int mSize;
    
    std::list<CElem<T>* > mLstCapcity;
    std::list<CElem<T>* > mLstReadWrite;
    
    pthread_mutex_t mMutex;
    pthread_cond_t  mCanWrite;
    pthread_cond_t  mCanRead;
};

#endif /* CCHANNELQUEUE_H */

