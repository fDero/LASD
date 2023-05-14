
// FRANCESCO DE ROSA N86004379

#pragma once

#include <cstdlib>
#include "../container/dictionary.hpp"

namespace lasd {

  template <typename Data> class HashTable
    : public virtual ResizableContainer
    , public virtual DictionaryContainer<Data>
    , public virtual MappableContainer<Data>
  {
    protected:
      using Container::size;
      unsigned short seed = rand();
      sizetype buckets;

    public:
      HashTable() = default;
      HashTable(const HashTable&) = default;
      HashTable(HashTable&&) = default;
      virtual ~HashTable() = default;

      HashTable& operator=(const HashTable&) noexcept = delete;
      HashTable& operator=(HashTable&&) noexcept = delete;

      bool operator==(const HashTable&) const noexcept = delete;
      bool operator!=(const HashTable&) const noexcept = delete;

    protected:
      sizetype HashFunction(const Data&) const noexcept;
      sizetype RoundupPower2(sizetype size) const noexcept;
  };
}

#include "hashtable.cpp"