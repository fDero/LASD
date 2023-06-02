
// FRANCESCO DE ROSA N86004379

#pragma once

#include "binarytreevec.hpp"
#include "../../container/mappable.hpp"
#include <cassert>

namespace lasd {

    /************************************************* NODEVEC **********************************************/

    template<typename Data> const Data& BinaryTreeVec<Data>::NodeVec::Element() const noexcept { return value; }
    template<typename Data> Data& BinaryTreeVec<Data>::NodeVec::Element() noexcept { return value; }

    template<typename Data> const BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::RightChild() const { 
        sizetype rightchild_index = 2*index + 2;
        if (rightchild_index >= tree->size) throw std::length_error("illegal requeste for a non-present node's right child");
        return tree->nodes[rightchild_index]; 
    }
    
    template<typename Data> MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::RightChild() { 
        sizetype rightchild_index = 2*index + 2;
        if (rightchild_index >= tree->size) throw std::length_error("illegal requeste for a non-present node's right child");
        return tree->nodes[rightchild_index];
    }

    template<typename Data> const BinaryTree<Data>::Node& BinaryTreeVec<Data>::NodeVec::LeftChild() const { 
        sizetype leftchild_index = 2*index + 1;
        if (leftchild_index >= tree->size) throw std::length_error("illegal requeste for a non-present node's left child");
        return tree->nodes[leftchild_index]; 
    }

    template<typename Data> MutableBinaryTree<Data>::MutableNode& BinaryTreeVec<Data>::NodeVec::LeftChild() { 
        sizetype leftchild_index = 2*index + 1;
        if (leftchild_index >= tree->size) throw std::length_error("illegal requeste for a non-present node's left child");
        return tree->nodes[leftchild_index]; 
    }




    /*********************************************** CONSTRUCTORS **********************************************/

    template<typename Data> BinaryTreeVec<Data>::~BinaryTreeVec() noexcept { delete [] nodes; }

    template<typename Data> BinaryTreeVec<Data>::BinaryTreeVec(const MappableContainer<Data>& other) noexcept {
        nodes = safe_nodes_alloc(other.Size());
        size = 0;
        other.Map([this](const Data& value) { 
            nodes[size].tree = this; 
            nodes[size].index = size; 
            nodes[size].value = value;
            size++; 
        });
    }

    template<typename Data> BinaryTreeVec<Data>::BinaryTreeVec(MutableMappableContainer<Data>&& other) noexcept {
        nodes = safe_nodes_alloc(other.Size());
        size = 0;
        other.Map([this](Data& value) { 
            nodes[size].tree =  this; 
            nodes[size].index = size;
            nodes[size].value = std::move(value);
            size++; 
        });
    }

    template<typename Data> BinaryTreeVec<Data>::BinaryTreeVec(const BinaryTreeVec<Data>& other) noexcept {
        this->operator=(other);
    }

    template<typename Data> BinaryTreeVec<Data>::BinaryTreeVec(BinaryTreeVec<Data>&& other) noexcept {
        this->operator=(std::move(other));
    }

    
    template<typename Data> BinaryTreeVec<Data>::NodeVec* BinaryTreeVec<Data>::safe_nodes_alloc(sizetype length) noexcept {
        return (length != 0)? new NodeVec[length] : nullptr;
    }


    


    /************************************************ ASSIGNMENT OPERATORS *******************************************/

    template<typename Data> BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(const BinaryTreeVec<Data>& other) noexcept {
        delete [] nodes;
        size = other.Size();
        nodes = safe_nodes_alloc(other.Size());
        for (sizetype i = 0; i < size; i++){
            nodes[i].value = other.nodes[i].value;
            nodes[i].tree = this;
            nodes[i].index = other.nodes[i].index;
        }
        return *this;
    }

    template<typename Data> BinaryTreeVec<Data>& BinaryTreeVec<Data>::operator=(BinaryTreeVec<Data>&& other) noexcept {
        std::swap(nodes, other.nodes);
        std::swap(size, other.size);
        for (sizetype i = 0; i < size; i++) nodes[i].tree = this;
        return *this;
    }






    /************************************************* ROOT GETTERS *********************************************/

    template<typename Data> const BinaryTreeVec<Data>::Node& BinaryTreeVec<Data>::Root() const {
        if (size == 0) throw std::length_error("attempt to get the root from an empty tree");
        return nodes[0];
    }

    template<typename Data> BinaryTreeVec<Data>::MutableNode& BinaryTreeVec<Data>::Root() {
        if (size == 0) throw std::length_error("attempt to get the root from an empty tree");
        return nodes[0];
    }




    /******************************************** COMPARISON OPERATORS ***************************************/

    template<typename Data> bool BinaryTreeVec<Data>::operator==(const BinaryTreeVec<Data>& other) const noexcept {
        if (size != other.Size()) return false;
        for (sizetype i = 0; i < size; i++){ if (other.nodes[i].value != nodes[i].value) return false; }
        return true;
    }

    template<typename Data> inline bool BinaryTreeVec<Data>::operator!=(const BinaryTreeVec<Data>& other) const noexcept {
        return not operator==(other);
    }




    /********************************************** OVERRIDES ***************************************/

    template<typename Data> void BinaryTreeVec<Data>::BreadthMap(MapFunctor mf) const {
        for (sizetype i = 0; i < size; i++) mf(nodes[i].value);
    }

    template<typename Data> void BinaryTreeVec<Data>::BreadthMap(MutableMapFunctor mf) {
        for (sizetype i = 0; i < size; i++) mf(nodes[i].value);
    }
    
    template<typename Data> void BinaryTreeVec<Data>::Clear(){
        delete [] nodes;
        nodes = nullptr;
        size = 0;
    }
}