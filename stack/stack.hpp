
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../container/container.hpp"

namespace lasd {

  template <typename Data> class Stack : public virtual ClearableContainer {
    public:
    
      Stack() = default;
      Stack(const Stack&) = default;
      Stack(Stack&&) = default;
      Stack(const MappableContainer<Data>&);
      Stack(MutableMappableContainer<Data>&&);
      virtual ~Stack() = default; 

      virtual bool operator==(const Stack&) const = delete;
      virtual bool operator!=(const Stack&) const = delete;

      virtual Stack& operator=(const Stack&) = delete;
      virtual Stack& operator=(Stack&&) = delete;
  
      virtual void Push(const Data&) = 0;
      virtual void Push(Data&&) = 0;
      virtual void Pop() = 0;
    
      virtual const Data& Top() const = 0;
      virtual Data& Top() = 0;
      
      Data TopNPop();
  };
}

#include "stack.cpp"