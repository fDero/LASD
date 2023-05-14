
// FRANCESCO DE ROSA 

#pragma once

#include "htopnadr.hpp"
#include "../../container/dictionary.hpp"

namespace lasd {

    /****************************************** INTERNAL STORAGE HANDLERS *************************************/

    sizetype constexpr OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT = 40000;

    template <typename Data> void HashTableOpnAdr<Data>::AllocStorage(sizetype size){
        buckets = std::max(OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT, RoundupPower2(size));
        storage = new Data*[buckets] (nullptr);
    }

    template <typename Data> void HashTableOpnAdr<Data>::DeallocStorage(){
        delete[] storage;
    }

    template <typename Data> void HashTableOpnAdr<Data>::Clear() noexcept {
        DeallocStorage();
        AllocStorage(OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT);
        size = 0;
    }

    template <typename Data> void HashTableOpnAdr<Data>::Resize(sizetype newsize) noexcept {
        if (buckets == std::max(RoundupPower2(newsize),OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT)) return;
        auto resized = HashTableOpnAdr<Data>(newsize);
        for (sizetype i = 0; i < buckets; i++) if (storage[i] != nullptr) resized.Insert(*storage[i]);
        this->operator=(std::move(resized)); 
    }




    /**************************************** CONSTRUCTORS AND DISTRUCTORS **********************************/

    template <typename Data> HashTableOpnAdr<Data>::HashTableOpnAdr() noexcept {
        AllocStorage(OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT);
    }

    template <typename Data> HashTableOpnAdr<Data>::HashTableOpnAdr(sizetype initial_size) noexcept {
        AllocStorage(initial_size);
    }

    template <typename Data> HashTableOpnAdr<Data>::HashTableOpnAdr(const MappableContainer<Data>& source) noexcept {
        AllocStorage(source.Size());
        DictionaryContainer<Data>::InsertAll(source);
    }

    template <typename Data> HashTableOpnAdr<Data>::HashTableOpnAdr(MutableMappableContainer<Data>&& source) noexcept {
        AllocStorage(source.Size());
        DictionaryContainer<Data>::InsertAll(std::move(source));
    }

    template <typename Data> HashTableOpnAdr<Data>::HashTableOpnAdr(sizetype initial_size, const MappableContainer<Data>& source) noexcept {
        AllocStorage(std::max(source.Size(), initial_size));
        DictionaryContainer<Data>::InsertAll(source);
    }

    template <typename Data> HashTableOpnAdr<Data>::HashTableOpnAdr(sizetype initial_size, MutableMappableContainer<Data>&& source) noexcept {
        AllocStorage(std::max(source.Size(), initial_size));
        DictionaryContainer<Data>::InsertAll(std::move(source));
    }

    template <typename Data> HashTableOpnAdr<Data>::HashTableOpnAdr(const HashTableOpnAdr<Data>& other) noexcept 
        : HashTableOpnAdr(static_cast<const MappableContainer<Data>&>(other)) { size = other.size; }

    template <typename Data> HashTableOpnAdr<Data>::HashTableOpnAdr(HashTableOpnAdr<Data>&& other) noexcept {
        this->operator=(std::move(other));
    }

    template <typename Data> HashTableOpnAdr<Data>::~HashTableOpnAdr() noexcept {
        DeallocStorage();
    }




    /**************************************************** ASSIGNMENTS *****************************************/

    template <typename Data> HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& other) noexcept {
        DeallocStorage();
        AllocStorage(other.buckets);
        DictionaryContainer<Data>::InsertAll(other);
        size = other.size;
        return *this;
    }

    template <typename Data> HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& other) noexcept {
        std::swap(storage, other.storage);
        std::swap(buckets, other.buckets);
        std::swap(size, other.size);
        std::swap(seed, other.seed);
        return *this;
    }




    /*********************************************** COMPARISON OPERATORS *************************************/

    template <typename Data> bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& other) const noexcept {
        if (size != other.size) return false;
        if (size == 0) return true;
        for (sizetype i = 0; i < buckets; i++) {
            if (storage[i] != nullptr and not other.Exists(*storage[i])) return false;
        }
        return true;
    }

    template <typename Data> bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& other) const noexcept {
        return not operator==(other);
    }




    /****************************************** DICTIONARY FUNCTIONALITIES ****************************************/

    template <typename Data> bool HashTableOpnAdr<Data>::Exists(const Data& target) const noexcept {
        return const_cast<HashTableOpnAdr<Data>*>(this)->LocateCell(target) != nullptr;
    }

    template <typename Data> bool HashTableOpnAdr<Data>::Remove(const Data& target) noexcept {
        Data*& location = LocateCell(target);
        if (location == nullptr) return false;
        delete location;
        location = nullptr;
        size--;
        return true;
    }

    template <typename Data> bool HashTableOpnAdr<Data>::Insert(const Data& target) noexcept {
        Data*& location = LocateCell(target);
        if (location != nullptr) return false;
        location = new Data(std::move(target));
        size++;
        return true;
    }
    
    template <typename Data> bool HashTableOpnAdr<Data>::Insert(Data&& target) noexcept {
        Data*& location = LocateCell(target);
        if (location != nullptr) return false;
        location = new Data(std::move(target));
        size++;
        return true;
    }

    template <typename Data> Data*& HashTableOpnAdr<Data>::LocateCell(const Data& value) {
        sizetype index = HashFunction(value);
        while (storage[index] != nullptr and value == (*storage[index])){
            ++index %= buckets;
        }
        return storage[index];
    }




    /************************************************ MAP / FOLD **********************************************/
    // notice that even if not explicitly required for this data-structure, maps and folds are
    // still very usefull for debugging purpuses, therfore they have been implemented anyway 

    template <typename Data> void HashTableOpnAdr<Data>::Fold(FoldFunctor functor, void* acc) const {
        this->Map([acc, functor](const Data& value){ functor(value, acc); });
    }

    template <typename Data> void HashTableOpnAdr<Data>::Map(MapFunctor functor) const {
        for (sizetype i = 0; i < buckets; i++){
            if (storage[i] != nullptr) functor(*storage[i]);
        }
    }
}