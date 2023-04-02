
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
      
      virtual bool Insert(const Data&) = 0;
      virtual bool Insert(Data&&) = 0;
      virtual bool Remove(const Data&) = 0;

      virtual bool InsertAll(const MappableContainer<Data>&);
      virtual bool InsertAll(const MutableMappableContainer<Data>&);
      virtual bool RemoveAll(const MappableContainer<Data>& source);
      
      virtual bool InsertSome(const MappableContainer<Data>& source);
      virtual bool InsertSome(const MutableMappableContainer<Data>& source);
      virtual bool RemoveSome(const MappableContainer<Data>& source);
  };
}

#include "dictionary.cpp"