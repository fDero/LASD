
// FRANCESCO DE ROSA 

#pragma once

#include "htclsadr.hpp"
#include "../../container/dictionary.hpp"

namespace lasd {

    /****************************************** INTERNAL STORAGE HANDLERS *************************************/

    sizetype constexpr CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT = 64;

    template <typename Data> void HashTableClsAdr<Data>::AllocStorage(sizetype size){
        buckets = std::max(CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT, RoundupPower2(size));
        storage = new ConcreteDictionaryType*[buckets] (nullptr);
    }

    template <typename Data> void HashTableClsAdr<Data>::DeallocStorage(){
        assert (storage != nullptr);
        for (sizetype i = 0; i < buckets; i++) delete storage[i];
        delete[] storage;
    }

    template <typename Data> void HashTableClsAdr<Data>::Clear() noexcept {
        DeallocStorage();
        AllocStorage(CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT);
        size = 0;
    }

    template <typename Data> void HashTableClsAdr<Data>::Resize(sizetype newsize) noexcept {
        if (buckets == std::max(RoundupPower2(newsize),CLOSED_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT)) return;
        auto resized = HashTableClsAdr<Data>(newsize);
        for (sizetype i = 0; i < buckets; i++) if (storage[i] != nullptr) resized.InsertAll(*(storage[i]));
        this->operator=(std::move(resized)); 
    }




    /**************************************** CONSTRUCTORS AND DISTRUCTORS **********************************/

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
        this->operator=(std::move(other));
    }

    template <typename Data> HashTableClsAdr<Data>::~HashTableClsAdr() noexcept {
        DeallocStorage();
    }




    /**************************************************** ASSIGNMENTS *****************************************/

    template <typename Data> HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(const HashTableClsAdr<Data>& other) noexcept {
        DeallocStorage();
        AllocStorage(other.buckets);
        DictionaryContainer<Data>::InsertAll(other);
        size = other.size;
        return *this;
    }

    template <typename Data> HashTableClsAdr<Data>& HashTableClsAdr<Data>::operator=(HashTableClsAdr<Data>&& other) noexcept {
        std::swap(storage, other.storage);
        std::swap(buckets, other.buckets);
        std::swap(size, other.size);
        std::swap(seed, other.seed);
        return *this;
    }




    /*********************************************** COMPARISON OPERATORS *************************************/

    template <typename Data> bool HashTableClsAdr<Data>::operator==(const HashTableClsAdr<Data>& other) const noexcept {
        if (size != other.Size()) return false;
        if (size == 0) return true;
        HashTableClsAdr<Data>& ccother = const_cast<HashTableClsAdr<Data>&>(other);
        for (sizetype i = 0; i < buckets; i++){
            if (storage[i] != nullptr) {
                bool success = true;
                storage[i]->Map([&ccother, &success](const Data& value){ success &= ccother.Exists(value); });
                if (not success) return false;
            }
        }
        return true;
    }

    template <typename Data> bool HashTableClsAdr<Data>::operator!=(const HashTableClsAdr<Data>& other) const noexcept {
        return not operator==(other);
    }




    /****************************************** DICTIONARY FUNCTIONALITIES ****************************************/

    template <typename Data> bool HashTableClsAdr<Data>::Exists(const Data& target) const noexcept {
        sizetype index = HashFunction(target);
        if (storage[index] == nullptr) return false;
        return storage[index]->Exists(target);
    }

    template <typename Data> bool HashTableClsAdr<Data>::Remove(const Data& target) noexcept {
        sizetype index = HashFunction(target);
        if (storage[index] == nullptr) return false;
        if (not storage[index]->Remove(target)) return false;
        size--;
        return true;
    }

    template <typename Data> bool HashTableClsAdr<Data>::Insert(const Data& target) noexcept {
        return InsertHelper(target);
    }
    
    template <typename Data> bool HashTableClsAdr<Data>::Insert(Data&& target) noexcept {
        return InsertHelper(std::move(target));
    }

    template <typename Data> template<typename ValueType> bool HashTableClsAdr<Data>::InsertHelper(ValueType&& target) {
        sizetype index = HashFunction(target);
        if (storage[index] != nullptr) {
            if (storage[index]->Insert(std::forward<ValueType>(target))){
                size++;
                return true;
            }
            return false;
        } 
        storage[index] = new ConcreteDictionaryType();
        storage[index]->Insert(std::forward<ValueType>(target));
        size++;
        return true;
    }




    /************************************************ MAP / FOLD **********************************************/
    // notice that even if not explicitly required for this data-structure, maps and folds are
    // still very usefull for debugging purpuses, therfore they have been implemented anyway 

    template <typename Data> void HashTableClsAdr<Data>::Fold(FoldFunctor functor, void* acc) const {
        this->Map([acc, functor](const Data& value){ functor(value, acc); });
    }

    template <typename Data> void HashTableClsAdr<Data>::Map(MapFunctor functor) const {
        for (sizetype i = 0; i < buckets; i++){
            if (storage[i] != nullptr) static_cast<ConcreteDictionaryType const*>(storage[i])->Map(functor);
        }
    }
}
