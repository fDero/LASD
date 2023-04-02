
// FRANCESCO DE ROSA N86004379

#pragma once

#include "testable.hpp"
#include "mappable.hpp"
#include "dictionary.hpp"

namespace lasd {

    template <typename Data> bool DictionaryContainer<Data>::InsertAll(const MappableContainer<Data>& source) {
        bool every_single_item_was_inserted = true;
        auto functor = [this](const Data& value, void* flag){ *((bool*)flag) &= this->Insert(value); };
        source.Fold(functor, &every_single_item_was_inserted);
        return every_single_item_was_inserted;
    }

    template <typename Data> bool DictionaryContainer<Data>::InsertAll(const MutableMappableContainer<Data>& source) {
        bool every_single_item_was_inserted = true;
        auto functor = [this](const Data& value, void* flag){ *((bool*)flag) &= this->Insert(value); };
        source.Fold(functor, &every_single_item_was_inserted);
        return every_single_item_was_inserted; 
    }

    template <typename Data> bool DictionaryContainer<Data>::RemoveAll(const MappableContainer<Data>& source) {
        bool every_single_item_was_removed = true;
        auto functor = [this](const Data& value, void* flag){ *((bool*)flag) &= this->Remove(value); };
        source.Fold(functor, &every_single_item_was_removed);
        return every_single_item_was_removed;
    }

    template <typename Data> bool DictionaryContainer<Data>::InsertSome(const MappableContainer<Data>& source) {
        bool at_least_one_item_was_inserted = false;
        auto functor = [this](const Data& value, void* flag){ *((bool*)flag) |= this->Insert(value); };
        source.Fold(functor, &at_least_one_item_was_inserted);
        return at_least_one_item_was_inserted;
    };
      
    template <typename Data> bool DictionaryContainer<Data>::InsertSome(const MutableMappableContainer<Data>& source) {
        bool at_least_one_item_was_inserted = false;
        auto functor = [this](const Data& value, void* flag){ *((bool*)flag) |= this->Insert(value); };
        source.Fold(functor, &at_least_one_item_was_inserted);
        return at_least_one_item_was_inserted;
    };

    template <typename Data> bool DictionaryContainer<Data>::RemoveSome(const MappableContainer<Data>& source) {
        bool at_least_one_item_was_removed = false;
        auto functor = [this](const Data& value, void* flag){ *((bool*)flag) |= this->Remove(value); };
        source.Fold(functor, &at_least_one_item_was_removed);
        return at_least_one_item_was_removed;
    };
}