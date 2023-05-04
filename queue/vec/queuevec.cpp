
// FRANCESCO DE ROSA N86004379

#pragma once

#include "queuevec.hpp"

namespace lasd {

    sizetype constexpr QUEUEVEC_MINIMUM_LENGTH = 8;


    /**************************************** CONSTRUCTORS AND DISTRUCTORS *************************************/

    template <typename Data> QueueVec<Data>::QueueVec() noexcept { 
        if constexpr (QUEUEVEC_MINIMUM_LENGTH != 0) {
            actual_length = QUEUEVEC_MINIMUM_LENGTH;
            storage = new Data[QUEUEVEC_MINIMUM_LENGTH];
        } 
    }

    template <typename Data> QueueVec<Data>::QueueVec(const MappableContainer<Data>& mc) noexcept {
        actual_length = std::max(mc.Size(), QUEUEVEC_MINIMUM_LENGTH);
        storage = Vector<Data>::array_safe_alloc(actual_length);
        mc.Map([this](const Data& value){ this->Enqueue(value); });
    }
    
    template <typename Data> QueueVec<Data>::QueueVec(MutableMappableContainer<Data>&& mmc) noexcept {
        actual_length = std::max(mmc.Size(), QUEUEVEC_MINIMUM_LENGTH);
        storage = Vector<Data>::array_safe_alloc(actual_length);
        mmc.Map([this](const Data& value){ this->Enqueue(std::move(value)); });
    }
    
    template <typename Data> QueueVec<Data>::QueueVec(QueueVec<Data>&& qqvc) noexcept { this->operator=(std::move(qqvc)); }
    template <typename Data> QueueVec<Data>::QueueVec(const QueueVec<Data>& qqvc) noexcept { this->operator=(qqvc); } 




    /******************************************* ASSIGNMENT OPERATORS *****************************************/

    template <typename Data> QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& qqvc) noexcept { 
        size = qqvc.size;
        actual_length = qqvc.actual_length;
        delete [] storage;
        storage = Vector<Data>::array_safe_alloc(actual_length);
        for (sizetype i = 0; i < qqvc.size; i++) storage[i] = qqvc.storage[(i+qqvc.head_index)%(qqvc.actual_length)];
        head_index = 0;
        return *this;
    }
    
    template <typename Data> inline QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& qqvc) noexcept { 
        std::swap(actual_length,qqvc.actual_length);
        std::swap(head_index,qqvc.head_index);
        Vector<Data>::operator=(std::move(qqvc));
        return *this;
    }




    /******************************************* COMPARISON OPERATORS *****************************************/

    template <typename Data> inline bool QueueVec<Data>::operator!=(const QueueVec<Data>& stk) const noexcept { 
        return not this->operator==(stk); 
    }

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



    /********************************************* CLEAR / RESIZE *****************************************/
    // notice that since the Vector implementations works on size, they need to be overrided to work on actual_length
    // having the variable actual_length to rappresent the memory footprint allows us to avoid overrding Empty and Size, 
    // wich indeed allows us to make them not virtual and therefore to reduce the total virtual overhead

    template <typename Data> void QueueVec<Data>::Clear() { 
        delete [] storage;
        storage = nullptr;
        size = 0;
        actual_length = 0;    
        head_index = 0;
    }

    template <typename Data> void QueueVec<Data>::Resize(sizetype newlength){
        Data* tmp = Vector<Data>::array_safe_alloc(newlength);
        for (int i = 0; i < size; i++) { 
            tmp[i] = storage[(i+head_index) % actual_length];
        }
        actual_length = newlength;
        head_index = 0;
        std::swap(storage, tmp);
        delete [] tmp;
    }



    /***************************************** INSERTIONS AND DELETIONS **********************************/

    template <typename Data> void QueueVec<Data>::Enqueue(const Data& value) noexcept {
        if (size + 1 > actual_length) Resize(actual_length * 2 + 1);
        storage[(head_index + size++)%actual_length] = value;
    }

    template <typename Data> void QueueVec<Data>::Enqueue(Data&& value) noexcept {
        if (size + 1 > actual_length) Resize(actual_length * 2 + 1);
        storage[(head_index + size++)%actual_length] = std::move(value);
    }

    template <typename Data> void QueueVec<Data>::Dequeue(){
        if (size == 0) throw std::length_error("Dequeue() method called on empty queue");
        ++head_index %= (actual_length);
        if (--size < actual_length/4) Resize(std::max(actual_length / 2, QUEUEVEC_MINIMUM_LENGTH));  
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