
// FRANCESCO DE ROSA N86004379

#pragma once

#include "iterator.hpp"
#include "../binarytree/binarytree.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../queue/vec/queuevec.hpp"

namespace lasd {

  template <typename Data> class BinaryTreeIterator 
    : public virtual ForwardIterator<Data>
  {
    protected:
      using Node = typename BinaryTree<Data>::Node;
      Node const* current = nullptr;
      Node const* root = nullptr;

    public:
      BinaryTreeIterator() = default;
      BinaryTreeIterator(const BinaryTreeIterator&) = default;
      BinaryTreeIterator(BinaryTreeIterator&&) = default;
      virtual ~BinaryTreeIterator() = default;

      virtual inline bool Terminated() const noexcept override;
      virtual const Data& operator*() const override;
  };








  template <typename Data> class BTPreOrderIterator 
    : public virtual ForwardIterator<Data>
    , public virtual ResettableIterator<Data>
    , public virtual BinaryTreeIterator<Data>
  {
    protected:
      using Node = BinaryTreeIterator<Data>::Node;
      using BinaryTreeIterator<Data>::current;
      using BinaryTreeIterator<Data>::root;
      StackVec<Node const*> suspended;
    public:
      BTPreOrderIterator(const BinaryTree<Data>&) noexcept;
      BTPreOrderIterator(const BTPreOrderIterator&) = default;
      BTPreOrderIterator(BTPreOrderIterator&&) = default;
      virtual ~BTPreOrderIterator() = default;
      using BinaryTreeIterator<Data>::Terminated;
      using BinaryTreeIterator<Data>::operator*;

      virtual inline bool operator==(const BTPreOrderIterator&) const noexcept;
      virtual inline bool operator!=(const BTPreOrderIterator&) const noexcept;

      BTPreOrderIterator& operator=(const BTPreOrderIterator&) = default;
      BTPreOrderIterator& operator=(BTPreOrderIterator&&) = default;

      virtual ForwardIterator<Data>& operator++() override;
      virtual void Reset() noexcept override;
  };






  template <typename Data> class BTPostOrderIterator 
    : public virtual ForwardIterator<Data>
    , public virtual ResettableIterator<Data>
    , public virtual BinaryTreeIterator<Data>
  {
    protected:
      using Node = BinaryTreeIterator<Data>::Node;
      using BinaryTreeIterator<Data>::current;
      using BinaryTreeIterator<Data>::root;
      StackVec<Node const*> suspended;
    public:
      BTPostOrderIterator(const BinaryTree<Data>&) noexcept;
      BTPostOrderIterator(const BTPostOrderIterator&) = default;
      BTPostOrderIterator(BTPostOrderIterator&&) = default;
      virtual ~BTPostOrderIterator() = default;
      using BinaryTreeIterator<Data>::Terminated;
      using BinaryTreeIterator<Data>::operator*;

      virtual inline bool operator==(const BTPostOrderIterator&) const noexcept;
      virtual inline bool operator!=(const BTPostOrderIterator&) const noexcept;

      BTPostOrderIterator& operator=(const BTPostOrderIterator&) = default;
      BTPostOrderIterator& operator=(BTPostOrderIterator&&) = default;

      virtual ForwardIterator<Data>& operator++() override;
      virtual void Reset() noexcept override;
    private:
      Node const* NavigateToLeft(Node const*);
  };





  template <typename Data> class BTInOrderIterator 
    : public virtual ForwardIterator<Data>
    , public virtual ResettableIterator<Data>
    , public virtual BinaryTreeIterator<Data>
  {
    protected:
      using Node = BinaryTreeIterator<Data>::Node;
      using BinaryTreeIterator<Data>::current;
      using BinaryTreeIterator<Data>::root;
      StackVec<Node const*> suspended;
    public:
      BTInOrderIterator(const BinaryTree<Data>&) noexcept;
      BTInOrderIterator(const BTInOrderIterator&) = default;
      BTInOrderIterator(BTInOrderIterator&&) = default;
      virtual ~BTInOrderIterator() = default;
      using BinaryTreeIterator<Data>::Terminated;
      using BinaryTreeIterator<Data>::operator*;

      virtual inline bool operator==(const BTInOrderIterator&) const noexcept;
      virtual inline bool operator!=(const BTInOrderIterator&) const noexcept;

      BTInOrderIterator& operator=(const BTInOrderIterator&) = default;
      BTInOrderIterator& operator=(BTInOrderIterator&&) = default;

      virtual ForwardIterator<Data>& operator++() override;
      virtual void Reset() noexcept override;
    private:
      Node const* NavigateToLeft(Node const*);
  };






  template <typename Data> class BTBreadthIterator 
    : public virtual ForwardIterator<Data>
    , public virtual ResettableIterator<Data>
    , public virtual BinaryTreeIterator<Data>
  {
    protected:
      using Node = BinaryTreeIterator<Data>::Node;
      using BinaryTreeIterator<Data>::current;
      using BinaryTreeIterator<Data>::root;
      QueueVec<Node const*> suspended;
    public:
      BTBreadthIterator(const BinaryTree<Data>&) noexcept;
      BTBreadthIterator(const BTBreadthIterator&) = default;
      BTBreadthIterator(BTBreadthIterator&&) = default;
      virtual ~BTBreadthIterator() = default;
      using BinaryTreeIterator<Data>::Terminated;
      using BinaryTreeIterator<Data>::operator*;

      virtual inline bool operator==(const BTBreadthIterator&) const noexcept;
      virtual inline bool operator!=(const BTBreadthIterator&) const noexcept;

      BTBreadthIterator& operator=(const BTBreadthIterator&) = default;
      BTBreadthIterator& operator=(BTBreadthIterator&&) = default;

      virtual ForwardIterator<Data>& operator++() override;
      virtual void Reset() noexcept override;
  };
}

#include "binarytree-iterators.cpp"