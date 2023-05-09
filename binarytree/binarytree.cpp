
// FRANCESCO DE ROSA N86004379

#pragma once

#include "binarytree.hpp"
#include "../container/mappable.hpp"
#include "../queue/vec/queuevec.hpp"
#include <type_traits>

namespace lasd {

    /******************************************************* NODE ***************************************************************/

    template <typename Data> inline bool BinaryTree<Data>::Node::IsLeaf() const noexcept {
        return (not HasLeftChild()) and (not HasRightChild()); 
    }
    
    template <typename Data> inline bool BinaryTree<Data>::Node::HasLeftChild() const noexcept {
        try { LeftChild(); return true; } catch(...) { return false; } 
    }
    
    template <typename Data> inline bool BinaryTree<Data>::Node::HasRightChild() const noexcept {
        try { RightChild(); return true; } catch(...) { return false; } 
    }    



    /************************************************** COMPARISON OPERATORS **************************************************/
    // the utility free function 'CompareSubTrees' has been provided to the user to compare two subtrees given the two roots

    template <typename Data> bool BinaryTree<Data>::CompareSubtrees(const Node& ax, const Node& bx) const noexcept {
        if (ax.HasLeftChild() != bx.HasLeftChild()) return false;
        if (ax.HasRightChild() != bx.HasRightChild()) return false;
        if (ax.HasLeftChild() and !CompareSubtrees(ax.LeftChild(), bx.LeftChild())) return false;
        if (ax.HasRightChild() and !CompareSubtrees(ax.RightChild(), bx.RightChild())) return false;
        return ax.Element() == bx.Element();
    }

    template <typename Data> bool BinaryTree<Data>::operator==(const BinaryTree<Data>& other) const noexcept {
        if(size != other.Size()) return false;
        if(size == 0) return true;
        return CompareSubtrees(Root(), other.Root());
    } 

    template <typename Data> inline bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& other) const noexcept {
        return not operator==(other);
    }
    


    /******************************************************* FOLD ***********************************************************/
    // the override is necessary because of the insurgence of errors such as 'no unique final overrider' for member-function 'Fold'

    template <typename Data> inline void BinaryTree<Data>::Fold(typename BinaryTree<Data>::FoldFunctor ff, void* accumulator) const {
        PreOrderMappableContainer<Data>::PreOrderFold(ff, accumulator);
    } 



    /************************************************ MAP HELPER FUNCTIONS **************************************************/
   
    template <typename Data> void BinaryTree<Data>::PreOrderMapOnSubtree(MapFunctor mf, const Node& node) const {
        mf(node.Element());
        if (node.HasLeftChild()) PreOrderMapOnSubtree(mf, node.LeftChild());
        if (node.HasRightChild()) PreOrderMapOnSubtree(mf, node.RightChild());
    }    

    template <typename Data> void BinaryTree<Data>::PostOrderMapOnSubtree(MapFunctor mf, const Node& node) const {
        if (node.HasLeftChild()) PostOrderMapOnSubtree(mf, node.LeftChild());
        if (node.HasRightChild()) PostOrderMapOnSubtree(mf, node.RightChild());
        mf(node.Element());
    }   

    template <typename Data> void BinaryTree<Data>::InOrderMapOnSubtree(MapFunctor mf, const Node& node) const {
        if (node.HasLeftChild()) InOrderMapOnSubtree(mf, node.LeftChild());
        mf(node.Element());
        if (node.HasRightChild()) InOrderMapOnSubtree(mf, node.RightChild());
    }

    template <typename Data> void BinaryTree<Data>::BreadthMapOnSubtree(MapFunctor mf, const Node& node) const { 
        QueueVec<Node const*> frointier;
        frointier.Enqueue(&node);
        while(not frointier.Empty()){
            if(frointier.Head()->HasLeftChild())  frointier.Enqueue(&frointier.Head()->LeftChild());
            if(frointier.Head()->HasRightChild()) frointier.Enqueue(&frointier.Head()->RightChild());
            mf(frointier.HeadNDequeue()->Element());
        }
    }




    /******************************************************* MAPS ****************************************************/

    template <typename Data> inline void BinaryTree<Data>::Map(typename BinaryTree<Data>::MapFunctor mf) const {
        if(not Empty()) PreOrderMapOnSubtree(mf, Root());
    } 
    

    template <typename Data> inline void BinaryTree<Data>::PreOrderMap(typename BinaryTree<Data>::MapFunctor mf) const {
        if(not Empty()) PreOrderMapOnSubtree(mf, Root());
    } 
    
    template <typename Data> inline void BinaryTree<Data>::PostOrderMap(typename BinaryTree<Data>::MapFunctor mf) const {
        if(not Empty()) PostOrderMapOnSubtree(mf, Root());
    } 

    template <typename Data> inline void BinaryTree<Data>::InOrderMap(typename BinaryTree<Data>::MapFunctor mf) const {
        if(not Empty()) InOrderMapOnSubtree(mf, Root());
    } 

    template <typename Data> inline void BinaryTree<Data>::BreadthMap(typename BinaryTree<Data>::MapFunctor mf) const {
        if(not Empty()) BreadthMapOnSubtree(mf, Root());
    }




    /****************************************************** MUTABLE MAPS *********************************************/

    template <typename Data> void MutableBinaryTree<Data>::Map(MutableMapFunctor mmf) {
        MapFunctor mf = [&mmf](const Data& data) { mmf(const_cast<Data&>(data)); };
        static_cast<const MutableBinaryTree<Data>*>(this)->Map(mf);
    } 
    
    template <typename Data> void MutableBinaryTree<Data>::PreOrderMap(MutableMapFunctor mmf) {
        MapFunctor mf = [&mmf](const Data& data) { mmf(const_cast<Data&>(data)); };
        static_cast<const MutableBinaryTree<Data>*>(this)->PreOrderMap(mf);
    } 
    
    template <typename Data> void MutableBinaryTree<Data>::PostOrderMap(MutableMapFunctor mmf) {
        MapFunctor mf = [&mmf](const Data& data) { mmf(const_cast<Data&>(data)); };
        static_cast<const MutableBinaryTree<Data>*>(this)->PostOrderMap(mf); 
    }

    template <typename Data> void MutableBinaryTree<Data>::InOrderMap(MutableMapFunctor mmf) {
        MapFunctor mf = [&mmf](const Data& data) { mmf(const_cast<Data&>(data)); };
        static_cast<const MutableBinaryTree<Data>*>(this)->InOrderMap(mf);
    } 

    template <typename Data> void MutableBinaryTree<Data>::BreadthMap(MutableMapFunctor mmf) {
        MapFunctor mf = [&mmf](const Data& data) { mmf(const_cast<Data&>(data)); };
        static_cast<const MutableBinaryTree<Data>*>(this)->BreadthMap(mf);
    }




    /************************************************** NON MUTABLE MAPS *********************************************/
    // the override is necessary because of the insurgence of errors such as 'no unique final overrider' for the following member-functions

    template <typename Data> inline void MutableBinaryTree<Data>::Map(MapFunctor mf)          const { BinaryTree<Data>::Map(mf); } 
    template <typename Data> inline void MutableBinaryTree<Data>::PreOrderMap(MapFunctor mf)  const { BinaryTree<Data>::PreOrderMap(mf); } 
    template <typename Data> inline void MutableBinaryTree<Data>::PostOrderMap(MapFunctor mf) const { BinaryTree<Data>::PostOrderMap(mf); } 
    template <typename Data> inline void MutableBinaryTree<Data>::InOrderMap(MapFunctor mf)   const { BinaryTree<Data>::InOrderMap(mf); } 
    template <typename Data> inline void MutableBinaryTree<Data>::BreadthMap(MapFunctor mf)   const { BinaryTree<Data>::BreadthMap(mf); }
}
