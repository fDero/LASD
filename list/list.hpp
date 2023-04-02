
// FRANCESCO DE ROSA N86004379  

#pragma once 

#include "../container/container.hpp"
#include "../container/mappable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

namespace lasd {

  template <typename Data> class List 
      : public virtual ClearableContainer, public virtual LinearContainer<Data>, public virtual DictionaryContainer<Data> {
    protected:

      using Container::size;

      struct Node {
        Data value;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node() = delete;
        Node(const Data& input) { value = input; }
        Node(const Node&) = default;
        Node(Node&&) = default;
        ~Node() = default;
      };

      Node* head = nullptr;
      Node* tail = nullptr;

    public:

      List() = default;
      List(const List&);
      List(List&&);
      List(const MappableContainer<Data>&);
      List(const MutableMappableContainer<Data>&);
      ~List();

      List& operator=(const List&);
      List& operator=(List&&);

      const Data& operator[](sizetype) const;
      Data& operator[](sizetype);

      virtual bool operator==(const List&) const;
      virtual bool operator!=(const List&) const;
      
      // Specific member functions (inherited from DictionaryContainer)
      virtual bool Insert(const Data&) { throw true; }
      virtual bool Insert(Data&&) { throw true; }
      virtual bool Remove(const Data&) { throw true; }

      void InsertAtFront(const Data&);
      // type InsertAtFront(argument) specifier; // Move of the value    
      // type RemoveFromFront() specifier; // (must throw std::length_error when empty)
      // type FrontNRemove() specifier; // (must throw std::length_error when empty)
      // type InsertAtBack(argument) specifier; // Copy of the value
      // type InsertAtBack(argument) specifier; // Move of the value
      void InsertAtBack(const Data&);
      //void InsertAtBack(Data&&);
      
      
      void Clear() override; 

      const Data& Front() const;
      Data& Front();

      const Data& Back() const;
      Data& Back();

      bool Exists(const Data&) const noexcept override;

      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using MutableMapFunctor = typename MutableMappableContainer<Data>::MutableMapFunctor;
      void PreOrderMap(MapFunctor) const override;
      void PostOrderMap(MapFunctor) const override;
      void PreOrderMap(MutableMapFunctor) override;
      void PostOrderMap(MutableMapFunctor) override;
      void Fold(FoldFunctor functor, void* accumulator) const override { LinearContainer<Data>::PreOrderFold(functor, accumulator); }
      void Map(MapFunctor functor) const override { PreOrderMap(functor); }
      void Map(MutableMapFunctor functor) override { PreOrderMap(functor); }
    };
}

#include "list.cpp"