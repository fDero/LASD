
// FRANCESCO DE ROSA N86004379

#pragma once

namespace lasd {

  template <typename Data> class Iterator {
    public:
      Iterator() = default;
      Iterator(const Iterator&) = default;
      Iterator(Iterator&&) = default;
      virtual ~Iterator() = default;

      virtual Iterator& operator=(const Iterator&) = delete;
      virtual Iterator& operator=(Iterator&&) = delete;
      
      virtual bool operator==(const Iterator&) const = delete;
      virtual bool operator!=(const Iterator&) const = delete;

      virtual const Data& operator*() const = 0;
      virtual bool Terminated() const noexcept = 0;
  };

  



  template <typename Data> class MutableIterator : public virtual Iterator<Data> { 
    public:
      MutableIterator() = default;
      MutableIterator(const MutableIterator&) = default;
      MutableIterator(MutableIterator&&) = default;
      virtual ~MutableIterator() = default;

      virtual MutableIterator& operator=(const MutableIterator&) = delete;
      virtual MutableIterator& operator=(MutableIterator&&) = delete;

      virtual bool operator==(const MutableIterator&) const = delete;
      virtual bool operator!=(const MutableIterator&) const = delete;

      virtual Data& operator*() = 0;
  };





  template <typename Data> class ForwardIterator : public virtual Iterator<Data> {
    public:
      ForwardIterator() = default;
      ForwardIterator(const ForwardIterator&) = default;
      ForwardIterator(ForwardIterator&&) = default;
      virtual ~ForwardIterator() = default;
      
      virtual ForwardIterator& operator=(const ForwardIterator&) = delete;
      virtual ForwardIterator& operator=(ForwardIterator&&) = delete;

      virtual bool operator==(const ForwardIterator&) const = delete;
      virtual bool operator!=(const ForwardIterator&) const = delete;

      virtual ForwardIterator<Data>& operator++() = 0;
  };

  




  template <typename Data> class BackwardIterator : public virtual Iterator<Data> {
    public:
      BackwardIterator() = default;
      BackwardIterator(const BackwardIterator&) = default;
      BackwardIterator(BackwardIterator&&) = default;
      virtual ~BackwardIterator() = default;
      
      virtual BackwardIterator& operator=(const BackwardIterator&) = delete;
      virtual BackwardIterator& operator=(BackwardIterator&&) = delete;

      virtual bool operator==(const BackwardIterator&) const = delete;
      virtual bool operator!=(const BackwardIterator&) const = delete;

      virtual BackwardIterator<Data>& operator--() = 0;
  };






  template <typename Data> class BidirectionalIterator 
    : public virtual ForwardIterator<Data>
    , public virtual BackwardIterator<Data>
  {
    public:
      BidirectionalIterator() = default;
      BidirectionalIterator(const BidirectionalIterator&) = default;
      BidirectionalIterator(BidirectionalIterator&&) = default;
      virtual ~BidirectionalIterator() = default;
      
      virtual BidirectionalIterator& operator=(const BidirectionalIterator&) = delete;
      virtual BidirectionalIterator& operator=(BidirectionalIterator&&) = delete;

      virtual bool operator==(const BidirectionalIterator&) const = delete;
      virtual bool operator!=(const BidirectionalIterator&) const = delete;
    
      virtual bool Terminated() = delete;
      virtual bool ForwardTerminated() const noexcept { return ForwardIterator<Data>::Terminated(); }
      virtual bool BackwardTerminated() const noexcept { return BackwardIterator<Data>::Terminated(); }
  };





  template <typename Data> class ResettableIterator : public virtual Iterator<Data> {
    public:
      ResettableIterator() = default;
      ResettableIterator(const ResettableIterator&) = default;
      ResettableIterator(ResettableIterator&&) = default;
      virtual ~ResettableIterator() = default;
      
      virtual ResettableIterator& operator=(const ResettableIterator&) = delete;
      virtual ResettableIterator& operator=(ResettableIterator&&) = delete;

      virtual bool operator==(const ResettableIterator&) const = delete;
      virtual bool operator!=(const ResettableIterator&) const = delete;

      virtual bool Reset() noexcept = 0;
  };
}