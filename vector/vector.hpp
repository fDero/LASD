
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "../container/container.hpp"
#include "../container/linear.hpp"

namespace lasd {

template <typename Data> 
class Vector : public virtual ResizableContainer, public virtual SortableLinearContainer<Data> {
  protected:
    using Container::size;
    Data* storage;
    
  public:

    Vector();
    Vector(const Vector&);
    Vector(Vector&&);
    Vector(sizetype);
    Vector(const MappableContainer<Data>&);
    Vector(const MutableMappableContainer<Data>&);
    ~Vector();

    virtual Vector& operator=(const Vector&);
    virtual Vector& operator=(Vector&&);

    const Data& operator[](sizetype) const;
    Data& operator[](sizetype);

    virtual bool operator==(const Vector&);
    virtual bool operator!=(const Vector&);
    
    virtual void Clear() override;
    virtual void Resize(sizetype) override;
  };
}

#include "vector.cpp"