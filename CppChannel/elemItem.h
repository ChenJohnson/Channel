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

#ifndef ELEMITEM_H
#define ELEMITEM_H

template <class T> 
class CElem{
private:
    T mItem;

public:
    CElem(T item){
        mItem = item;
    }
    
    void SetElem(T item){
        mItem = item;
    }
    
    T GetElem() const{
        return mItem;
    }
};

#endif /* ELEMITEM_H */

