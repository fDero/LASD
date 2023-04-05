
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../container/container.hpp"

namespace lasd {

  template <typename Data> class Stack : public virtual ClearableContainer {
    public:
      Stack() = default;
      Stack(const Stack&) = default;
      Stack(Stack&&) = default;
      virtual ~Stack() = default; 

      virtual bool operator==(const Stack&) const = delete;
      virtual bool operator!=(const Stack&) const = delete;

      virtual Stack& operator=(const Stack&) = delete;
      virtual Stack& operator=(Stack&&) = delete;
  
      virtual const Data& Top() const = 0;  // (non-mutable version; concrete function must throw std::length_error when empty)
      virtual Data& Top() = 0;              // (mutable version; concrete function must throw std::length_error when empty)
      virtual void Pop() = 0;               // (concrete function must throw std::length_error when empty)
    
      virtual Data TopNPop();
      virtual void Push(const Data&) = 0;
      virtual void Push(Data&&) = 0;
  };
}

#include "stack.cpp"