
// FRANCESCO DE ROSA N86004379

#pragma once

#include "queue.hpp"

namespace lasd {

    template <typename Data> Data Queue<Data>::HeadNDequeue() {
        if (Empty()) throw std::length_error("HeadNDequeue() method called on empty queue");
        Data tmp = std::move(Head());
        Dequeue();
        return tmp;
    }
} 