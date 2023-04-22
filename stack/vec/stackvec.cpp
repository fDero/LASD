
// FRANCESCO DE ROSA N86004379

#pragma once

#include "stackvec.hpp"

namespace lasd {

    sizetype constexpr STACKVEC_MINIMUM_LENGTH = 8;

    /*********************************** CONSTRUCTORS AND DISTRUCTORS *******************************/

    template <typename Data> StackVec<Data>::StackVec() { 
        if constexpr (STACKVEC_MINIMUM_LENGTH != 0) {
            actual_length = STACKVEC_MINIMUM_LENGTH;
            storage = new Data[STACKVEC_MINIMUM_LENGTH];
        } 
    }

    template <typename Data> StackVec<Data>::~StackVec() = default;

    template <typename Data> StackVec<Data>::StackVec(const MappableContainer<Data>& mc) { 
        Resize(mc.Size());
        mc.Map([this](const Data& value){ this->Push(value); });
    }


    template <typename Data> StackVec<Data>::StackVec(MutableMappableContainer<Data>&& mmc) { 
        Resize(mmc.Size());
        mmc.Map([this](Data& value){ this->Push(std::move(value)); });
    }

    template <typename Data> StackVec<Data>::StackVec(const StackVec& stk) { this->operator=(stk); }
    template <typename Data> StackVec<Data>::StackVec(StackVec&& stk) { this->operator=(std::move(stk)); }
    



    /*************************************** ASSIGNMENT OPERATORS **********************************/

    template <typename Data> StackVec<Data>& StackVec<Data>::operator=(const StackVec<Data>& stk) { 
        size = stk.size;
        Resize(stk.actual_length);
        std::copy(stk.storage, stk.storage + size, storage);
        return *this;
    }
    
    template <typename Data> inline StackVec<Data>& StackVec<Data>::operator=(StackVec<Data>&& stk) { 
        std::swap(actual_length,stk.actual_length);
        Vector<Data>::operator=(std::move(stk));
        return *this;
    }




    /************************************** COMPARISON OPERATORS **********************************/

    template <typename Data> inline bool StackVec<Data>::operator==(const StackVec<Data>& stk) const noexcept { return Vector<Data>::operator==(stk); }
    template <typename Data> inline bool StackVec<Data>::operator!=(const StackVec<Data>& stk) const noexcept { return Vector<Data>::operator!=(stk); }




    /*************************************** RESIZE / CLEAR ****************************************/
    // notice that since the Vector implementations works on size, they need to be overrided to work on actual_length
    // having the variable actual_length to rappresent the memory footprint allows us to avoid overrding Empty and Size, 
    // wich indeed allows us to make them not virtual and therefore to reduce the total virtual overhead

    template <typename Data> inline void StackVec<Data>::Clear() { 
        delete [] storage;
        storage = nullptr;
        size = 0;
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



    /****************************** DATA ACCESS OPERATORS / METHODS ********************************/

    template <typename Data> const Data& StackVec<Data>::Top() const { 
        if (size == 0) throw std::length_error("Top() method called on an empty stack");
        return Vector<Data>::Back(); 
    }
    
    template <typename Data> Data& StackVec<Data>::Top() { 
        if (size == 0) throw std::length_error("Top() method called on an empty stack");
        return Vector<Data>::Back(); 
    }

    template <typename Data> inline void StackVec<Data>::Pop(){
        if (size == 0) throw std::length_error("Pop() method called on an empty stack");
        if (--size < actual_length/4 && actual_length/2 >= STACKVEC_MINIMUM_LENGTH) Resize(actual_length/2);
    }

    template <typename Data> void StackVec<Data>::Push(const Data& value){
        if (++size >= actual_length) Resize(actual_length * 2 + 1);
        this->Back() = value;
    }

    template <typename Data> void StackVec<Data>::Push(Data&& value){
        if (++size >= actual_length) Resize(actual_length * 2 + 1);
        this->Back() = std::move(value);
    }
}
