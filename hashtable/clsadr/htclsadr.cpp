
// FRANCESCO DE ROSA 

#pragma once

#include "htclsadr.hpp"
#include "../../container/dictionary.hpp"

namespace lasd {

    /****************************************** INTERNAL STORAGE HANDLERS *************************************/

    sizetype constexpr CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT = 64;

    template <typename Data> void HashTableClsAdr<Data>::AllocStorage(sizetype size){
        buckets = std::max(CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT, RoundupPower2(size));
        storage.Resize(buckets);
        storage.Map([](List<Data>& bucket){ bucket.Clear(); });
    }

    template <typename Data> void HashTableClsAdr<Data>::Clear() noexcept {
        AllocStorage(CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT);
        size = 0;
    }

    template <typename Data> void HashTableClsAdr<Data>::Resize(sizetype newsize) noexcept {
        if (buckets == std::max(RoundupPower2(newsize),CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT)) return;
        auto resized = HashTableClsAdr<Data>(newsize, *this);
        this->operator=(std::move(resized)); 
    }




    /************************************************ CONSTRUCTORS ********************************************/

    template <typename Data> HashTableClsAdr<Data>::HashTableClsAdr() noexcept {
        AllocStorage(CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT);
    }

    template <typename Data> HashTableClsAdr<Data>::HashTableClsAdr(sizetype initial_size) noexcept {
        AllocStorage(initial_size);
    }

    template <typename Data> HashTableClsAdr<Data>::HashTableClsAdr(const MappableContainer<Data>& source) noexcept {
        AllocStorage(source.Size());
        DictionaryContainer<Data>::InsertAll(source);
    }

    template <typename Data> HashTableClsAdr<Data>::HashTableClsAdr(MutableMappableContainer<Data>&& source) noexcept {
        AllocStorage(source.Size());
        DictionaryContainer<Data>::InsertAll(std::move(source));
    }

    template <typename Data> HashTableClsAdr<Data>::HashTableClsAdr(sizetype initial_size, const MappableContainer<Data>& source) noexcept {
        AllocStorage(std::max(source.Size(), initial_size));
        DictionaryContainer<Data>::InsertAll(source);
    }

    template <typename Data> HashTableClsAdr<Data>::HashTableClsAdr(sizetype initial_size, MutableMappableContainer<Data>&& source) noexcept {
        AllocStorage(std::max(source.Size(), initial_size));
        DictionaryContainer<Data>::InsertAll(std::move(source));
    }

    template <typename Data> HashTableClsAdr<Data>::HashTableClsAdr(const HashTableClsAdr<Data>& other) noexcept 
        : HashTableClsAdr(static_cast<const MappableContainer<Data>&>(other)) { size = other.size; }

    template <typename Data> HashTableClsAdr<Data>::HashTableClsAdr(HashTableClsAdr<Data>&& other) noexcept {
        AllocStorage(CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT);
        this->operator=(std::move(other));
    }





    /**************************************************** ASSIGNMENTS *****************************************/

    template <typename Data> HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& other) noexcept {
        AllocStorage(other.buckets);
        DictionaryContainer<Data>::InsertAll(other);
        size = other.size;
        return *this;
    }

    template <typename Data> HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& other) noexcept {
        storage = std::move(other.storage);
        std::swap(buckets, other.buckets);
        std::swap(size, other.size);
        std::swap(seed, other.seed);
        return *this;
    }




    /*********************************************** COMPARISON OPERATORS *************************************/

    template <typename Data> bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& other) const noexcept {
        try {
            if (size != other.Size()) return false;
            if (size == 0) return true;
            storage.Map([&other](const List<Data>& bucket){
                bucket.Map([&other](const Data& value){
                    if (not other.Exists(value)) throw "hashtables are different!";
                });
            });
            return true;
        } catch(...) { 
            return false;
        }
    }

    template <typename Data> bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& other) const noexcept {
        return not operator==(other);
    }




    /****************************************** DICTIONARY FUNCTIONALITIES ****************************************/

    template <typename Data> bool HashTableClsAdr<Data>::Exists(const Data& target) const noexcept {
        sizetype index = HashFunction(target);
        return storage[index].Exists(target);
    }

    template <typename Data> bool HashTableClsAdr<Data>::Remove(const Data& target) noexcept {
        sizetype index = HashFunction(target);
        bool item_was_removed = storage[index].Remove(target);
        if (item_was_removed) size--;
        return item_was_removed;
    }

    template <typename Data> bool HashTableClsAdr<Data>::Insert(const Data& value) noexcept {
        sizetype index = HashFunction(value);
        bool item_was_inserted = storage[index].Insert(value);
        if (item_was_inserted) size++;
        return item_was_inserted;
    }
    
    template <typename Data> bool HashTableClsAdr<Data>::Insert(Data&& value) noexcept {
        sizetype index = HashFunction(value);
        bool item_was_inserted = storage[index].Insert(std::move(value));
        if (item_was_inserted) size++;
        return item_was_inserted;
    }




    /************************************************ MAP / FOLD **********************************************/
    // notice that even if not explicitly required for this data-structure, maps and folds are
    // still very usefull for debugging purpuses, therfore they have been implemented anyway 

    template <typename Data> void HashTableClsAdr<Data>::Fold(FoldFunctor functor, void* acc) const {
        this->Map([acc, functor](const Data& value){ functor(value, acc); });
    }

    template <typename Data> void HashTableClsAdr<Data>::Map(MapFunctor functor) const {
        for (sizetype i = 0; i < buckets; i++) storage[i].Map(functor);
    }
}
