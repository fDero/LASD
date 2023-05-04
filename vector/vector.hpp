
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "../container/container.hpp"
#include "../container/linear.hpp"

namespace lasd {

  template <typename Data> class Vector 
    : public virtual ResizableContainer
    , public virtual SortableLinearContainer<Data> 
  {
    protected:
      using Container::size;
      Data* storage = nullptr;
      
    public:

      Vector() noexcept = default;
      Vector(const Vector&) noexcept;
      Vector(Vector&&) noexcept;
      Vector(sizetype) noexcept;
      Vector(const MappableContainer<Data>&) noexcept;
      Vector(MutableMappableContainer<Data>&&) noexcept;
      virtual ~Vector() noexcept;

      virtual Vector& operator=(const Vector&) noexcept;
      virtual Vector& operator=(Vector&&) noexcept;

      virtual const Data& operator[](sizetype) const override;
      virtual Data& operator[](sizetype) override;

      virtual inline bool operator==(const Vector&) const noexcept;
      virtual inline bool operator!=(const Vector&) const noexcept;

      virtual void Resize(sizetype) override;

    protected:
      inline Data* array_safe_alloc(sizetype);
  };
}

#include "vector.cpp"