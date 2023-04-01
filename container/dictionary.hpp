
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
      
      //bool Insert(const Data&) = 0;
      //bool Insert(Data&&) = 0;
      //bool Remove(const Data&) = 0;
      
      //bool InsertAll(const MappableContainer<Data>&) = 0;
      //bool InsertAll(const MutableMappableContainer<Data>&&) = 0;
      //bool RemoveALl(const MappableContainer<Data>&) = 0;
      
      //bool InsertSome(const MappableContainer<Data>&) = 0;
      //bool InsertSome(const MutableMappableContainer<Data>&&) = 0;
      //bool RemoveSome(const MappableContainer<Data>&) = 0;      
  };
}



      // type InsertAll(argument) specifiers; // Copy of the value; From MappableContainer; True if all are inserted
      // type InsertAll(argument) specifiers; // Move of the value; From MutableMappableContainer; True if all are inserted
      // type RemoveAll(argument) specifiers; // From MappableContainer; True if all are removed

      // type InsertSome(argument) specifiers; // Copy of the value; From MappableContainer; True if some is inserted
      // type InsertSome(argument) specifiers; // Move of the value; From MutableMappableContainer; True if some is inserted
      // type RemoveSome(argument) specifiers; // From MappableContainer; True if some is removed
