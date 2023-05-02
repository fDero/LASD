
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../container/mappable.hpp"
#include "../container/dictionary.hpp"

namespace lasd {

  template <typename Data> class BST 
    : public virtual ClearableContainer
    , public virtual DictionaryContainer<Data>
    , public virtual BinaryTree<Data>
    , virtual BinaryTreeLnk<Data>
  {
    protected:
      using Container::size;
      using NodeLnk = typename BinaryTreeLnk<Data>::NodeLnk;
      using BinaryTreeLnk<Data>::root;
    
    public: 
      BST() = default;
      BST(const BST&) noexcept;
      BST(BST&&) noexcept;
      BST(const MappableContainer<Data>&) noexcept;
      BST(MutableMappableContainer<Data>&&) noexcept;
      virtual ~BST() = default;

      using BinaryTree<Data>::operator==;
      using BinaryTree<Data>::operator!=;

      BST& operator=(const BST&) noexcept;
      BST& operator=(BST&&) noexcept;

      const Data& Min() const;
      Data MinNRemove();
      void RemoveMin();

      const Data& Max() const;
      Data MaxNRemove();
      void RemoveMax();

      const Data& Predecessor(const Data&) const;
      Data PredecessorNRemove(const Data&);
      void RemovePredecessor(const Data&);

      const Data& Successor(const Data&) const;
      Data SuccessorNRemove(const Data&);
      void RemoveSuccessor(const Data&);

      using Container::Empty;
      using Container::Size;

      using BinaryTree<Data>::Root;
      using BinaryTreeLnk<Data>::Clear;

      virtual inline bool Insert(const Data&) override;
      virtual inline bool Insert(Data&&) override;
      
      virtual bool Remove(const Data&) override;
      virtual inline bool Exists(const Data&) const noexcept override;

    private:
      NodeLnk*& FindNodePointer(const Data&, NodeLnk*&);
      NodeLnk*& FindPredecessorPointer(const Data&, NodeLnk*&);
      NodeLnk*& FindSuccessorPointer(const Data&, NodeLnk*&);
    
      NodeLnk*& FindMinInSubtree(NodeLnk*&);
      NodeLnk*& FindMaxInSubtree(NodeLnk*&);

      template<typename Value> bool InsertHelper(Value&&);
      void Detatch(NodeLnk*&);
    };
}

#include "bst.cpp"
