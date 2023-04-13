
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../stack.hpp"
#include "../../vector/vector.hpp"
#include "../../container/mappable.hpp"

namespace lasd {

  template <typename Data> class StackVec : public virtual Stack<Data>, virtual Vector<Data> {
    protected:
      using Vector<Data>::size;
      using Vector<Data>::storage;
      sizetype actual_length = 0;
    public:
      
      StackVec();
      StackVec(const MappableContainer<Data>&);
      StackVec(MutableMappableContainer<Data>&&);
      StackVec(const StackVec&);
      StackVec(StackVec&&);
      virtual ~StackVec(); 
      
      virtual inline StackVec& operator=(const StackVec&);
      virtual inline StackVec& operator=(StackVec&&);

      virtual inline bool operator==(const StackVec&) const noexcept;
      virtual inline bool operator!=(const StackVec&) const noexcept;

      using Vector<Data>::Size;
      using Vector<Data>::Empty;
      
      virtual inline void Clear() override;
      virtual void Resize(sizetype) override;

      virtual void Push(const Data&) override;
      virtual void Push(Data&&) override;

      virtual inline void Pop() override;
 
      virtual const Data& Top() const override;
      virtual Data& Top() override;
      
      using Stack<Data>::TopNPop;
  };
}

#include "stackvec.cpp"