
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../stack.hpp"
#include "../../list/list.hpp"

namespace lasd {

  template <typename Data> class StackLst : public virtual Stack<Data> , virtual List<Data> {
    protected:
      using List<Data>::Node;
      using Container::size;
    public:

      StackLst();
      StackLst(const StackLst&);
      StackLst(StackLst&&);
      virtual ~StackLst(); 
      
      virtual inline StackLst& operator=(const StackLst&);
      virtual inline StackLst& operator=(StackLst&&);

      virtual inline bool operator==(const StackLst&) const noexcept;
      virtual inline bool operator!=(const StackLst&) const noexcept;

      using List<Data>::Clear;
      using List<Data>::Size;
      using List<Data>::Empty;

      using List<Data>::Map;
      using List<Data>::PreOrderMap;
      using List<Data>::PostOrderMap;

      using List<Data>::Fold;
      using List<Data>::PreOrderFold;
      using List<Data>::PostOrderFold;

      using List<Data>::Insert;
      using List<Data>::InsertAll;
      using List<Data>::InsertSome;

      using List<Data>::Remove;
      using List<Data>::RemoveAll;
      using List<Data>::RemoveSome;

      virtual inline void Push(const Data&) override;
      virtual inline void Push(Data&&) override;

      virtual inline void Pop() override;
 
      virtual inline const Data& Top() const override;
      virtual inline Data& Top() override;
      
      using Stack<Data>::TopNPop;
  };
}

#include "stacklst.cpp"