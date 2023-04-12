
// FRANCESCO DE ROSA N86004379

#pragma once

#include "stack.hpp"

namespace lasd {
      
    template <typename Data> Data Stack<Data>::TopNPop() {
        if (Empty()) throw std::length_error("TopNPop() method called on empty stack");
        Data tmp = std::move(Top());
        Pop();
        return tmp;
    }
}