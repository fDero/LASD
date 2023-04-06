
// FRANCESCO DE ROSA N86004379

#pragma once

#include "queuelst.hpp"

namespace lasd {

    template <typename Data> QueueLst<Data>::QueueLst() : List<Data>() {}
    template <typename Data> QueueLst<Data>::QueueLst(const QueueLst& qqlst) : List<Data>(qqlst) {}
    template <typename Data> QueueLst<Data>::QueueLst(QueueLst&& qqlst) : List<Data>(qqlst) {}
    template <typename Data> QueueLst<Data>::~QueueLst() = default;

    template <typename Data> inline bool QueueLst<Data>::operator==(const QueueLst<Data>& stk) const noexcept { return List<Data>::operator==(stk); }
    template <typename Data> inline bool QueueLst<Data>::operator!=(const QueueLst<Data>& stk) const noexcept { return List<Data>::operator!=(stk); }

    template <typename Data> inline QueueLst<Data>& QueueLst<Data>::operator=(const QueueLst<Data>& stk) { List<Data>::operator=(stk); return *this; }
    template <typename Data> inline QueueLst<Data>& QueueLst<Data>::operator=(QueueLst<Data>&& stk) { List<Data>::operator=(stk); return *this; }

    template <typename Data> inline void QueueLst<Data>::Enqueue(const Data& value) { List<Data>::InsertAtBack(value); }
    template <typename Data> inline void QueueLst<Data>::Enqueue(Data&& value) { List<Data>::InsertAtBack(value); }
    template <typename Data> inline void QueueLst<Data>::Dequeue() { List<Data>::RemoveFromFront(); }
     
    template <typename Data> inline const Data& QueueLst<Data>::Head() const { return List<Data>::Front(); }
    template <typename Data> inline Data& QueueLst<Data>::Head() { return List<Data>::Front(); }
}