
// FRANCESCO DE ROSA N86004379

#pragma once

#include "stackvec.hpp"

namespace lasd {

    template <typename Data> StackVec<Data>::StackVec() : Vector<Data>() {}
    template <typename Data> StackVec<Data>::~StackVec() = default;

    template <typename Data> StackVec<Data>::StackVec(const StackVec& stckvc) : Vector<Data>(stckvc) { actual_length = stckvc.actual_length; }
    template <typename Data> StackVec<Data>::StackVec(StackVec&& stckvc) : Vector<Data>(stckvc) { actual_length = stckvc.actual_length; }
    
    template <typename Data> inline bool StackVec<Data>::operator==(const StackVec<Data>& stk) const noexcept { return Vector<Data>::operator==(stk); }
    template <typename Data> inline bool StackVec<Data>::operator!=(const StackVec<Data>& stk) const noexcept { return Vector<Data>::operator!=(stk); }

    template <typename Data> const Data& StackVec<Data>::Top() const { 
        if (size == 0) throw std::length_error("Top() method called on an empty stack");
        return this->Back(); 
    }
    
    template <typename Data> Data& StackVec<Data>::Top() { 
        if (size == 0) throw std::length_error("Top() method called on an empty stack");
        return this->Back(); 
    }
   
    template <typename Data> StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stk) { 
        stk.PreOrderMap([this](const Data& value){ this->Push(value); }); 
        return *this;
    }
    
    template <typename Data> inline StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stk) { 
        actual_length = stk.actual_length;
        size = stk.size;
        storage = stk.storage;
        stk.storage = nullptr;
        return *this; 
    }
   
    template <typename Data> inline void StackVec<Data>::Clear() { 
        Vector<Data>::Clear();
        actual_length = 0;    
    }

    template <typename Data> void StackVec<Data>::Resize(sizetype newlength) { 
        Data* tmp = (newlength)? new Data[newlength] : nullptr;
        sizetype minimum_length = std::min(newlength, actual_length);
        std::copy(storage, storage + minimum_length, tmp);
        std::swap(tmp, storage);
        delete [] tmp;
        actual_length = newlength;
    }

    template <typename Data> inline void StackVec<Data>::Pop(){
        if (size == 0) throw std::length_error("Pop() method called on an empty stack");
        if (--size < actual_length/4) Resize(actual_length/2);
    }

    template <typename Data> void StackVec<Data>::Push(const Data& value){
        if (++size >= actual_length) Resize(actual_length * 2 + 1);
        this->Back() = value;
    }

    template <typename Data> void StackVec<Data>::Push(Data&& value){
        if (++size >= actual_length) Resize(actual_length * 2 + 1);
        this->Back() = value;
    }
}
