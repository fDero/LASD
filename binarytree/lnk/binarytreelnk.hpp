
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../binarytree.hpp"
#include "../../container/mappable.hpp"

namespace lasd {

  template <typename Data> class BinaryTreeLnk 
    : public virtual MutableBinaryTree<Data> 
    , public virtual ClearableContainer
  {
    public:
      using Node = typename BinaryTree<Data>::Node;
      using MutableNode = typename MutableBinaryTree<Data>::MutableNode;

    protected:
      
      using Container::size;

      struct NodeLnk 
        : public virtual MutableBinaryTree<Data>::MutableNode 
      { 
        NodeLnk(const Data&) noexcept;
        NodeLnk(Data&&) noexcept;
        virtual ~NodeLnk() noexcept;
        
        NodeLnk* left = nullptr;
        NodeLnk* right = nullptr;
        Data value;

        virtual const Data& Element() const noexcept override;      
        virtual Data& Element() noexcept override;

        virtual const Node& RightChild() const override;      
        virtual MutableNode& RightChild() override;

        virtual const Node& LeftChild() const override;      
        virtual MutableNode& LeftChild() override;
      };

      NodeLnk* root = nullptr;
      BinaryTreeLnk() = default;
      
    public:

      BinaryTreeLnk(const BinaryTreeLnk&) noexcept;
      BinaryTreeLnk(BinaryTreeLnk&&) noexcept;
      BinaryTreeLnk(const MappableContainer<Data>&) noexcept;
      BinaryTreeLnk(MutableMappableContainer<Data>&&) noexcept;
      virtual ~BinaryTreeLnk() noexcept;

      BinaryTreeLnk& operator=(const BinaryTreeLnk&) noexcept;
      BinaryTreeLnk& operator=(BinaryTreeLnk&&) noexcept;

      virtual inline bool operator==(const BinaryTreeLnk& other) const noexcept;
      virtual inline bool operator!=(const BinaryTreeLnk& other) const noexcept;

      virtual const Node& Root() const override;
      virtual MutableNode& Root() override;

      virtual void Clear() override;

      using MapFunctor = typename BinaryTree<Data>::MapFunctor;
      using MutableMapFunctor = typename MutableBinaryTree<Data>::MutableMapFunctor;
      using FoldFunctor = typename BinaryTree<Data>::FoldFunctor;

    private:
      NodeLnk* CloneSubtree(NodeLnk*);
      void ReplaceSubtree(NodeLnk*&, NodeLnk*);
      template <typename InputType> void BuildFromMappable(InputType&&, QueueVec<NodeLnk*>&) noexcept;
  };

}

#include "binarytreelnk.cpp"