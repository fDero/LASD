
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../queue.hpp"
#include "../../list/list.hpp"
#include "../../container/mappable.hpp"

namespace lasd {

  template <typename Data> class QueueLst 
    : public virtual Queue<Data> , virtual List<Data> 
  {
    protected:
      using List<Data>::Node;
      using List<Data>::size;
    public:
    
      QueueLst() = default;
      QueueLst(const MappableContainer<Data>&) noexcept;
      QueueLst(MutableMappableContainer<Data>&&) noexcept;
      QueueLst(const QueueLst&) noexcept;
      QueueLst(QueueLst&&) noexcept;
      virtual ~QueueLst() = default; 
      
      virtual inline QueueLst& operator=(const QueueLst&) noexcept;
      virtual inline QueueLst& operator=(QueueLst&&) noexcept;

      virtual inline bool operator==(const QueueLst&) const noexcept;
      virtual inline bool operator!=(const QueueLst&) const noexcept;

      using List<Data>::Clear;
      using List<Data>::Size;
      using List<Data>::Empty;

      virtual inline void Enqueue(const Data&) noexcept override;
      virtual inline void Enqueue(Data&&) noexcept override;

      virtual inline void Dequeue() override;

      virtual inline const Data& Head() const override;
      virtual inline Data& Head() override;
      
      using Queue<Data>::HeadNDequeue;
  };
}

#include "queuelst.cpp"