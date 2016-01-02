/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   CChannelQueue.cpp
 * Author: ustcjohnson
 * Email:  johnson.chen0204@gmail.com
 * Created on 2015年12月31日, 下午9:25
 */

#include "CChannelQueue.h"

template<class T>
CChannelQueue<T>::CChannelQueue(int iSize, T elem) {
    mSize = iSize;
    mLstCapcity = new std::list<CElem<T>* >(iSize);
    for(int i = 0; i < mSize; i++){
        mLstCapcity.push_back(new CElem<T>(elem));
    }
    
    mLstReadWrite = new std::list<CElem<T>* >(iSize);
    
    mMutex = PTHREAD_MUTEX_INITIALIZER;
    mCanRead = PTHREAD_COND_INITIALIZER;
    mCanWrite = PTHREAD_COND_INITIALIZER;
}

/*CChannelQueue::CChannelQueue(const CChannelQueue& orig) {
  
    
}*/



template<class T>
CChannelQueue<T>::~CChannelQueue() {
     //it;

    typename std::list<CElem<T>*>::iterator iterCapcity = mLstCapcity.begin();
    while(iterCapcity != mLstCapcity.end()){
        delete *iterCapcity;
        iterCapcity++;
    }
    
    typename std::list<CElem<T>*>::iterator iterReadWrite = mLstReadWrite.begin();
    while(iterReadWrite != mLstReadWrite.end()){
        delete *iterReadWrite;
        iterReadWrite++;
    }    
}

template<class T>
T CChannelQueue<T>::readElem(){
    pthread_mutex_lock(&mMutex);
    
    while(mLstReadWrite.size() <= 0){
        pthread_cond_wait(&mCanRead, &mMutex);
    }
    
    CElem<T>* head = mLstReadWrite.pop_front();
    if(head != NULL){
        return head->GetElem();
    }
    mLstCapcity.push_back(head);
    
    pthread_cond_signal(&mCanWrite);
    if(mLstReadWrite.size() > 0){
        pthread_cond_signal(&mCanRead);
    }
    
    pthread_mutex_unlock(&mMutex);
}

template<class T>
void CChannelQueue<T>::writeElem(T elem){
    pthread_mutex_lock(&mMutex);
    
    while(mLstCapcity.size() <= 0){
        pthread_cond_wait(&mCanWrite, &mMutex);
    }
    
    CElem<T>* adding = mLstCapcity.pop_front();
    adding->SetElem(elem);
    
    mLstReadWrite.push_back(adding);
    
    pthread_cond_signal(&mCanRead);
    if(mLstCapcity.size() > 0){
        pthread_cond_signal(&mCanWrite);
    }
    
    pthread_mutex_unlock(&mMutex);
}