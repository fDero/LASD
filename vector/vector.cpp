
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "vector.hpp"
#include "../container/mappable.hpp"
#include <stdexcept>

namespace lasd {

    template<typename Data> Vector<Data>::Vector() {
        size = 0;
        storage = nullptr;
    }

    template<typename Data> Vector<Data>::Vector(sizetype initial_size){
        size = initial_size;
        storage = new Data [initial_size];
    }

    template<typename Data> Vector<Data>::Vector(const Vector& vector){
        size = vector.size;
        storage = new Data[size];
        for(int i = 0; i < size; i++) storage[i] = vector.storage[i];
    }

    template<typename Data> Vector<Data>::Vector(Vector&& vector){
        storage = vector.storage;
        vector.storage = nullptr;
        size = vector.size;
    }

    template<typename Data, typename Mappable> Vector<Data> build_vector_from_mappable(const Mappable& source){
        Vector<Data> vector = Vector<Data>(source.Size());
        sizetype index_last_inserted = 0;
        source.Map([&vector, &index_last_inserted](const Data& value){
            vector[index_last_inserted] = value;
            index_last_inserted++;
        });
        return vector;
    }

    template<typename Data> Vector<Data>::Vector(const MappableContainer<Data>& source){
        storage = build_vector_from_mappable(source).storage;
        size = source.Size();
    }

    template<typename Data> Vector<Data>::Vector(const MutableMappableContainer<Data>& source){
        storage = build_vector_from_mappable(source).storage;
        size = source.Size();
    }

    template<typename Data> Vector<Data>::~Vector(){ 
        delete[] storage; 
    }

    template<typename Data> Vector<Data>& Vector<Data>::operator=(const Vector& vector){
        delete [] storage;
        size = vector.size;
        storage = new Data[size];
        for(sizetype i = 0; i < size; i++) storage[i] = vector.storage[i];
        return *this;
    }

    template<typename Data> Vector<Data>& Vector<Data>::operator=(Vector&& vector){
        size = vector.size;
        std::swap(storage,vector.storage);
        vector.storage = nullptr;
        return *this;
    }

    template<typename Data> bool Vector<Data>::operator==(const Vector& vector){
        return compare_linear_access_containers(*this,vector);
    }

    template<typename Data> bool Vector<Data>::operator!=(const Vector& vector){
        return not compare_linear_access_containers(*this,vector);
    }

    template <typename Data> void Vector<Data>::Clear() {
        size = 0;
        delete [] storage;
        storage = nullptr;
    }

    template<typename Data> void Vector<Data>::Resize(sizetype newsize){
        Data* tmp = (newsize)? new Data[newsize] : nullptr;
        sizetype minimum_length = std::min(newsize, size);
        for (int i = 0; i < minimum_length; i++) tmp[i] = storage[i];
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
