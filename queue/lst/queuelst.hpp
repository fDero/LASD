
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../queue.hpp"
#include "../../list/list.hpp"
#include "../../container/mappable.hpp"

namespace lasd {

  template <typename Data> class QueueLst : public virtual Queue<Data> , virtual List<Data> {
    protected:
      using List<Data>::Node;
      using List<Data>::size;
    public:
    
      QueueLst();
      QueueLst(const MappableContainer<Data>&);
      QueueLst(MutableMappableContainer<Data>&&);
      QueueLst(const QueueLst&);
      QueueLst(QueueLst&&);
      virtual ~QueueLst(); 
      
      virtual inline QueueLst& operator=(const QueueLst&);
      virtual inline QueueLst& operator=(QueueLst&&);

      virtual inline bool operator==(const QueueLst&) const noexcept;
      virtual inline bool operator!=(const QueueLst&) const noexcept;

      using List<Data>::Clear;
      using List<Data>::Size;
      using List<Data>::Empty;

      virtual inline void Enqueue(const Data&) override;
      virtual inline void Enqueue(Data&&) override;

      virtual inline void Dequeue() override;

      virtual inline const Data& Head() const override;
      virtual inline Data& Head() override;
      
      using Queue<Data>::HeadNDequeue;
  };
}

#include "queuelst.cpp"