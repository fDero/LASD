
// FRANCESCO DE ROSA N86004379

#pragma once

#include "stacklst.hpp"

namespace lasd {

    template <typename Data> StackLst<Data>::StackLst() : List<Data>() {}
    template <typename Data> StackLst<Data>::StackLst(const StackLst& stcklst) : List<Data>(stcklst) {}
    template <typename Data> StackLst<Data>::StackLst(StackLst&& stcklst) : List<Data>(std::move(stcklst)) {}
    template <typename Data> StackLst<Data>::~StackLst() = default;

    template <typename Data> StackLst<Data>::StackLst(const MappableContainer<Data>& mc) {
        mc.Map([this](const Data& value){ this->InsertAtBack(value); });
    }

    template <typename Data> StackLst<Data>::StackLst(MutableMappableContainer<Data>&& mmc) {
        mmc.Map([this](Data& value){ this->InsertAtBack(std::move(value)); });
    }
    
    template <typename Data> inline bool StackLst<Data>::operator==(const StackLst<Data>& stk) const noexcept { return List<Data>::operator==(stk); }
    template <typename Data> inline bool StackLst<Data>::operator!=(const StackLst<Data>& stk) const noexcept { return List<Data>::operator!=(stk); }

    template <typename Data> inline StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stk) { 
        List<Data>::operator=(stk); 
        return *this; 
    }
    
    template <typename Data> inline StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stk) { 
        List<Data>::operator=(std::move(stk)); 
        return *this; 
    }

    template <typename Data> inline void StackLst<Data>::Push(const Data& value) { List<Data>::InsertAtFront(value); }
    template <typename Data> inline void StackLst<Data>::Push(Data&& value) { List<Data>::InsertAtFront(std::move(value)); }
    
    template <typename Data> inline void StackLst<Data>::Pop() {
        if (size == 0) throw std::length_error("Pop() method called on empty stack"); 
        List<Data>::RemoveFromFront(); 
    }
     
    template <typename Data> inline const Data& StackLst<Data>::Top() const { 
        if (size == 0) throw std::length_error("Top() method called on empty stack");
        return List<Data>::Front(); 
    }
    
    template <typename Data> inline Data& StackLst<Data>::Top() { 
        if (size == 0) throw std::length_error("Top() method called on empty stack");
        return List<Data>::Front(); 
    }
}