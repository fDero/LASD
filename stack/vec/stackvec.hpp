
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../stack.hpp"
#include "../../vector/vector.hpp"
#include "../../container/mappable.hpp"

namespace lasd {

  template <typename Data> class StackVec 
    : public virtual Stack<Data>, virtual Vector<Data> 
  {
    protected:
      using Vector<Data>::size;
      using Vector<Data>::storage;
      sizetype actual_length = 0;
    public:
      
      StackVec() noexcept;
      StackVec(const MappableContainer<Data>&) noexcept ;
      StackVec(MutableMappableContainer<Data>&&) noexcept;
      StackVec(const StackVec&) noexcept;
      StackVec(StackVec&&) noexcept;
      virtual ~StackVec() = default; 
      
      virtual inline StackVec& operator=(const StackVec&) noexcept;
      virtual inline StackVec& operator=(StackVec&&) noexcept;

      virtual inline bool operator==(const StackVec&) const noexcept;
      virtual inline bool operator!=(const StackVec&) const noexcept;

      using Vector<Data>::Size;
      using Vector<Data>::Empty;
      
      virtual inline void Clear() override;
      virtual void Resize(sizetype) override;

      virtual void Push(const Data&) noexcept override;
      virtual void Push(Data&&) noexcept override;

      virtual inline void Pop() override;
 
      virtual const Data& Top() const override;
      virtual Data& Top() override;
      
      using Stack<Data>::TopNPop;
  };
}

#include "stackvec.cpp"