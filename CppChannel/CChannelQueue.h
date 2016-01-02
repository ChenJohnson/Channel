/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   elemItem.h
 * Author: ustcjohnson
 * Email: johnson.chen0204@gmail.com
 * Created on 2015年12月31日, 下午9:19
 */

#ifndef _CCHANNELQUEUE
#define _CCHANNELQUEUE

#include "elemItem.h"
#include <pthread.h>
#include <iostream>
#include <list>

template <class T> 
class CChannelQueue{
public:
    CChannelQueue(int iSize, T elem){
        mSize = iSize;
        mLstCapcity = new std::list<CElem<T>* >();
        for(int i = 0; i < mSize; i++){
            mLstCapcity->push_back(new CElem<T>(elem));
        }
        
        mLstReadWrite = new std::list<CElem<T>*>();
        
        mMutex = PTHREAD_MUTEX_INITIALIZER;
        mCanRead = PTHREAD_COND_INITIALIZER;
        mCanWrite = PTHREAD_COND_INITIALIZER;
    }

    virtual ~CChannelQueue(){
         //it;

            typename std::list<CElem<T>*>::iterator iterCapcity = mLstCapcity->begin();
            while(iterCapcity != mLstCapcity->end()){
                delete *iterCapcity;
                iterCapcity++;
            }
            
            typename std::list<CElem<T>*>::iterator iterReadWrite = mLstReadWrite->begin();
            while(iterReadWrite != mLstReadWrite->end()){
                delete *iterReadWrite;
                iterReadWrite++;
            }    
    }

    // write elem to the queue
    void writeElem(T elem){
        pthread_mutex_lock(&mMutex);

        //std::cout << "capcity's size: " << mLstCapcity->size() << std::endl;
        
        while(mLstCapcity->size() <= 0){
            pthread_cond_wait(&mCanWrite, &mMutex);
        }

        CElem<T>* adding = mLstCapcity->front();
        adding->SetElem(elem);

        mLstCapcity->pop_front();
        
        mLstReadWrite->push_back(adding);
        
        pthread_cond_signal(&mCanRead);
        if(mLstCapcity->size() > 0){
            pthread_cond_signal(&mCanWrite);
        }
        
        pthread_mutex_unlock(&mMutex);
    }

    // read elem from the queue
    T readElem(){
        pthread_mutex_lock(&mMutex);
        
        while(mLstReadWrite->size() <= 0){
            pthread_cond_wait(&mCanRead, &mMutex);
        }
        
        CElem<T>* head = mLstReadWrite->front();
        mLstReadWrite->pop_front();

        mLstCapcity->push_back(head);
        
        pthread_cond_signal(&mCanWrite);
        if(mLstReadWrite->size() > 0){
            pthread_cond_signal(&mCanRead);
        }       
        pthread_mutex_unlock(&mMutex);

        if(head != NULL){
            return head->GetElem();
        } 
    }

private:
    int mSize;
    std::list<CElem<T>*> *mLstCapcity;
    std::list<CElem<T>*> *mLstReadWrite;

    pthread_mutex_t mMutex;
    pthread_cond_t  mCanWrite;
    pthread_cond_t  mCanRead;
};

#endif

