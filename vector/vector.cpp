
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "vector.hpp"
#include "../container/mappable.hpp"
#include <stdexcept>

namespace lasd {

    /***************************** CONSTRUCTORS AND DISTRUCTORS ************************/

    template<typename Data> Vector<Data>::Vector(const Vector& vector) noexcept {
        this->operator=(vector);
    }

    template<typename Data> Vector<Data>::Vector(Vector&& vector) noexcept {
        this->operator=(std::move(vector));
    }
    
    template<typename Data> Vector<Data>::Vector(sizetype initial_size) noexcept {
        size = initial_size;
        storage = new Data [initial_size];
    }

    template<typename Data> Vector<Data>::Vector(const MappableContainer<Data>& source) noexcept {
        this->Resize(source.Size());
        sizetype index_last_inserted = 0;
        source.Map([this, &index_last_inserted](const Data& value){
            (this->storage)[index_last_inserted] = value;
            index_last_inserted++;
        });
    }

    template<typename Data> Vector<Data>::Vector(MutableMappableContainer<Data>&& source) noexcept {
        this->Resize(source.Size());
        sizetype index_last_inserted = 0;
        source.Map([this, &index_last_inserted](Data& value){
            (this->storage)[index_last_inserted] = std::move(value);
            index_last_inserted++;
        });
    }

    template<typename Data> Vector<Data>::~Vector() noexcept { 
        delete[] storage; 
    }


    /************************************* COMPARISON OPERATORS ******************************/

    template <typename Data> inline bool Vector<Data>::operator==(const Vector<Data>& other) const noexcept {
        return LinearContainer<Data>::operator==(other);
    }

    template <typename Data> inline bool Vector<Data>::operator!=(const Vector<Data>& other) const noexcept {
        return LinearContainer<Data>::operator!=(other);
    }



    /*********************************** ASSIGNMENT OPERATORS ********************************/

    template<typename Data> Vector<Data>& Vector<Data>::operator=(const Vector& vector) noexcept {
        Resize(vector.size);
        std::copy(vector.storage, vector.storage + size, storage);
        return *this;
    }

    template<typename Data> Vector<Data>& Vector<Data>::operator=(Vector&& vector) noexcept {
        std::swap(size,vector.size);
        std::swap(storage,vector.storage);
        return *this;
    }   



    /******************************************* RESIZE *****************************************/
    // notice that Clear() is inherited from ClearableContainer as a call to Resize(0). wich indeed
    // deallocates everything and correctly set the size to be zero. Therefore is not overrided

    template<typename Data> inline Data* Vector<Data>::array_safe_alloc(sizetype length) {
        return (length)? new Data[length] : nullptr;
    }

    template<typename Data> void Vector<Data>::Resize(sizetype newsize){
        Data* tmp = array_safe_alloc(newsize);
        sizetype minimum_length = std::min(newsize, size);
        std::copy(storage, storage + minimum_length, tmp);
        std::swap(tmp, storage);
        delete [] tmp;
        size = newsize;
    }



    /*************************************** DATA ACCESS OPERATORS ******************************/

    template<typename Data> Data& Vector<Data>::operator[](sizetype index){
        if (index >= size) throw std::out_of_range("index exceeds the current size");
        return storage[index];
    }

    template<typename Data> const Data& Vector<Data>::operator[](sizetype index) const {
        if (index >= size) throw std::out_of_range("index exceeds the current size");
        return storage[index];
    }
}