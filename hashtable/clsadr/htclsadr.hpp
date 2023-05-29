
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../hashtable.hpp"
#include "../../container/dictionary.hpp"
#include "../../list/list.hpp"

namespace lasd {

  template <typename Data> class HashTableClsAdr : public virtual HashTable<Data> {
    protected:

      using Container::size;
      using HashTable<Data>::seed;
      using HashTable<Data>::buckets;
      
      Vector<List<Data>> storage;

      using HashTable<Data>::HashFunction;
      using HashTable<Data>::RoundupPower2;
    
    public:
      HashTableClsAdr() noexcept;
      HashTableClsAdr(sizetype initial_size) noexcept;
      HashTableClsAdr(const MappableContainer<Data>&) noexcept;
      HashTableClsAdr(sizetype initial_size, const MappableContainer<Data>&) noexcept;
      HashTableClsAdr(MutableMappableContainer<Data>&&) noexcept;
      HashTableClsAdr(sizetype initial_size, MutableMappableContainer<Data>&&) noexcept;
      HashTableClsAdr(const HashTableClsAdr&) noexcept;
      HashTableClsAdr(HashTableClsAdr&&) noexcept;
      virtual ~HashTableClsAdr() = default;

      HashTableClsAdr& operator=(const HashTableClsAdr&) noexcept;
      HashTableClsAdr& operator=(HashTableClsAdr&&) noexcept;

      bool operator==(const HashTableClsAdr&) const noexcept;
      bool operator!=(const HashTableClsAdr&) const noexcept;
      
      bool Insert(const Data&) noexcept override;
      bool Insert(Data&&) noexcept override;
      bool Remove(const Data&) noexcept override;
      bool Exists(const Data&) const noexcept override;

      void Resize(sizetype) noexcept override;
      void Clear() noexcept override;

      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      
      void Map(MapFunctor) const override;
      void Fold(FoldFunctor, void*) const override;

    private:
      void AllocStorage(sizetype size);
  };

}

#include "htclsadr.cpp"