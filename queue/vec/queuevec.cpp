
// FRANCESCO DE ROSA N86004379

#pragma once

#include "queuevec.hpp"
#include <cassert>

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
        while (i != tail_index && j != stk.tail_index){
            if (storage[i] != stk.storage[j]) return false;
            ++i %= actual_length;
            ++j %= stk.actual_length;
        }
        assert (i == tail_index and j == stk.tail_index);
        return storage[i] == stk.storage[j];
    }

    template <typename Data> QueueVec<Data>& QueueVec<Data>::operator=(const QueueVec<Data>& qqvc) { 
        Resize(qqvc.actual_length);
        qqvc.PostOrderMap([this](const Data& value){ this->Enqueue(value); });  
        return *this;
    }
    
    template <typename Data> inline QueueVec<Data>& QueueVec<Data>::operator=(QueueVec<Data>&& qqvc) { 
        actual_length = qqvc.actual_length;
        head_index = qqvc.head_index;
        tail_index = qqvc.tail_index;
        Vector<Data>::operator=(std::move(qqvc));
        return *this;
    }    

    template <typename Data> inline void QueueVec<Data>::Clear() { 
        Vector<Data>::Clear();
        actual_length = 0;    
        head_index = 0;
        tail_index = 0;
    }
}