
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
      virtual ~List();

      List& operator=(const List&);
      List& operator=(List&&);

      const Data& operator[](sizetype) const override;
      Data& operator[](sizetype) override;

      virtual bool operator==(const List&) const;
      virtual bool operator!=(const List&) const;
      
      virtual bool Insert(const Data&) override;
      virtual bool Insert(Data&&) override;
      virtual bool Remove(const Data&) override;

      virtual void InsertAtFront(const Data&);
      virtual void InsertAtFront(Data&&);    
      
      virtual void InsertAtBack(const Data&);
      virtual void InsertAtBack(Data&&);
  
      virtual void RemoveFromFront();
      virtual void RemoveFromBack();

      virtual Data FrontNRemove();
      virtual Data BackNRemove();
      
      virtual void Clear() override; 

      virtual const Data& Front() const;
      virtual Data& Front();

      virtual const Data& Back() const;
      virtual Data& Back();

      virtual bool Exists(const Data&) const noexcept override;

      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using MutableMapFunctor = typename MutableMappableContainer<Data>::MutableMapFunctor;
      
      virtual void PreOrderMap(MutableMapFunctor) override;
      virtual void PostOrderMap(MutableMapFunctor) override;
    };
}

#include "list.cpp"