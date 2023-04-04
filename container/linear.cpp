
// FRANCESCO DE ROSA N86004379  

#pragma once

#include <stdexcept>

namespace lasd {

  template<typename Data> bool LinearContainer<Data>::operator==(const LinearContainer<Data>& sequence) const noexcept {
    if(size != sequence.size) return false;
    for (int i = 0; i < sequence.size; i++)
      if (this->operator[](i) != sequence.operator[](i)) return false;
    return true;
  }

  template<typename Data> bool LinearContainer<Data>::operator!=(const LinearContainer<Data>& sequence) const noexcept {
    return not this->operator==(sequence);
  }

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

  template<typename Data> void SortableLinearContainer<Data>::Sort() {
    for (int current = 0; current < size; current++){
      for (int i = current; i > 0 and this->operator[](i) < this->operator[](i-1); i--){
        std::swap(this->operator[](i), this->operator[](i-1));
      }
    }
  }

  template<typename Data> void LinearContainer<Data>::PreOrderMap(MutableMapFunctor functor) {
    for (int i = 0; i < size; i++) functor(this->operator[](i));
  }

  template<typename Data> void LinearContainer<Data>::PostOrderMap(MutableMapFunctor functor) {
    for (int i = size-1; i >= 0; i--) functor(this->operator[](i));
  }

  template<typename Data> void LinearContainer<Data>::Fold(FoldFunctor functor, void* accumulator) const { PreOrderFold(functor,accumulator); }
  template<typename Data> void LinearContainer<Data>::Map(MapFunctor functor) const { PreOrderMap(functor); }
  template<typename Data> void LinearContainer<Data>::Map(MutableMapFunctor functor) { PreOrderMap(functor); }
}