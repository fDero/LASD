
// FRANCESCO DE ROSA N86004379  

#pragma once

#include <stdexcept>

namespace lasd {

  /************************************************ COMPARISON OPERATORS ***************************************/

  template<typename Data> bool LinearContainer<Data>::operator==(const LinearContainer<Data>& sequence) const noexcept {
    if(size != sequence.size) return false;
    for (int i = 0; i < sequence.size; i++)
      if (this->operator[](i) != sequence.operator[](i)) return false;
    return true;
  }

  template<typename Data> bool inline LinearContainer<Data>::operator!=(const LinearContainer<Data>& sequence) const noexcept {
    return not this->operator==(sequence);
  }


  /**************************************************** DATA ACCESS METHODS **************************************/

  template<typename Data> const Data& LinearContainer<Data>::Front() const {
    if (size == 0) throw std::length_error("Front() method invoked on an empty container");
    return this->operator[](0);
  }

  template<typename Data> Data& LinearContainer<Data>::Front() {
    if (size == 0) throw std::length_error("Front() method invoked on an empty container");
    return this->operator[](0);
  }

  template<typename Data> const Data& LinearContainer<Data>::Back() const {
    if (size == 0) throw std::length_error("Back() method invoked on an empty container");
    return this->operator[](size-1);
  }

  template<typename Data> Data& LinearContainer<Data>::Back() {
    if (size == 0) throw std::length_error("Back() method invoked on an empty container");
    return this->operator[](size-1);
  }

  template<typename Data> bool LinearContainer<Data>::Exists(const Data& target) const noexcept {
    for(int i = 0; i < size; i++)
        if (this->operator[](i) == target) return true;
    return false;
  }

  /********************************************************* MAPS ***********************************************/
  // note that the const version are implicitly derived from PreOrderMappableContainer and 
  // PostOrderMappableContainer, and are both defined in "mappable.cpp". Moreover to resolve the diamond structure 
  // problem that arises from having Map and Fold defined in both the classes LinearContainer is extending, here 
  // they are overrided. The override just forward the call to the relative PreOrders

  template<typename Data> void LinearContainer<Data>::PreOrderMap(MutableMapFunctor functor) {
    for (sizetype i = 0; i < size; i++) functor(this->operator[](i));
  }

  template<typename Data> void LinearContainer<Data>::PostOrderMap(MutableMapFunctor functor) {
    for (sizetype i = size; i > 0; i--) functor(this->operator[](i-1));
  }

  template<typename Data> void inline LinearContainer<Data>::Fold(FoldFunctor functor, void* accumulator) const { PreOrderFold(functor,accumulator); }
  template<typename Data> void inline LinearContainer<Data>::Map(MapFunctor functor) const { PreOrderMap(functor); }
  template<typename Data> void inline LinearContainer<Data>::Map(MutableMapFunctor functor) { PreOrderMap(functor); }
}