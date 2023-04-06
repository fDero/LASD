
// FRANCESCO DE ROSA N86004379

#pragma once

#include "queue.hpp"

namespace lasd {
    
    template <typename Data> Queue<Data>::Queue(const MappableContainer<Data>& container) {
        container.Map([this](const Data& value){ this->Enqueue(value); });
    }

    template <typename Data> Queue<Data>::Queue(MutableMappableContainer<Data>&& container) {
        container.Map([this](Data& value){ this->Enqueue(std::move(value)); });
    }

    template <typename Data> Data Queue<Data>::HeadNDequeue() {
        Data tmp = std::move(Head());
        Dequeue();
        return tmp;
    }
} 