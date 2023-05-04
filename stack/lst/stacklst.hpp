
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../stack.hpp"
#include "../../list/list.hpp"
#include "../../container/mappable.hpp"

namespace lasd {

  template <typename Data> class StackLst 
    : public virtual Stack<Data>, virtual List<Data> 
  {
    protected:
      using List<Data>::Node;
      using Container::size;
    public:
      StackLst() = default;
      StackLst(const MappableContainer<Data>&) noexcept;
      StackLst(MutableMappableContainer<Data>&&) noexcept;
      StackLst(const StackLst&) noexcept;
      StackLst(StackLst&&) noexcept;
      virtual ~StackLst() = default; 
      
      virtual inline StackLst& operator=(const StackLst&) noexcept;
      virtual inline StackLst& operator=(StackLst&&) noexcept;

      virtual inline bool operator==(const StackLst&) const noexcept;
      virtual inline bool operator!=(const StackLst&) const noexcept;

      using List<Data>::Clear;
      using List<Data>::Size;
      using List<Data>::Empty;

      virtual inline void Push(const Data&) noexcept override;
      virtual inline void Push(Data&&) noexcept override;

      virtual inline void Pop() override;
 
      virtual inline const Data& Top() const override;
      virtual inline Data& Top() override;
      
      using Stack<Data>::TopNPop;
  };
}

#include "stacklst.cpp"