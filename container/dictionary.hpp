
// FRANCESCO DE ROSA N86004379

#pragma once

#include "testable.hpp"
#include "mappable.hpp"

namespace lasd {

  template <typename Data> class DictionaryContainer : public virtual TestableContainer<Data> {
    public:
      DictionaryContainer() = default;
      DictionaryContainer(const DictionaryContainer&) = default;
      DictionaryContainer(DictionaryContainer&&) = default;
      virtual ~DictionaryContainer() = default;
    
      virtual DictionaryContainer& operator=(const DictionaryContainer&) = delete;
      virtual DictionaryContainer& operator=(DictionaryContainer&&) = delete;

      virtual bool operator==(const DictionaryContainer&) const noexcept = delete;
      virtual bool operator!=(const DictionaryContainer&) const noexcept = delete;
      
      virtual bool Insert(const Data&) noexcept = 0;
      virtual bool Insert(Data&&) noexcept = 0;
      virtual bool Remove(const Data&) noexcept = 0;

      virtual bool InsertAll(const MappableContainer<Data>&) noexcept;
      virtual bool InsertAll(MutableMappableContainer<Data>&&) noexcept;
      virtual bool RemoveAll(const MappableContainer<Data>&) noexcept;
      
      virtual bool InsertSome(const MappableContainer<Data>&) noexcept;
      virtual bool InsertSome(MutableMappableContainer<Data>&&) noexcept;
      virtual bool RemoveSome(const MappableContainer<Data>&) noexcept;
  };
}

#include "dictionary.cpp"