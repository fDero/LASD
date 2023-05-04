
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "mappable.hpp"

// even if it was not required, lasd::SortableContainer<T> has been set up to provide multple sort algorithms, and they are 
// QuickSort, MergeSort, InsertionSort and SelectionSort. By default Sort() just calls QuickSort. Implementations are in the file "sortable.cpp"

namespace lasd {

  template <typename Data> class LinearContainer 
    : public virtual MutablePreOrderMappableContainer<Data>
    , public virtual MutablePostOrderMappableContainer<Data> 
  { 
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
      inline virtual bool operator!=(const LinearContainer&) const noexcept;
      
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

      using PreOrderMappableContainer<Data>::PreOrderFold;
      using PostOrderMappableContainer<Data>::PostOrderFold;

      using PreOrderMappableContainer<Data>::PreOrderMap;
      using PostOrderMappableContainer<Data>::PostOrderMap;

      virtual void PreOrderMap(MutableMapFunctor) override;
      virtual void PostOrderMap(MutableMapFunctor) override;
      
      virtual inline void Fold(FoldFunctor functor, void* accumulator) const override;
      virtual inline void Map(MapFunctor) const override;
      virtual inline void Map(MutableMapFunctor) override;
  };





  template <typename Data> class SortableLinearContainer 
    : public virtual LinearContainer<Data> 
  {
    protected:
      using Container::size;
    public:
      SortableLinearContainer() = default;
      SortableLinearContainer(const SortableLinearContainer&) = default;
      SortableLinearContainer(SortableLinearContainer&&) = default;
      virtual ~SortableLinearContainer() = default;
    
      virtual SortableLinearContainer& operator=(const SortableLinearContainer&) = delete;
      virtual SortableLinearContainer& operator=(SortableLinearContainer&&) = delete;

      using Container::Size;
      using Container::Empty;

      using LinearContainer<Data>::operator==;
      using LinearContainer<Data>::operator!=;
      using LinearContainer<Data>::operator[];

      void InsertionSort() noexcept;
      void SelectionSort() noexcept;
      inline void QuickSort() noexcept;
      inline void MergeSort() noexcept; 
      inline void Sort() noexcept;

      bool Sorted() const noexcept;

    private:
      void QuickSort(sizetype, sizetype);
      void MergeSort(sizetype, sizetype);
  };
}

#include "linear.cpp"
#include "sortable.cpp"