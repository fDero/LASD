
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

    template <typename Node> bool CompareSubTrees(const Node& ax, const Node& bx) {
        if (ax.HasLeftChild() != bx.HasLeftChild()) return false;
        if (ax.HasRightChild() != bx.HasRightChild()) return false;
        if (ax.HasLeftChild() and !CompareSubTrees(ax.LeftChild(), bx.LeftChild())) return false;
        if (ax.HasRightChild() and !CompareSubTrees(ax.RightChild(), bx.RightChild())) return false;
        return ax.Element() == bx.Element();
    }

    template <typename Data> bool BinaryTree<Data>::operator==(const BinaryTree<Data>& other) const noexcept {
        if(size != other.Size()) return false;
        if(size == 0) return true;
        return CompareSubTrees(Root(), other.Root());
    } 

    template <typename Data> inline bool BinaryTree<Data>::operator!=(const BinaryTree<Data>& other) const noexcept {
        return not operator==(other);
    }
    


    /******************************************************* FOLD ***********************************************************/
    // the override is necessary because of the insurgence of errors such as 'no unique final overrider' for member-function 'Fold'

    template <typename Data> inline void BinaryTree<Data>::Fold(typename BinaryTree<Data>::FoldFunctor ff, void* accumulator) const {
        PreOrderMappableContainer<Data>::PreOrderFold(ff, accumulator);
    } 



    /************************************************ MAP HELPER FUNCTIONS ****************************************************/
    // these free functions can be called on BinaryTree<Data>::Node, MutableBinaryTree<Data>::MutableNode, BinaryTreeLnk<Data>::NodeLnk
    // and every other node-like type thanks to universal-referencing, a technique aviable since C++11
    // (more info: https://isocpp.org/blog/2012/11/universal-references-in-c11-scott-meyers). The effect of this functions is to perform
    // a map (PreOrder/PostOrder/InOrder/Breadth) on a subtree given the root node of that subtree. The '&&' (universal reference) can 
    // be translated in both & and const& so that both mutable and immutable cases are covered. In 'BreadthMapOnSubtree' std::remove_reference
    // is used to avoid having a pointer to a non const reference (wich in C++ is illegal)
   
    template <typename Functor, typename Node> void PreOrderMapOnSubtree(Functor mf, Node&& node){
        mf(node.Element());
        if (node.HasLeftChild()) PreOrderMapOnSubtree(mf, node.LeftChild());
        if (node.HasRightChild()) PreOrderMapOnSubtree(mf, node.RightChild());
    }    

    template <typename Functor, typename Node> void PostOrderMapOnSubtree(Functor mf, Node&& node){
        if (node.HasLeftChild()) PostOrderMapOnSubtree(mf, node.LeftChild());
        if (node.HasRightChild()) PostOrderMapOnSubtree(mf, node.RightChild());
        mf(node.Element());
    }   

    template <typename Functor, typename Node> void InOrderMapOnSubtree(Functor mf, Node&& node){
        if (node.HasLeftChild()) InOrderMapOnSubtree(mf, node.LeftChild());
        mf(node.Element());
        if (node.HasRightChild()) InOrderMapOnSubtree(mf, node.RightChild());
    }

    template <typename Functor, typename Node> inline void BreadthMapOnSubtree(Functor mf, Node&& node){ 
        QueueVec<typename std::remove_reference<Node>::type*> frointier;
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

    template <typename Data> inline void MutableBinaryTree<Data>::Map(MutableMapFunctor mf) {
        if(not Empty()) PreOrderMapOnSubtree(mf, Root());
    } 
    

    template <typename Data> inline void MutableBinaryTree<Data>::PreOrderMap(MutableMapFunctor mf) {
        if(not Empty()) PreOrderMapOnSubtree(mf, Root());
    } 
    
    template <typename Data> inline void MutableBinaryTree<Data>::PostOrderMap(MutableMapFunctor mf) {
        if(not Empty()) PostOrderMapOnSubtree(mf, Root());
    } 

    template <typename Data> inline void MutableBinaryTree<Data>::InOrderMap(MutableMapFunctor mf) {
        if(not Empty()) InOrderMapOnSubtree(mf, Root());
    } 

    template <typename Data> inline void MutableBinaryTree<Data>::BreadthMap(MutableMapFunctor mf) {
        if(not Empty()) BreadthMapOnSubtree(mf, Root());
    }




    /************************************************** NON MUTABLE MAPS *********************************************/
    // the override is necessary because of the insurgence of errors such as 'no unique final overrider' for the following member-functions

    template <typename Data> inline void MutableBinaryTree<Data>::Map(MapFunctor mf)          const { BinaryTree<Data>::Map(mf); } 
    template <typename Data> inline void MutableBinaryTree<Data>::PreOrderMap(MapFunctor mf)  const { BinaryTree<Data>::PreOrderMap(mf); } 
    template <typename Data> inline void MutableBinaryTree<Data>::PostOrderMap(MapFunctor mf) const { BinaryTree<Data>::PostOrderMap(mf); } 
    template <typename Data> inline void MutableBinaryTree<Data>::InOrderMap(MapFunctor mf)   const { BinaryTree<Data>::InOrderMap(mf); } 
    template <typename Data> inline void MutableBinaryTree<Data>::BreadthMap(MapFunctor mf)   const { BinaryTree<Data>::BreadthMap(mf); }
}
