
// FRANCESCO DE ROSA N86004379

#pragma once

#include "testable.hpp"
#include "mappable.hpp"


namespace lasd {

    
    /********************************************************* MAPS IN TERMS OF SPECIFIC MAPS **************************************************************/

    template <typename Data> void MutablePreOrderMappableContainer<Data>::Map(MutableMapFunctor functor)  { PreOrderMap(functor); }
    template <typename Data> void MutablePostOrderMappableContainer<Data>::Map(MutableMapFunctor functor) { PostOrderMap(functor); }
    template <typename Data> void MutableInOrderMappableContainer<Data>::Map(MutableMapFunctor functor)   { InOrderMap(functor); }
    template <typename Data> void MutableBreadthMappableContainer<Data>::Map(MutableMapFunctor functor)   { BreadthOrderMap(functor); }

    template <typename Data> void PreOrderMappableContainer<Data>::Map(MapFunctor functor) const  { PreOrderMap(functor); }
    template <typename Data> void PostOrderMappableContainer<Data>::Map(MapFunctor functor) const { PostOrderMap(functor); }
    template <typename Data> void InOrderMappableContainer<Data>::Map(MapFunctor functor) const   { InOrderMap(functor); }
    template <typename Data> void BreadthMappableContainer<Data>::Map(MapFunctor functor) const   { BreadthOrderMap(functor); }




    /***********************************************************  FOLDS DEFINED IN TERMS OF MAPS *******************************************************/

    template <typename Data> void PreOrderMappableContainer<Data>::PreOrderFold(FoldFunctor functor, void* accumulator) const {
        PreOrderMap([functor, accumulator](const Data& value){ functor(value, accumulator); });
    }

    template <typename Data> void PostOrderMappableContainer<Data>::PostOrderFold(FoldFunctor functor, void* accumulator) const {
        PostOrderMap([functor, accumulator](const Data& value){ functor(value, accumulator); });
    }

    template <typename Data> void InOrderMappableContainer<Data>::InOrderFold(FoldFunctor functor, void* accumulator) const {
        InOrderMap([functor, accumulator](const Data& value){ functor(value, accumulator); });
    }

    template <typename Data> void BreadthMappableContainer<Data>::BreadthFold(FoldFunctor functor, void* accumulator) const {
        BreadthMap([functor, accumulator](const Data& value){ functor(value, accumulator); });
    }



    /********************************************************** MAPS DEFINED IN TERMS OF MUTABLE MAPS ***************************************************/

    // note that in this scenario, we know (and we are 100% sure about it) that the operation is not going to alter the internal state of the classes 
    // since although we are performing a mutable mapping, we are doing so by iterating a function wich takes a const reference argument
    // therefore the values do not change hence we mark the method as const

/*
    template <typename Data> void MutablePreOrderMappableContainer<Data>::PreOrderMap(MapFunctor functor) const {
        const_cast<MutablePreOrderMappableContainer<Data>*>(this)->PreOrderMap(???);
    }

    template <typename Data> void MutablePostOrderMappableContainer<Data>::PostOrderMap(MapFunctor functor) const {
        //((const PostOrderMappableContainer<Data>&)(*this)).PostOrderMap([functor](Data& value){ functor(value); });
    }

    template <typename Data> void MutableInOrderMappableContainer<Data>::InOrderMap(MapFunctor functor) const {
        //((const InOrderMappableContainer<Data>&)(*this)).InOrderMap([functor](Data& value){ functor(value); });
    }

    template <typename Data> void MutableBreadthMappableContainer<Data>::BreadthMap(MapFunctor functor) const {
        //((const BreadthMappableContainer<Data>&)(*this)).BreadthMap([functor](Data& value){ functor(value); });
    }
  */  
}