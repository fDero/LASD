
// FRANCESCO DE ROSA N86004379  

#pragma once

#include <functional>
#include "foldable.hpp"

namespace lasd {

  template <typename Data> class MappableContainer : public virtual FoldableContainer<Data> { 
    public:
      MappableContainer() = default;
      MappableContainer(const MappableContainer&) = default;
      MappableContainer(MappableContainer&&) = default;
      virtual ~MappableContainer() = default;

      bool virtual operator==(const MappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const MappableContainer& contaner) const noexcept = delete;

      virtual MappableContainer& operator=(const MappableContainer&) = delete;
      virtual MappableContainer& operator=(MappableContainer&&) = delete;

      using MapFunctor = std::function<void(const Data&)>;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      virtual void Map(MapFunctor) const = 0;
  };





  template <typename Data> class PreOrderMappableContainer : 
      public virtual MappableContainer<Data>, public virtual PreOrderFoldableContainer<Data> {
    public:
      PreOrderMappableContainer() = default;
      PreOrderMappableContainer(const PreOrderMappableContainer&) = default;
      PreOrderMappableContainer(PreOrderMappableContainer&&) = default;
      virtual ~PreOrderMappableContainer() = default;

      bool virtual operator==(const PreOrderMappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const PreOrderMappableContainer& contaner) const noexcept = delete;

      virtual PreOrderMappableContainer& operator=(const PreOrderMappableContainer&) = delete;
      virtual PreOrderMappableContainer& operator=(PreOrderMappableContainer&&) = delete;

      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      virtual void PreOrderMap(MapFunctor) const = 0;
      virtual void Map(MapFunctor functor) const override;
      virtual void PreOrderFold(FoldFunctor, void*) const override;
  };





  template <typename Data> class PostOrderMappableContainer : 
      public virtual MappableContainer<Data>, public virtual PostOrderFoldableContainer<Data> {
    public:
      PostOrderMappableContainer() = default;
      PostOrderMappableContainer(const PostOrderMappableContainer&) = default;
      PostOrderMappableContainer(PostOrderMappableContainer&&) = default;
      virtual ~PostOrderMappableContainer() = default;

      bool virtual operator==(const PostOrderMappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const PostOrderMappableContainer& contaner) const noexcept = delete;

      virtual PostOrderMappableContainer& operator=(const PostOrderMappableContainer&) = delete;
      virtual PostOrderMappableContainer& operator=(PostOrderMappableContainer&&) = delete;

      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      virtual void PostOrderMap(MapFunctor) const = 0;
      virtual void Map(MapFunctor functor) const override;
      virtual void PostOrderFold(FoldFunctor, void*) const override;
  };





  template <typename Data> class InOrderMappableContainer 
      : public virtual MappableContainer<Data>, public virtual InOrderFoldableContainer<Data> {
    public:
      InOrderMappableContainer() = default;
      InOrderMappableContainer(const InOrderMappableContainer&) = default;
      InOrderMappableContainer(InOrderMappableContainer&&) = default;
      virtual ~InOrderMappableContainer() = default;

      bool virtual operator==(const InOrderMappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const InOrderMappableContainer& contaner) const noexcept = delete;

      virtual InOrderMappableContainer& operator=(const InOrderMappableContainer&) = delete;
      virtual InOrderMappableContainer& operator=(InOrderMappableContainer&&) = delete;

      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      virtual void InOrderMap(MapFunctor) const = 0;
      virtual void Map(MapFunctor functor) const override;
      virtual void InOrderFold(FoldFunctor, void*) const override;
  };





  template <typename Data> class BreadthMappableContainer 
      : public virtual MappableContainer<Data>, public virtual BreadthFoldableContainer<Data> {
    public:
      BreadthMappableContainer() = default;
      BreadthMappableContainer(const BreadthMappableContainer&) = default;
      BreadthMappableContainer(BreadthMappableContainer&&) = default;
      virtual ~BreadthMappableContainer() = default;

      bool virtual operator==(const BreadthMappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const BreadthMappableContainer& contaner) const noexcept = delete;

      virtual BreadthMappableContainer& operator=(const BreadthMappableContainer&) = delete;
      virtual BreadthMappableContainer& operator=(BreadthMappableContainer&&) = delete;

      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      virtual void BreadthMap(MapFunctor) const = 0;
      virtual void Map(MapFunctor functor) const override;
      virtual void BreadthFold(FoldFunctor, void*) const override;
  };





  template <typename Data> class MutableMappableContainer : public virtual MappableContainer<Data> { 
    public:
      MutableMappableContainer() = default;
      MutableMappableContainer(const MutableMappableContainer&) = default;
      MutableMappableContainer(MutableMappableContainer&&) = default;
      virtual ~MutableMappableContainer() = default;

      bool virtual operator==(const MutableMappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const MutableMappableContainer& contaner) const noexcept = delete;

      virtual MutableMappableContainer& operator=(const MutableMappableContainer&) = delete;
      virtual MutableMappableContainer& operator=(MutableMappableContainer&&) = delete;
      
      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MutableMapFunctor = std::function<void(Data &)>;
      virtual void Map(MutableMapFunctor) = 0;
  };





  template <typename Data> class MutablePreOrderMappableContainer 
      : public virtual MutableMappableContainer<Data>, public virtual PreOrderMappableContainer<Data> {
    public:
      MutablePreOrderMappableContainer() = default;
      MutablePreOrderMappableContainer(const MutablePreOrderMappableContainer&) = default;
      MutablePreOrderMappableContainer(MutablePreOrderMappableContainer&&) = default;
      virtual ~MutablePreOrderMappableContainer() = default;

      bool virtual operator==(const MutablePreOrderMappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const MutablePreOrderMappableContainer& contaner) const noexcept = delete;

      virtual MutablePreOrderMappableContainer& operator=(const MutablePreOrderMappableContainer&) = delete;
      virtual MutablePreOrderMappableContainer& operator=(MutablePreOrderMappableContainer&&) = delete;
      
      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MutableMapFunctor = typename MutableMappableContainer<Data>::MutableMapFunctor;
      virtual void PreOrderMap(MutableMapFunctor) = 0;
      virtual void Map(MutableMapFunctor functor) override;
  };



    template <typename Data> class MutablePostOrderMappableContainer
      : public virtual MutableMappableContainer<Data>, public virtual PostOrderMappableContainer<Data> {
    public:
      MutablePostOrderMappableContainer() = default;
      MutablePostOrderMappableContainer(const MutablePostOrderMappableContainer&) = default;
      MutablePostOrderMappableContainer(MutablePostOrderMappableContainer&&) = default;
      virtual ~MutablePostOrderMappableContainer() = default;

      bool virtual operator==(const MutablePostOrderMappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const MutablePostOrderMappableContainer& contaner) const noexcept = delete;

      virtual MutablePostOrderMappableContainer& operator=(const MutablePostOrderMappableContainer&) = delete;
      virtual MutablePostOrderMappableContainer& operator=(MutablePostOrderMappableContainer&&) = delete;
      
      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MutableMapFunctor = typename MutableMappableContainer<Data>::MutableMapFunctor;
      virtual void PostOrderMap(MutableMapFunctor) = 0;
      virtual void Map(MutableMapFunctor functor) override;
  };





  template <typename Data> class MutableInOrderMappableContainer 
      : public virtual MutableMappableContainer<Data>, public virtual InOrderMappableContainer<Data> {  
    public:
      MutableInOrderMappableContainer() = default;
      MutableInOrderMappableContainer(const MutableInOrderMappableContainer&) = default;
      MutableInOrderMappableContainer(MutableInOrderMappableContainer&&) = default;
      virtual ~MutableInOrderMappableContainer() = default;

      bool virtual operator==(const MutableInOrderMappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const MutableInOrderMappableContainer& contaner) const noexcept = delete;

      virtual MutableInOrderMappableContainer& operator=(const MutableInOrderMappableContainer&) = delete;
      virtual MutableInOrderMappableContainer& operator=(MutableInOrderMappableContainer&&) = delete;
      
      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MutableMapFunctor = typename MutableMappableContainer<Data>::MutableMapFunctor;
      virtual void InOrderMap(MutableMapFunctor) = 0;
      virtual void Map(MutableMapFunctor functor) override;
  };





  template <typename Data> class MutableBreadthMappableContainer
      : public virtual MutableMappableContainer<Data>, public virtual BreadthMappableContainer<Data> {  
    public:
      MutableBreadthMappableContainer() = default;
      MutableBreadthMappableContainer(const MutableBreadthMappableContainer&) = default;
      MutableBreadthMappableContainer(MutableBreadthMappableContainer&&) = default;
      virtual ~MutableBreadthMappableContainer() = default;

      bool virtual operator==(const MutableBreadthMappableContainer& container) const noexcept = delete;
      bool virtual operator!=(const MutableBreadthMappableContainer& contaner) const noexcept = delete;

      virtual MutableBreadthMappableContainer& operator=(const MutableBreadthMappableContainer&) = delete;
      virtual MutableBreadthMappableContainer& operator=(MutableBreadthMappableContainer&&) = delete;
      
      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MutableMapFunctor = typename MutableMappableContainer<Data>::MutableMapFunctor;
      virtual void BreadthMap(MutableMapFunctor) = 0;
      virtual void Map(MutableMapFunctor functor) override;
  };
}

#include "mappable.cpp"