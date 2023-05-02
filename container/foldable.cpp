
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "testable.hpp"
#include <functional>
#include "foldable.hpp"

namespace lasd {

    template <typename Data> bool FoldableContainer<Data>::Exists(const Data& target) const noexcept {
        bool found = false;
        auto search = [target](const Data& value, void* flag){ *((bool*)flag) |= (value == target); };
        Fold(search,&found);
        return found;
    }

    template <typename Data> inline void PreOrderFoldableContainer<Data>::Fold(FoldFunctor functor, void* accumulator) const { 
        PreOrderFold(functor, accumulator); 
    }

    template <typename Data> inline void PostOrderFoldableContainer<Data>::Fold(FoldFunctor functor, void* accumulator) const { 
        PostOrderFold(functor, accumulator); 
    }

    template <typename Data> inline void InOrderFoldableContainer<Data>::Fold(FoldFunctor functor, void* accumulator) const { 
        InOrderFold(functor, accumulator); 
    }

    template <typename Data> inline void BreadthFoldableContainer<Data>::Fold(FoldFunctor functor, void* accumulator) const { 
        BreadthFold(functor, accumulator); 
    }
}