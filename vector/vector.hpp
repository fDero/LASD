
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "../container/container.hpp"
#include "../container/linear.hpp"

namespace lasd {

template <typename Data> 
class Vector : public virtual ResizableContainer, public virtual SortableLinearContainer<Data> {
  protected:
    using Container::size;
    Data* storage = nullptr;
    
  public:

    Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector(sizetype);
    Vector(const MappableContainer<Data>&);
    Vector(MutableMappableContainer<Data>&&);
    virtual ~Vector();

    virtual Vector& operator=(const Vector&);
    virtual Vector& operator=(Vector&&);

    virtual const Data& operator[](sizetype) const override;
    virtual Data& operator[](sizetype) override;

    using LinearContainer<Data>::operator==;
    using LinearContainer<Data>::operator!=;

    virtual void Resize(sizetype) override;
  };
}

#include "vector.cpp"