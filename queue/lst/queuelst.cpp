
// FRANCESCO DE ROSA N86004379

#pragma once

#include "queuelst.hpp"

namespace lasd {

    /************************************* CONSTRUCTORS AND DISTRUCTORS *******************************/

    template <typename Data> QueueLst<Data>::QueueLst(const QueueLst& qqlst) noexcept : List<Data>(qqlst) {}
    template <typename Data> QueueLst<Data>::QueueLst(QueueLst&& qqlst) noexcept : List<Data>(std::move(qqlst)) {}

    template <typename Data> QueueLst<Data>::QueueLst(MutableMappableContainer<Data>&& mmc) noexcept {
        mmc.Map([this](Data& value){ this->Enqueue(std::move(value)); });   
    }

    template <typename Data> QueueLst<Data>::QueueLst(const MappableContainer<Data>& mc) noexcept {
        mc.Map([this](const Data& value){ this->Enqueue(value); });
    }
    



    /************************************** ASSIGNMENT OPERATORS ***************************************/

    template <typename Data> inline QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& stk) noexcept{ 
        List<Data>::operator=(stk); 
        return *this; 
    }
    
    template <typename Data> inline QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& stk) noexcept { 
        List<Data>::operator=(std::move(stk)); 
        return *this; 
    }




    /*************************************** COMPARISON OPERATORS *************************************/

    template <typename Data> inline bool QueueLst<Data>::operator==(const QueueLst<Data>& stk) const noexcept { return List<Data>::operator==(stk); }
    template <typename Data> inline bool QueueLst<Data>::operator!=(const QueueLst<Data>& stk) const noexcept { return List<Data>::operator!=(stk); }

    
    
    
    /**************************************** INSERTION AND DELETIONS *********************************/

    template <typename Data> inline void QueueLst<Data>::Enqueue(const Data& value) noexcept { List<Data>::InsertAtBack(value); }
    template <typename Data> inline void QueueLst<Data>::Enqueue(Data&& value) noexcept { List<Data>::InsertAtBack(std::move(value)); }
    
    template <typename Data> inline void QueueLst<Data>::Dequeue() { 
        if (size == 0) throw std::length_error("Dequeue() method called on empty queue");
        List<Data>::RemoveFromFront(); 
    }
     
    template <typename Data> inline const Data& QueueLst<Data>::Head() const { 
        if (size == 0) throw std::length_error("Head() method called on empty queue");
        return List<Data>::Front(); 
    }
    
    template <typename Data> inline Data& QueueLst<Data>::Head() { 
        if (size == 0) throw std::length_error("Head() method called on empty queue");
        return List<Data>::Front(); 
    }
}