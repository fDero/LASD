
#pragma once

#include "../hashtable.hpp"
#include "../clsadr/htclsadr.hpp"

namespace lasd {

  template <typename Data> class HashTableOpnAdr : public virtual HashTable<Data> {
    protected:
      using Container::size;
      using HashTable<Data>::seed;
      using HashTable<Data>::buckets;
      
      using HashTable<Data>::HashFunction;
      using HashTable<Data>::RoundupPower2;

      sizetype removed_data_counter = 0;
      enum class State { EMPTY, CLEARED, OCCUPIED };

      Vector<Data> values_storage;
      Vector<State> state_storage;

    public:
      HashTableOpnAdr() noexcept;
      HashTableOpnAdr(sizetype initial_size) noexcept;
      HashTableOpnAdr(const MappableContainer<Data>&) noexcept;
      HashTableOpnAdr(sizetype initial_size, const MappableContainer<Data>&) noexcept;
      HashTableOpnAdr(MutableMappableContainer<Data>&&) noexcept;
      HashTableOpnAdr(sizetype initial_size, MutableMappableContainer<Data>&&) noexcept;
      HashTableOpnAdr(const HashTableOpnAdr&) noexcept;
      HashTableOpnAdr(HashTableOpnAdr&&) noexcept;
      virtual ~HashTableOpnAdr() = default;

      HashTableOpnAdr& operator=(const HashTableOpnAdr&) noexcept;
      HashTableOpnAdr& operator=(HashTableOpnAdr&&) noexcept;

      bool operator==(const HashTableOpnAdr&) const noexcept;
      bool operator!=(const HashTableOpnAdr&) const noexcept;
      
      bool Insert(const Data&) noexcept override;
      bool Insert(Data&&) noexcept override;
      bool Remove(const Data&) noexcept override;
      bool Exists(const Data&) const noexcept override;

      void Resize(sizetype) noexcept override;
      void Clear() noexcept override;

      void Reset();

      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      
      void Map(MapFunctor) const override;
      void Fold(FoldFunctor, void*) const override;
    
    private:
      void AllocStorage(sizetype size);
      std::pair<sizetype, sizetype> LocateBucket(const Data&) const noexcept;
      bool RemoveAtIndex(const Data&, sizetype) noexcept;
      template<typename ValueType> bool InsertHelper(ValueType&&) noexcept;
  };
}

#include "htopnadr.cpp"




/*
private:

    // ...

  protected:

    // using HashTable<Data>::???;

    // ...

  public:
    
    // Default constructor
    // HashTableOpnAdr() specifiers;

  
    // Specific constructors
    // HashTableOpnAdr(argument) specifiers; // A hash table of a given size
    // HashTableOpnAdr(argument) specifiers; // A hash table obtained from a MappableContainer
    // HashTableOpnAdr(argument) specifiers; // A hash table of a given size obtained from a MappableContainer
    // HashTableOpnAdr(argument) specifiers; // A hash table obtained from a MutableMappableContainer
    // HashTableOpnAdr(argument) specifiers; // A hash table of a given size obtained from a MutableMappableContainer

    // Copy constructor
    // HashTableOpnAdr(argument) specifiers;

    // Move constructor
    // HashTableOpnAdr(argument) specifiers;

    // Destructor
    // ~HashTableOpnAdr() specifiers;


    // Copy assignment
    // type operator=(argument) specifiers;

    // Move assignment
    // type operator=(argument) specifiers;

    // Comparison operators
    // type operator==(argument) specifiers;
    // type operator!=(argument) specifiers;


    // Specific member functions (inherited from DictionaryContainer)

    // type Insert(argument) specifiers; // Override DictionaryContainer member (Copy of the value)
    // type Insert(argument) specifiers; // Override DictionaryContainer member (Move of the value)
    // type Remove(argument) specifiers; // Override DictionaryContainer member


    // Specific member functions (inherited from TestableContainer)

    // type Exists(argument) specifiers; // Override TestableContainer member

    // Specific member functions (inherited from ResizableContainer)

    // type Resize(argument) specifiers; // Resize the hashtable to a given size


    // Specific member functions (inherited from ClearableContainer)

    // type Clear() specifiers; // Override Container member

  public:

    // Auxiliary member functions

    // type HashKey(argument) specifiers;
    // type Find(argument) specifiers;
    // type FindEmpty(argument) specifiers;
    // type Remove(argument) specifiers;

*/