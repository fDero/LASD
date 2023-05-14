
// FRANCESCO DE ROSA 

#pragma once

#include "htopnadr.hpp"
#include "../../container/dictionary.hpp"

namespace lasd {

    /****************************************** INTERNAL STORAGE HANDLERS *************************************/

    sizetype constexpr OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT = 128;

    template <typename Data> void HashTableOpnAdr<Data>::AllocStorage(sizetype size){
        buckets = std::max(OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT, RoundupPower2(size));
        storage = new HashNode[buckets]();
    }

    template <typename Data> void HashTableOpnAdr<Data>::DeallocStorage(){
        assert (storage != nullptr);
        for (sizetype i = 0; i < buckets; i++) delete storage[i].value;
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
        for (sizetype i = 0; i < buckets; i++) if (storage[i].value != nullptr) resized.Insert(*(storage[i].value));
        this->operator=(std::move(resized)); 
    }

    template <typename Data> void HashTableOpnAdr<Data>::Reset(){
        HashTableOpnAdr<Data> resetted = HashTableOpnAdr<Data>(this->Size(), static_cast<MappableContainer<Data>&&>(std::move(*this)));
        this->operator=(std::move(resetted));
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
        std::swap(removed_data_counter, other.removed_data_counter);
        return *this;
    }




    /*********************************************** COMPARISON OPERATORS *************************************/

    template <typename Data> bool HashTableOpnAdr<Data>::operator==(const HashTableOpnAdr<Data>& other) const noexcept {
        if (size != other.size) return false;
        if (size == 0) return true;
        for (sizetype i = 0; i < buckets; i++) {
            if (storage[i].value != nullptr and not other.Exists(*(storage[i].value))) return false;
        }
        return true;
    }

    template <typename Data> bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& other) const noexcept {
        return not operator==(other);
    }




    /****************************************** DICTIONARY FUNCTIONALITIES ****************************************/

    template <typename Data> bool HashTableOpnAdr<Data>::Exists(const Data& target) const noexcept {
        return const_cast<HashTableOpnAdr<Data>*>(this)->LocateTargetBucket(target).value != nullptr;
    }

    template <typename Data> bool HashTableOpnAdr<Data>::Remove(const Data& target) noexcept {
        HashNode& targetbucket = LocateTargetBucket(target);
        if (targetbucket.value == nullptr) return false;
        delete targetbucket.value;
        targetbucket.value = nullptr;
        targetbucket.removed = true;
        if (--size <= 0.3*buckets) Resize(size);
        if (++removed_data_counter + size >= 0.3*buckets) Reset();
        return true;
    }

    template <typename Data> bool HashTableOpnAdr<Data>::Insert(const Data& target) noexcept {
        HashNode& location = LocateTargetBucket(target);
        if (location.value != nullptr) return false;
        location.value = new Data(target);
        location.removed = false;
        if (++size >= 0.7*buckets) Resize(buckets+100);
        return true;
    }
    
    template <typename Data> bool HashTableOpnAdr<Data>::Insert(Data&& target) noexcept {
        HashNode& location = LocateTargetBucket(target);
        if (location.value != nullptr) return false;
        location.value = new Data(target);
        location.removed = false;
        if (++size >= 0.7*buckets) Resize(buckets+100);
        return true;
    }

    template <typename Data> HashTableOpnAdr<Data>::HashNode& HashTableOpnAdr<Data>::LocateTargetBucket(const Data& value) {
        sizetype index = HashFunction(value);
        while (storage[index].value != nullptr or storage[index].removed){
            if (not storage[index].removed and value == *(storage[index].value)) break;
            ++index %= buckets;
        }
        assert(storage != nullptr);
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
            if (storage[i].value != nullptr) functor(*(storage[i].value));
        }
    }
}