
// FRANCESCO DE ROSA N86004379  

#pragma once 

// the method Empty and Size are not virtual because they are never overrided. In lasd::StackVec<T> and lasd::QueVec<T> size still rappresent
// the number of elements properly contained in the container so Size and Empty still works and do not need to be overrided. Instead Resize and Clear
// are overrided but in lasd::QueVec<T> Resize should have been overrided anyway so it's not a big problem. This choice, although restrictive, works fine
// for the current hiarchy and minimizes the numbers of methods declared virtual, wich itself minimazes the virtual-overall-overhead cost of the structures

namespace lasd {

  using sizetype = unsigned long;

  class Container {
    protected:       
      sizetype size = 0;
    public:
      Container() = default;
      Container(const Container&) = default;
      Container(Container&&) = default;
      virtual ~Container() = default; 

      virtual bool operator==(const Container&) const = delete;
      virtual bool operator!=(const Container&) const = delete;

      virtual Container& operator=(const Container&) = delete;
      virtual Container& operator=(Container&&) = delete;

      inline bool Empty() const noexcept { return (size == 0); }
      inline sizetype Size() const noexcept { return size; }
  };

  
  
  
  class ClearableContainer : public virtual Container {
    public: 
      ClearableContainer() = default;
      ClearableContainer(const ClearableContainer&) = default;
      ClearableContainer(ClearableContainer&&) = default;
      virtual ~ClearableContainer() = default; 

      virtual bool operator==(const ClearableContainer&) const = delete;
      inline virtual bool operator!=(const ClearableContainer&) const = delete;

      virtual ClearableContainer& operator=(const ClearableContainer&) = delete;
      virtual ClearableContainer& operator=(ClearableContainer&&) = delete;

      virtual void Clear() = 0;
  };

  
  
  
  class ResizableContainer : public virtual ClearableContainer {
    public:
      ResizableContainer() = default;
      ResizableContainer(const ResizableContainer&) = default;
      ResizableContainer(ResizableContainer&&) = default;
      virtual ~ResizableContainer() = default; 

      virtual bool operator==(const ResizableContainer&) const noexcept = delete;
      inline virtual bool operator!=(const ResizableContainer&) const noexcept = delete;

      virtual ResizableContainer& operator=(const ResizableContainer&) = delete;
      virtual ResizableContainer& operator=(ResizableContainer&&) = delete; 

      virtual void Resize(sizetype newSize) = 0;
      inline virtual void Clear() override { Resize(0); }
  };
}