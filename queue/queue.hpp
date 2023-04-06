
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../container/container.hpp"

namespace lasd {

  template <typename Data> class Queue : public virtual ClearableContainer {
    public:
      
      Queue() = default;
      Queue(const Queue&) = default;
      Queue(Queue&&) = default;
      virtual ~Queue() = default;
      
      virtual bool operator==(const Queue&) const noexcept = delete;
      virtual bool operator!=(const Queue&) const noexcept = delete;

      virtual Queue& operator=(const Queue&) = delete;
      virtual Queue& operator=(Queue&&) = delete;

      virtual void Enqueue(const Data&) = 0;
      virtual void Enqueue(Data&&) = 0;
      virtual void Dequeue() = 0;
      
      virtual const Data& Head() const = 0;
      virtual Data& Head() = 0;
      
      Data HeadNDequeue();
  };
}

#include "queue.cpp"