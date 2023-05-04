
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

      virtual bool operator==(const BST<Data>&) const noexcept;
      virtual bool operator!=(const BST<Data>&) const noexcept;

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

      using BinaryTreeLnk<Data>::Map;
      using BinaryTreeLnk<Data>::PreOrderMap;
      using BinaryTreeLnk<Data>::PostOrderMap;
      using BinaryTreeLnk<Data>::InOrderMap;
      using BinaryTreeLnk<Data>::BreadthMap;
      
      using BinaryTreeLnk<Data>::Fold;
      using BinaryTreeLnk<Data>::PreOrderFold;
      using BinaryTreeLnk<Data>::PostOrderFold;
      using BinaryTreeLnk<Data>::InOrderFold;
      using BinaryTreeLnk<Data>::BreadthFold;
      
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

      void DeleteJustThisNode(NodeLnk*&);

      template<typename Value> bool InsertHelper(Value&&);
      void Detatch(NodeLnk*&);
    };
}

#include "bst.cpp"
