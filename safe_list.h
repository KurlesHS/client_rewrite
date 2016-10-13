/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   safe_list.h
 * Author: kurles
 *
 * Created on 12 октября 2016 г., 16:13
 */

#ifndef SAFE_LIST_H
#define SAFE_LIST_H

#include <list>
#include <iostream>

using namespace std;

template<typename _Tp, typename _Alloc = std::allocator<_Tp> >
class safe_list : public std::list<_Tp, _Alloc>
{
public:    
    void safe_remove(const _Tp &element) {
        if (mIsIterating) {
            mToDelete.push_back(element);
        } else {
            this->remove(element);
        }
    }

    void safe_clear() {
        if (mIsIterating) {
            mIsNeedToClear = true;
        } else {
            this->clear();
        }
        
    }

    template<typename M, typename ... Args>
    void call_member_func(M m, Args ...args) {        
        #define CALL_MEMBER_FN(object,ptrToMember)  ((object)->*(ptrToMember))
        mIsIterating = true;
        for (const auto pointer : *this) {
            CALL_MEMBER_FN(pointer, m)(std::forward<Args>(args)...);
        }
        mIsIterating = false;
        bool isRemoving = false;
        for (const auto pointer : mToDelete) {
            isRemoving = true;
            this->remove(pointer);
        }
        if (isRemoving) {
            mToDelete.clear();
        }
        if (mIsNeedToClear) {
            this->clear();
            mIsNeedToClear = false;
        }        
    }
    template<typename ... Args>
    void call_function(Args ...args) {
        mIsIterating = true;
        for (const auto func : *this) {
            func(std::forward<Args>(args)...);
        }
        mIsIterating = false;
        if (mIsNeedToClear) {
            this->clear();
            mIsNeedToClear = false;
        }
    }

private:
    bool mIsIterating = false;
    bool mIsNeedToClear = false;
    std::list<_Tp, _Alloc> mToDelete;
};


#endif /* SAFE_LIST_H */

