
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../queue.hpp"
#include "../../vector/vector.hpp"
#include "../../container/mappable.hpp"

namespace lasd {

  template <typename Data> class QueueVec 
    : public virtual Queue<Data>, virtual Vector<Data> 
  {
    protected:
      using Vector<Data>::storage;
      using Vector<Data>::size;
      sizetype actual_length = 0;
      sizetype head_index = 0;
    public:

      QueueVec() noexcept;
      QueueVec(const MappableContainer<Data>&) noexcept;
      QueueVec(MutableMappableContainer<Data>&&) noexcept;
      QueueVec(const QueueVec&) noexcept;
      QueueVec(QueueVec&&) noexcept;
      virtual ~QueueVec() = default; 
      
      virtual inline QueueVec& operator=(const QueueVec&) noexcept;
      virtual inline QueueVec& operator=(QueueVec&&) noexcept ;

      virtual bool operator==(const QueueVec&) const noexcept;
      virtual inline bool operator!=(const QueueVec&) const noexcept;

      using Vector<Data>::Size;
      using Vector<Data>::Empty;
      
      virtual void Clear() override;
      virtual void Resize(sizetype) override;

      virtual void Enqueue(const Data&) noexcept override;
      virtual void Enqueue(Data&&) noexcept override;

      virtual void Dequeue() override;
 
      virtual const Data& Head() const override;
      virtual Data& Head() override;
      
      using Queue<Data>::HeadNDequeue;
  };
}

#include "queuevec.cpp"