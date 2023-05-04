
// FRANCESCO DE ROSA N86004379  

#pragma once 

#include "../container/container.hpp"
#include "../container/mappable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

//the class lasd::List<T> been implemented as a doubly-linked list since it's much more efficient to perform PostOrderMaps on it
//this way, since the possibility to remove from the tail is now aviable, the method "RemoveFromBack" has been implemented 

namespace lasd {

  template <typename Data> class List 
    : public virtual ClearableContainer
    , public virtual LinearContainer<Data>
    , public virtual DictionaryContainer<Data> 
  {
    protected:

      using Container::size;

      struct Node {
        Data value;
        Node* next = nullptr;
        Node* prev = nullptr;

        Node(const Data& input) { value = input; }
        Node(Data&& input) { value = std::move(input); }

        Node() = delete;
        Node(Node&& node) = delete;
        Node(const Node&) = delete;
        ~Node() = default;
      };

      Node* head = nullptr;
      Node* tail = nullptr;

    public:

      List() = default;
      List(const List&) noexcept;
      List(List&&) noexcept;
      List(const MappableContainer<Data>&) noexcept;
      List(MutableMappableContainer<Data>&&) noexcept;
      virtual ~List() noexcept;

      List& operator=(const List&) noexcept;
      List& operator=(List&&) noexcept;

      const Data& operator[](sizetype) const override;
      Data& operator[](sizetype) override;

      virtual bool operator==(const List&) const noexcept;
      virtual inline bool operator!=(const List&) const noexcept;
      
      virtual bool Insert(const Data&) noexcept override;
      virtual bool Insert(Data&&) noexcept override;
      virtual bool Remove(const Data&) noexcept override;

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

    private:
      void Dealloc();
      void EmplaceAtFront(Node*);
      void EmplaceAtBack(Node*);
  };
}

#include "list.cpp"