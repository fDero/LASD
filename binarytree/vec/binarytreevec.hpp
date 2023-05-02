
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../binarytree.hpp"

namespace lasd {

  template <typename Data> class BinaryTreeVec 
    : public virtual MutableBinaryTree<Data> 
    , public virtual ClearableContainer
  {
    public:
      using Node = typename BinaryTree<Data>::Node;
      using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
      
    protected:

      using Container::size;
  
      struct NodeVec 
        : public virtual MutableBinaryTree<Data>::MutableNode 
      { 
        NodeVec() = default;
        virtual ~NodeVec() = default;
        
        BinaryTreeVec* tree;
        sizetype index;
        Data value;

        virtual const Data& Element() const noexcept override;      
        virtual Data& Element() noexcept override;

        virtual const Node& RightChild() const override;      
        virtual MutableNode& RightChild() override;

        virtual const Node& LeftChild() const override;      
        virtual MutableNode& LeftChild() override;
      };

      friend NodeVec;
      BinaryTreeVec() = default;

      NodeVec* nodes = nullptr;
      
    public:

      BinaryTreeVec(const BinaryTreeVec&) noexcept;
      BinaryTreeVec(BinaryTreeVec&&) noexcept;
      BinaryTreeVec(const MappableContainer<Data>&) noexcept;
      BinaryTreeVec(MutableMappableContainer<Data>&&) noexcept;
      virtual ~BinaryTreeVec() noexcept;

      BinaryTreeVec& operator=(const BinaryTreeVec&) noexcept;
      BinaryTreeVec& operator=(BinaryTreeVec&&) noexcept;

      virtual bool operator==(const BinaryTree<Data>&) const noexcept;
      virtual bool operator!=(const BinaryTree<Data>&) const noexcept;
      bool operator==(const BinaryTreeVec<Data>&) const noexcept;
      bool operator!=(const BinaryTreeVec<Data>&) const noexcept;

      virtual const Node& Root() const override;
      virtual MutableNode& Root() override;

      virtual void Clear() override;

      using MapFunctor = typename BinaryTree<Data>::MapFunctor;
      using MutableMapFunctor = typename MutableBinaryTree<Data>::MutableMapFunctor;
      using FoldFunctor = typename BinaryTree<Data>::FoldFunctor;

      virtual void BreadthMap(MapFunctor) const override;
      virtual void BreadthMap(MutableMapFunctor) override;

    private:
      NodeVec* safe_nodes_alloc(sizetype) noexcept;
  };
}

#include "binarytreevec.cpp"