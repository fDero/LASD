
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "mappable.hpp"

namespace lasd {

  template <typename Data> class LinearContainer 
      : public virtual MutablePreOrderMappableContainer<Data>, public virtual MutablePostOrderMappableContainer<Data> { 
    protected:
      using Container::size;
    public:
      LinearContainer() = default;
      LinearContainer(const LinearContainer&) = default;
      LinearContainer(LinearContainer&&) = default;
      virtual ~LinearContainer() = default;
    
      virtual LinearContainer& operator=(const LinearContainer&) = delete;
      virtual LinearContainer& operator=(LinearContainer&&) = delete;

      virtual bool operator==(const LinearContainer&) const noexcept;
      virtual bool operator!=(const LinearContainer&) const noexcept;
      
      virtual const Data& operator[](sizetype) const = 0;
      virtual Data& operator[](sizetype) = 0; 

      const Data& Front() const;
      Data& Front();

      const Data& Back() const;
      Data& Back();

      virtual bool Exists(const Data&) const noexcept override;

      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MutableMapFunctor = typename MutableMappableContainer<Data>::MutableMapFunctor;
      virtual void PreOrderFold(FoldFunctor functor, void* returnvalue) const override;
      virtual void PostOrderFold(FoldFunctor functor, void* returnvalue) const override;
      virtual void PreOrderMap(MapFunctor) const override;
      virtual void PostOrderMap(MapFunctor) const override;
      virtual void PreOrderMap(MutableMapFunctor) override;
      virtual void PostOrderMap(MutableMapFunctor) override;
      virtual void Fold(FoldFunctor functor, void* returnvalue) const override { PreOrderFold(functor, returnvalue); }
      virtual void Map(MapFunctor functor) const override { PreOrderMap(functor); }
      virtual void Map(MutableMapFunctor functor) override { PreOrderMap(functor); }
  };





  template <typename Data> class SortableLinearContainer : public virtual LinearContainer<Data> {
    protected:
      using Container::size;
    public:
      SortableLinearContainer() = default;
      SortableLinearContainer(const SortableLinearContainer&) = default;
      SortableLinearContainer(SortableLinearContainer&&) = default;
      virtual ~SortableLinearContainer() = default;
    
      virtual SortableLinearContainer& operator=(const SortableLinearContainer&) = delete;
      virtual SortableLinearContainer& operator=(SortableLinearContainer&&) = delete;

      virtual bool operator==(const SortableLinearContainer&) const noexcept;
      virtual bool operator!=(const SortableLinearContainer&) const noexcept;

      virtual void Sort();
  };
}

#include "linear.cpp"