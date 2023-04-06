
// FRANCESCO DE ROSA N86004379

#pragma once

#include "stacklst.hpp"

namespace lasd {

    template <typename Data> StackLst<Data>::StackLst() : List<Data>() {}
    template <typename Data> StackLst<Data>::StackLst(const StackLst& stcklst) : List<Data>(stcklst) {}
    template <typename Data> StackLst<Data>::StackLst(StackLst&& stcklst) : List<Data>(stcklst) {}
    template <typename Data> StackLst<Data>::~StackLst() = default;

    template <typename Data> inline bool StackLst<Data>::operator==(const StackLst<Data>& stk) const noexcept { return List<Data>::operator==(stk); }
    template <typename Data> inline bool StackLst<Data>::operator!=(const StackLst<Data>& stk) const noexcept { return List<Data>::operator!=(stk); }

    template <typename Data> inline StackLst<Data>& StackLst<Data>::operator=(const StackLst<Data>& stk) { List<Data>::operator=(stk); return *this; }
    template <typename Data> inline StackLst<Data>& StackLst<Data>::operator=(StackLst<Data>&& stk) { List<Data>::operator=(stk); return *this; }

    template <typename Data> inline void StackLst<Data>::Push(const Data& value) { List<Data>::InsertAtFront(value); }
    template <typename Data> inline void StackLst<Data>::Push(Data&& value) { List<Data>::InsertAtFront(value); }
    template <typename Data> inline void StackLst<Data>::Pop() { List<Data>::RemoveFromFront(); }
     
    template <typename Data> inline const Data& StackLst<Data>::Top() const { return List<Data>::Front(); }
    template <typename Data> inline Data& StackLst<Data>::Top() { return List<Data>::Front(); }
}