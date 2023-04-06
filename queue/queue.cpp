
// FRANCESCO DE ROSA N86004379

#pragma once

#include "queue.hpp"

namespace lasd {
    
    template <typename Data> Data Queue<Data>::HeadNDequeue() {
        Data tmp = std::move(Head());
        Dequeue();
        return tmp;
    }
} 