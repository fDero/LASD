
// FRANCESCO DE ROSA N86004379

#include "stack.hpp"

namespace lasd {
    
    template <typename Data> Data Stack<Data>::TopNPop() {
        Data tmp = std::move(Top());
        Pop();
        return tmp;
    }
}
