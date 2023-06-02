
// FRANCESCO DE ROSA 

#pragma once

#include "htopnadr.hpp"
#include "../../container/dictionary.hpp"

namespace lasd {

    /****************************************** INTERNAL STORAGE HANDLERS *************************************/

    sizetype constexpr OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT = 128;
    
    double constexpr CRITICAL_SIZE_LOWERBOUND_TRESHOLD_RATEO = 0.4;
    double constexpr CRITICAL_SIZE_UPPERBOUND_TRESHOLD_RATEO = 0.7;
    double constexpr CRITICAL_UNUSED_BUCKET_TRESHOLD_RATEO   = 0.3;


    template <typename Data> void HashTableOpnAdr<Data>::AllocStorage(sizetype size){
        buckets = std::max(OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT, RoundupPower2(size));
        values_storage.Resize(buckets);
        state_storage.Resize(buckets);
        state_storage.Map([](State& state){ state = State::EMPTY; });
    }

    template <typename Data> void HashTableOpnAdr<Data>::Clear() noexcept {
        AllocStorage(OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT);
        size = 0;
    }

    template <typename Data> void HashTableOpnAdr<Data>::Resize(sizetype newsize) noexcept {
        if (buckets == std::max(RoundupPower2(newsize),OPEN_ADDRESSING_HASHTABLE_MINIMUM_BUCKET_AMOUNT)) return;
        auto resized = HashTableOpnAdr<Data>(newsize, *this);
        this->operator=(std::move(resized)); 
    }

    template <typename Data> void HashTableOpnAdr<Data>::Reset(){
        auto resetted = HashTableOpnAdr<Data>(*this);
        this->operator=(std::move(resetted));
    }




    /************************************************* CONSTRUCTORS **********************************************/

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




    /**************************************************** ASSIGNMENTS *****************************************/

    template <typename Data> HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(const HashTableOpnAdr<Data>& other) noexcept {
        this->Clear();
        DictionaryContainer<Data>::InsertAll(other);
        size = other.size;
        return *this;
    }

    template <typename Data> HashTableOpnAdr<Data>& HashTableOpnAdr<Data>::operator=(HashTableOpnAdr<Data>&& other) noexcept {
        state_storage = std::move(other.state_storage);
        values_storage = std::move(other.values_storage);
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
            if (state_storage[i] == State::OCCUPIED and !other.Exists(values_storage[i])) return false;
        }
        return true;
    }

    template <typename Data> bool HashTableOpnAdr<Data>::operator!=(const HashTableOpnAdr<Data>& other) const noexcept {
        return not operator==(other);
    }




    /****************************************** DICTIONARY FUNCTIONALITIES ****************************************/

    template <typename Data> bool HashTableOpnAdr<Data>::Exists(const Data& target) const noexcept {
        auto [ search_index, insertion_index ] = LocateBucket(target);
        return state_storage[search_index] == State::OCCUPIED;
        auto const_casted = const_cast<HashTableOpnAdr<Data>*>(this);
        std::swap(const_casted->values_storage[search_index], const_casted->values_storage[insertion_index]);
        std::swap(const_casted->state_storage[search_index], const_casted->state_storage[insertion_index]);
    }

    template <typename Data> bool HashTableOpnAdr<Data>::Remove(const Data& target) noexcept {
        auto [ search_index, insertion_index ] = LocateBucket(target);
        return RemoveAtIndex(target, search_index);
    }

    template <typename Data> bool HashTableOpnAdr<Data>::RemoveAtIndex(const Data& target, sizetype index) noexcept {
        if (state_storage[index] != State::OCCUPIED) return false;
        state_storage[index] = State::CLEARED;
        if (--size <= CRITICAL_SIZE_LOWERBOUND_TRESHOLD_RATEO * buckets) Resize(buckets/2);
        else if (++removed_data_counter >= CRITICAL_UNUSED_BUCKET_TRESHOLD_RATEO * buckets) Reset();
        return true;
    }
    
    template <typename Data> bool HashTableOpnAdr<Data>::Insert(const Data& value) noexcept { 
        return InsertHelper(value); 
    }

    template <typename Data> bool HashTableOpnAdr<Data>::Insert(Data&& value) noexcept { 
        return InsertHelper(std::move(value)); 
    }

    template <typename Data> template<typename ValueType> bool HashTableOpnAdr<Data>::InsertHelper(ValueType&& value) noexcept {
        auto [ search_index, insertion_index ] = LocateBucket(value);
        if (state_storage[insertion_index] == State::OCCUPIED) return false;
        bool item_was_removed = RemoveAtIndex(value, search_index);
        if (state_storage[insertion_index] == State::CLEARED) removed_data_counter--;
        state_storage[insertion_index] = State::OCCUPIED;
        values_storage[insertion_index] = std::forward<ValueType>(value);
        if (++size >= CRITICAL_SIZE_UPPERBOUND_TRESHOLD_RATEO * buckets) Resize(buckets*2);
        return not item_was_removed;
    }

    template <typename Data> std::pair<sizetype, sizetype> HashTableOpnAdr<Data>::LocateBucket(const Data& target) const noexcept {
        sizetype encoding = HashFunction(target);
        sizetype index = encoding;
        long long first_cleared_bucket = -1;
        for (sizetype attempt = 1; attempt < buckets; attempt++) {
            if (state_storage[index] != State::OCCUPIED and first_cleared_bucket == -1) first_cleared_bucket = index;
            if (state_storage[index] == State::OCCUPIED and values_storage[index] == target) break;
            if (state_storage[index] == State::EMPTY) break;
            index = attempt*attempt + attempt;
            index = (index/2 + encoding) % buckets; 
        }
        if (first_cleared_bucket == -1) first_cleared_bucket = index;
        return {index, static_cast<sizetype>(first_cleared_bucket)};
    }







    /************************************************ MAP / FOLD **********************************************/
    // notice that even if not explicitly required for this data-structure, maps and folds are
    // still very usefull for debugging purpuses, therfore they have been implemented anyway 

    template <typename Data> void HashTableOpnAdr<Data>::Fold(FoldFunctor functor, void* acc) const {
        this->Map([acc, functor](const Data& value){ functor(value, acc); });
    }

    template <typename Data> void HashTableOpnAdr<Data>::Map(MapFunctor functor) const {
        for (sizetype i = 0; i < buckets; i++) if (state_storage[i] == State::OCCUPIED) functor(values_storage[i]);
    }
}