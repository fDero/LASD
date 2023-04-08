
// FRANCESCO DE ROSA N86004379

#pragma once

#include "queuevec.hpp"

namespace lasd {

    template <typename Data> QueueVec<Data>::QueueVec() : Vector<Data>() {}
    template <typename Data> QueueVec<Data>::~QueueVec() = default;

    template <typename Data> QueueVec<Data>::QueueVec(const MappableContainer<Data>& mc) : Queue<Data>::Queue(mc) { }
    template <typename Data> QueueVec<Data>::QueueVec(MutableMappableContainer<Data>&& mmc) : Queue<Data>::Queue(std::move(mmc)) { }
    
    template <typename Data> QueueVec<Data>::QueueVec(QueueVec<Data>&& qqvc) { this->operator=(std::move(qqvc)); }
    template <typename Data> QueueVec<Data>::QueueVec(const QueueVec<Data>& qqvc) { this->operator=(qqvc); } 
        
    template <typename Data> inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& stk) const noexcept { return not this->operator==(stk); }
    template <typename Data> bool QueueVec<Data>::operator==(const QueueVec<Data>& stk) const noexcept { 
        if (stk.size != size) return false;
        sizetype i = head_index;
        sizetype j = stk.head_index;
        for (sizetype counter = 0; counter < size; counter++){
            if (storage[i] != stk.storage[j]) return false;
            ++i %= actual_length;
            ++j %= stk.actual_length;
        }
        return true;
    }

    template <typename Data> QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& qqvc) { 
        Resize(qqvc.actual_length);
        size = qqvc.size;
        head_index = qqvc.head_index;
        std::copy(qqvc.storage, qqvc.storage + actual_length, storage);  
        return *this;
    }
    
    template <typename Data> inline QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& qqvc) { 
        std::swap(actual_length,qqvc.actual_length);
        std::swap(head_index,qqvc.head_index);
        Vector<Data>::operator=(std::move(qqvc));
        return *this;
    }    

    template <typename Data> void QueueVec<Data>::Clear() { 
        delete [] storage;
        storage = nullptr;
        size = 0;
        actual_length = 0;    
        head_index = 0;
    }

    template <typename Data> void QueueVec<Data>::Resize(sizetype newlength){
        Data* tmp = new Data [newlength];
        for (int i = 0; i < size; i++) { 
            tmp[i] = storage[(i+head_index) % actual_length];
        }
        actual_length = newlength;
        head_index = 0;
        std::swap(storage, tmp);
        delete [] tmp;
    }

    template <typename Data> void QueueVec<Data>::Enqueue(const Data& value){
        if (size + 1 > actual_length) Resize(actual_length * 2 + 1);
        storage[(head_index + size++)%actual_length] = value;
    }

    template <typename Data> void QueueVec<Data>::Enqueue(Data&& value){
        if (size + 1 > actual_length) Resize(actual_length * 2 + 1);
        storage[(head_index + size++)%actual_length] = std::move(value);
    }

    template <typename Data> void QueueVec<Data>::Dequeue(){
        if (size == 0) throw std::length_error("Dequeue() method called on empty queue");
        ++head_index %= (actual_length);
        if (size - 1 < actual_length/4) Resize(actual_length / 2);  
        size--;
    }

    template <typename Data> const Data& QueueVec<Data>::Head() const {
        if (size == 0) throw std::length_error("Head() method called on empty queue");
        return storage[head_index]; 
    }

    template <typename Data> Data& QueueVec<Data>::Head() {
        if (size == 0) throw std::length_error("Head() method called on empty queue");
        return storage[head_index]; 
    }
}