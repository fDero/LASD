
// FRANCESCO DE ROSA N86004379

#pragma once

#include "stack.hpp"

namespace lasd {
    
    template <typename Data> Stack<Data>::Stack(const MappableContainer<Data>& container) {
        container.Map([this](const Data& value){ this->Push(value); });
    }

    template <typename Data> Stack<Data>::Stack(MutableMappableContainer<Data>&& container) {
        container.Map([this](Data& value){ this->Push(std::move(value)); });
    }
      
    template <typename Data> Data Stack<Data>::TopNPop() {
        Data tmp = std::move(Top());
        Pop();
        return tmp;
    }
}