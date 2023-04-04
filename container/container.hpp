
// FRANCESCO DE ROSA N86004379  

#pragma once 

namespace lasd {


  using sizetype = unsigned long;


  class Container {
    protected:       
      sizetype size = 0;
    public:
      Container() = default;
      Container(const Container& container) = default;
      Container(Container&& container) = default;
      virtual ~Container() = default; 

      virtual bool operator==(const Container& container) const noexcept = delete;
      virtual bool operator!=(const Container& contaner) const noexcept = delete;

      virtual Container& operator=(const Container&) = delete;
      virtual Container& operator=(Container&&) = delete;

      bool Empty() const noexcept { return (size == 0); }
      int Size() const noexcept { return size; }
  };

  
  
  
  class ClearableContainer : public virtual Container {
    public: 
      ClearableContainer() = default;
      ClearableContainer(const ClearableContainer& container) = default;
      ClearableContainer(ClearableContainer&& container) = default;
      virtual ~ClearableContainer() = default; 

      virtual bool operator==(const ClearableContainer& container) const noexcept = delete;
      virtual bool operator!=(const ClearableContainer& contaner) const noexcept = delete;

      virtual ClearableContainer& operator=(const ClearableContainer&) = delete;
      virtual ClearableContainer& operator=(ClearableContainer&&) = delete;

      virtual void Clear() = 0;
  };

  
  
  
  class ResizableContainer : public virtual ClearableContainer {
    public:
      ResizableContainer() = default;
      ResizableContainer(const ResizableContainer& container) = default;
      ResizableContainer(ResizableContainer&& container) = default;
      virtual ~ResizableContainer() = default; 

      virtual bool operator==(const ResizableContainer& container) const noexcept = delete;
      virtual bool operator!=(const ResizableContainer& contaner) const noexcept = delete;

      virtual ResizableContainer& operator=(const ResizableContainer&) = delete;
      virtual ResizableContainer& operator=(ResizableContainer&&) = delete; 

      virtual void Resize(sizetype newSize) = 0;
      virtual void Clear() override { Resize(0); }
  };
}