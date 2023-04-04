
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "vector.hpp"
#include "../container/mappable.hpp"
#include <stdexcept>

namespace lasd {

    template<typename Data> Vector<Data>::Vector() = default;

    template<typename Data> Vector<Data>::Vector(const Vector& vector){
        this->operator=(vector);
    }

    template<typename Data> Vector<Data>::Vector(Vector&& vector){
        this->operator=(vector);
    }
    
    template<typename Data> Vector<Data>::Vector(sizetype initial_size){
        size = initial_size;
        storage = new Data [initial_size];
    }

    template<typename Data> Vector<Data>::Vector(const MappableContainer<Data>& source){
        this->Resize(source.size);
        sizetype index_last_inserted = 0;
        source.Map([this, &index_last_inserted](const Data& value){
            (this->storage)[index_last_inserted] = value;
            index_last_inserted++;
        });
    }

    template<typename Data> Vector<Data>::Vector(MutableMappableContainer<Data>&& source){
        this->Resize(source.size);
        sizetype index_last_inserted = 0;
        source.Map([this, &index_last_inserted](Data& value){
            (this->storage)[index_last_inserted] = std::move(value);
            index_last_inserted++;
        });
    }

    template<typename Data> Vector<Data>::~Vector(){ 
        delete[] storage; 
    }

    template<typename Data> Vector<Data>& Vector<Data>::operator=(const Vector& vector){
        Resize(vector.size);
        std::copy(vector.storage, vector.storage + size, storage);
        return *this;
    }

    template<typename Data> Vector<Data>& Vector<Data>::operator=(Vector&& vector){
        size = vector.size;
        std::swap(storage,vector.storage);
        vector.storage = nullptr;
        return *this;
    }   

    template<typename Data> void Vector<Data>::Resize(sizetype newsize){
        Data* tmp = (newsize)? new Data[newsize] : nullptr;
        sizetype minimum_length = std::min(newsize, size);
        std::copy(storage, storage + minimum_length, tmp);
        std::swap(tmp, storage);
        delete [] tmp;
        size = newsize;
    }

    template<typename Data> Data& Vector<Data>::operator[](sizetype index){
        if (index >= size) throw std::out_of_range("index exceeds the current size");
        return storage[index];
    }

    template<typename Data> const Data& Vector<Data>::operator[](sizetype index) const {
        if (index >= size) throw std::out_of_range("index exceeds the current size");
        return storage[index];
    }
}