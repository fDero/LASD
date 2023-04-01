
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "testable.hpp"
#include <functional>

namespace lasd {

  template <typename Data> class FoldableContainer : public virtual TestableContainer<Data> {
    public:
      FoldableContainer() = default;
      FoldableContainer(const FoldableContainer&) = default;
      FoldableContainer(FoldableContainer&&) = default;
      virtual ~FoldableContainer() = default;

      bool virtual operator==(const FoldableContainer& container) const noexcept = delete;
      bool virtual operator!=(const FoldableContainer& contaner) const noexcept = delete;

      virtual FoldableContainer& operator=(const FoldableContainer&) = delete;
      virtual FoldableContainer& operator=(FoldableContainer&&) = delete;

      using FoldFunctor = typename std::function<void(const Data&, void*)>;
      virtual void Fold(FoldFunctor functor, void* returnvalue) const = 0;
  };

  
  
  
  template <typename Data> class PreOrderFoldableContainer : public virtual FoldableContainer<Data> {
    public:
      PreOrderFoldableContainer() = default;
      PreOrderFoldableContainer(const PreOrderFoldableContainer&) = default;
      PreOrderFoldableContainer(PreOrderFoldableContainer&&) = default;
      virtual ~PreOrderFoldableContainer() = default;

      virtual bool operator==(const PreOrderFoldableContainer& container) const noexcept = delete;
      virtual bool operator!=(const PreOrderFoldableContainer& contaner) const noexcept = delete;

      virtual PreOrderFoldableContainer& operator=(const PreOrderFoldableContainer&) = delete;
      virtual PreOrderFoldableContainer& operator=(PreOrderFoldableContainer&&) = delete;

      
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      virtual void PreOrderFold(FoldFunctor functor, void* returnvalue) const = 0;
      virtual void Fold(FoldFunctor functor, void* returnvalue) const override { PreOrderFold(functor, returnvalue); };
  };

  
  
  
  template <typename Data> class PostOrderFoldableContainer : public virtual FoldableContainer<Data>{
    public:
      PostOrderFoldableContainer() = default;
      PostOrderFoldableContainer(const PostOrderFoldableContainer&) = default;
      PostOrderFoldableContainer(PostOrderFoldableContainer&&) = default;
      virtual ~PostOrderFoldableContainer() = default;

      virtual bool operator==(const PostOrderFoldableContainer& container) const noexcept = delete;
      virtual bool operator!=(const PostOrderFoldableContainer& contaner) const noexcept = delete;

      virtual PostOrderFoldableContainer& operator=(const PostOrderFoldableContainer&) = delete;
      virtual PostOrderFoldableContainer& operator=(PostOrderFoldableContainer&&) = delete;

      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      virtual void PostOrderFold(FoldFunctor functor, void* returnvalue) const = 0;
      virtual void Fold(FoldFunctor functor, void* returnvalue) const override { PostOrderFold(functor, returnvalue); }
  };

  
  
  
  template <typename Data> class InOrderFoldableContainer {
    public:
      InOrderFoldableContainer() = default;
      InOrderFoldableContainer(const InOrderFoldableContainer&) = default;
      InOrderFoldableContainer(InOrderFoldableContainer&&) = default;
      virtual ~InOrderFoldableContainer() = default;

      virtual bool operator==(const InOrderFoldableContainer& container) const noexcept = delete;
      virtual bool operator!=(const InOrderFoldableContainer& contaner) const noexcept = delete;

      virtual InOrderFoldableContainer& operator=(const InOrderFoldableContainer&) = delete;
      virtual InOrderFoldableContainer& operator=(InOrderFoldableContainer&&) = delete;

      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      virtual void InOrderFold(FoldFunctor functor, void* returnvalue) const = 0;
      virtual void Fold(FoldFunctor functor, void* returnvalue) const override { InOrderFold(functor, returnvalue); };
  };




  template <typename Data> class BreadthFoldableContainer : public virtual FoldableContainer<Data> {
    public:
      BreadthFoldableContainer() = default;
      BreadthFoldableContainer(const BreadthFoldableContainer&) = default;
      BreadthFoldableContainer(BreadthFoldableContainer&&) = default;
      virtual ~BreadthFoldableContainer() = default;

      virtual bool operator==(const BreadthFoldableContainer& container) const noexcept = delete;
      virtual bool operator!=(const BreadthFoldableContainer& contaner) const noexcept = delete;

      virtual BreadthFoldableContainer& operator=(const BreadthFoldableContainer&) = delete;
      virtual BreadthFoldableContainer& operator=(BreadthFoldableContainer&&) = delete;

      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      virtual void BreadthFold(FoldFunctor functor, void* returnvalue) const = 0;
      virtual void Fold(FoldFunctor functor, void* returnvalue) const override { BreadthFold(functor, returnvalue); }
  };
}