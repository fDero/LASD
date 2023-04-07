
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../queue.hpp"
#include "../../vector/vector.hpp"
#include "../../container/mappable.hpp"

namespace lasd {

  template <typename Data> class QueueVec : public virtual Queue<Data>, virtual Vector<Data> {
    protected:
      using Vector<Data>::storage;
      using Vector<Data>::size;
      sizetype actual_length = 0;
      sizetype head_index = 0;
      sizetype tail_index = 0; 
    public:

      QueueVec();
      QueueVec(const MappableContainer<Data>&);
      QueueVec(MutableMappableContainer<Data>&&);
      QueueVec(const QueueVec&);
      QueueVec(QueueVec&&);
      virtual ~QueueVec(); 
      
      virtual inline QueueVec& operator=(const QueueVec&);
      virtual inline QueueVec& operator=(QueueVec&&);

      virtual bool operator==(const QueueVec&) const noexcept;
      virtual inline bool operator!=(const QueueVec&) const noexcept;

      using Vector<Data>::Size;
      using Vector<Data>::Empty;
      
      virtual inline void Clear() override;
      virtual void Resize(sizetype) override;

      using Vector<Data>::Map;
      using Vector<Data>::PreOrderMap;
      using Vector<Data>::PostOrderMap;

      using Vector<Data>::Fold;
      using Vector<Data>::PreOrderFold;
      using Vector<Data>::PostOrderFold;

      virtual void Enqueue(const Data&) override;
      virtual void Enqueue(Data&&) override;

      virtual inline void Dequeue() override;
 
      virtual const Data& Head() const override;
      virtual Data& Head() override;
      
      using Stack<Data>::HeadNDequeue;
  };
}

#include "queuevec.cpp"