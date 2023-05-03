
// FRANCESCO DE ROSA N86004379

#pragma once

#include "iterator.hpp"
#include "../binarytree/binarytree.hpp"
#include "binarytree-const-iterators.hpp"

namespace lasd {

  template <typename Data> class BinaryTreeMutableIterator 
    : public virtual BinaryTreeIterator<Data>
    , public virtual MutableIterator<Data>
  {
    protected:
      using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
      using Node = typename BinaryTree<Data>::Node;
      using BinaryTreeIterator<Data>::current;
      using BinaryTreeIterator<Data>::root; 
    public:
      BinaryTreeMutableIterator() = default;
      BinaryTreeMutableIterator(const BinaryTreeMutableIterator&) = default;
      BinaryTreeMutableIterator(BinaryTreeMutableIterator&&) = default;
      virtual ~BinaryTreeMutableIterator() = default;
      
      virtual inline const Data& operator*() const override;
      virtual Data& operator*() override;
  };






  template <typename Data> class BTPreOrderMutableIterator 
    : public virtual BTPreOrderIterator<Data>
    , public virtual BinaryTreeMutableIterator<Data>
  {
    protected:
      using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
      using Node = typename BinaryTree<Data>::Node;
      using BTPreOrderIterator<Data>::suspended;
      using BinaryTreeIterator<Data>::current;
      using BinaryTreeIterator<Data>::root; 
    public:
      BTPreOrderMutableIterator(const MutableBinaryTree<Data>& tree) noexcept : BTPreOrderIterator<Data>(tree) {};
      BTPreOrderMutableIterator(const BTPreOrderMutableIterator&) = default;
      BTPreOrderMutableIterator(BTPreOrderMutableIterator&&) = default;
      virtual ~BTPreOrderMutableIterator() = default;

      BTPreOrderMutableIterator& operator=(const BTPreOrderMutableIterator&) = default;
      BTPreOrderMutableIterator& operator=(BTPreOrderMutableIterator&&) = default;

      using BTPreOrderIterator<Data>::operator==;
      using BTPreOrderIterator<Data>::operator!=;
      using BinaryTreeMutableIterator<Data>::operator*;
      using BTPreOrderIterator<Data>::operator++;
      using BinaryTreeIterator<Data>::Terminated;
      using BTPreOrderIterator<Data>::Reset;
  };






  template <typename Data> class BTPostOrderMutableIterator 
    : public virtual BTPostOrderIterator<Data>
    , public virtual BinaryTreeMutableIterator<Data>
  {
    protected:
      using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
      using Node = typename BinaryTree<Data>::Node;
      using BTPostOrderIterator<Data>::suspended;
      using BinaryTreeIterator<Data>::current;
      using BinaryTreeIterator<Data>::root; 
    public:
      BTPostOrderMutableIterator(const MutableBinaryTree<Data>& tree) noexcept : BTPostOrderIterator<Data>(tree) {};
      BTPostOrderMutableIterator(const BTPostOrderMutableIterator&) = default;
      BTPostOrderMutableIterator(BTPostOrderMutableIterator&&) = default;
      virtual ~BTPostOrderMutableIterator() = default;

      BTPostOrderMutableIterator& operator=(const BTPostOrderMutableIterator&) = default;
      BTPostOrderMutableIterator& operator=(BTPostOrderMutableIterator&&) = default;

      using BTPostOrderIterator<Data>::operator==;
      using BTPostOrderIterator<Data>::operator!=;
      using BinaryTreeMutableIterator<Data>::operator*;
      using BTPostOrderIterator<Data>::operator++;
      using BinaryTreeIterator<Data>::Terminated;
      using BTPostOrderIterator<Data>::Reset;
  };






  template <typename Data> class BTInOrderMutableIterator
    : public virtual BTInOrderIterator<Data>
    , public virtual BinaryTreeMutableIterator<Data>
  {
    protected:
      using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
      using Node = typename BinaryTree<Data>::Node;
      using BTInOrderIterator<Data>::suspended;
      using BinaryTreeIterator<Data>::current;
      using BinaryTreeIterator<Data>::root; 
    public:
      BTInOrderMutableIterator(const MutableBinaryTree<Data>& tree) noexcept : BTInOrderIterator<Data>(tree) {};
      BTInOrderMutableIterator(const BTInOrderMutableIterator&) = default;
      BTInOrderMutableIterator(BTInOrderMutableIterator&&) = default;
      virtual ~BTInOrderMutableIterator() = default;

      BTInOrderMutableIterator& operator=(const BTInOrderMutableIterator&) = default;
      BTInOrderMutableIterator& operator=(BTInOrderMutableIterator&&) = default;

      using BTInOrderIterator<Data>::operator==;
      using BTInOrderIterator<Data>::operator!=;
      using BinaryTreeMutableIterator<Data>::operator*;
      using BTInOrderIterator<Data>::operator++;
      using BinaryTreeIterator<Data>::Terminated;
      using BTInOrderIterator<Data>::Reset;
  };





  
  template <typename Data> class BTBreadthMutableIterator 
    : public virtual BTBreadthIterator<Data>
    , public virtual BinaryTreeMutableIterator<Data>
  {
    protected:
      using MutableNode = typename MutableBinaryTree<Data>::MutableNode;
      using Node = typename BinaryTree<Data>::Node;
      using BTBreadthIterator<Data>::suspended;
      using BinaryTreeIterator<Data>::current;
      using BinaryTreeIterator<Data>::root; 
    public:
      BTBreadthMutableIterator(const MutableBinaryTree<Data>& tree) noexcept : BTBreadthIterator<Data>(tree) {};
      BTBreadthMutableIterator(const BTBreadthMutableIterator&) = default;
      BTBreadthMutableIterator(BTBreadthMutableIterator&&) = default;
      virtual ~BTBreadthMutableIterator() = default;

      BTBreadthMutableIterator& operator=(const BTBreadthMutableIterator&) = default;
      BTBreadthMutableIterator& operator=(BTBreadthMutableIterator&&) = default;

      using BTBreadthIterator<Data>::operator==;
      using BTBreadthIterator<Data>::operator!=;
      using BinaryTreeMutableIterator<Data>::operator*;
      using BTBreadthIterator<Data>::operator++;
      using BinaryTreeIterator<Data>::Terminated;
      using BTBreadthIterator<Data>::Reset;
  };
}

#include "binarytree-iterators.cpp"