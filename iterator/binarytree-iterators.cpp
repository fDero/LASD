
// FRANCESCO DE ROSA N86004379

#pragma once

#include "binarytree-const-iterators.hpp"
#include "binarytree-mutable-iterators.hpp"

namespace lasd {

    /********************************************** GENERIC BINARYTREEITERATOR ****************************************/

    template <typename Data> inline bool BinaryTreeIterator<Data>::Terminated() const noexcept {
        return current == nullptr;
    }

    template <typename Data> const Data& BinaryTreeIterator<Data>::operator*() const {
        if (current == nullptr) throw std::out_of_range("attempt to read a value from a terminated iterator");
        return current->Element();
    }

    template <typename Data> inline const Data& BinaryTreeMutableIterator<Data>::operator*() const {
        return BinaryTreeIterator<Data>::operator*();
    }

    template <typename Data> inline Data& BinaryTreeMutableIterator<Data>::operator*() {
        if (current == nullptr) throw std::out_of_range("attempt to read a value from a terminated iterator");
        return ((MutableNode*&)const_cast<Node*&>(current))->Element();
    }






    /********************************************** PREORDER BINARYTREEITERATOR ****************************************/

    template <typename Data> inline bool BTPreOrderIterator<Data>::operator==(const BTPreOrderIterator<Data>& other) const noexcept {
        return other.current == current;
    }

    template <typename Data> inline bool BTPreOrderIterator<Data>::operator!=(const BTPreOrderIterator<Data>& other) const noexcept {
        return other.current != current;
    }
    
    template <typename Data> BTPreOrderIterator<Data>::BTPreOrderIterator(const BinaryTree<Data>& tree) noexcept {
        suspended = lasd::StackVec<Node const*>();
        current = root = &(tree.Root());
    }

    template <typename Data> void BTPreOrderIterator<Data>::Reset() noexcept { 
        suspended.Clear();
        current = root; 
    }

    template <typename Data> ForwardIterator<Data>& BTPreOrderIterator<Data>::operator++() {
        if (current == nullptr) throw std::out_of_range("attempt to increment a terminated iterator");
        if (current->HasLeftChild()){
            if (current->HasRightChild()) suspended.Push(current);
            current = &(current->LeftChild());
        }
        else if (current->HasRightChild()) current = &(current->RightChild());
        else if (not suspended.Empty()) current = &(suspended.TopNPop()->RightChild());
        else current = nullptr;
        return *this;
    }






    /********************************************** POSTORDER BINARYTREEITERATOR ***************************************/

    template <typename Data> inline bool BTPostOrderIterator<Data>::operator==(const BTPostOrderIterator<Data>& other) const noexcept {
        return other.current == current;
    }

    template <typename Data> inline bool BTPostOrderIterator<Data>::operator!=(const BTPostOrderIterator<Data>& other) const noexcept {
        return other.current != current;
    }
    
    template <typename Data> BTPostOrderIterator<Data>::BTPostOrderIterator(const BinaryTree<Data>& tree) noexcept {
        return;
    }

    template <typename Data> void BTPostOrderIterator<Data>::Reset() noexcept {
        suspended.Clear();
        current = root;
    }

    template <typename Data> ForwardIterator<Data>& BTPostOrderIterator<Data>::operator++() {
        return *this;
    }





    /********************************************** INORDER BINARYTREEITERATOR ****************************************/

    template <typename Data> inline bool BTInOrderIterator<Data>::operator==(const BTInOrderIterator<Data>& other) const noexcept {
        return other.current == current;
    }

    template <typename Data> inline bool BTInOrderIterator<Data>::operator!=(const BTInOrderIterator<Data>& other) const noexcept {
        return other.current != current;
    }
    
    template <typename Data> BTInOrderIterator<Data>::BTInOrderIterator(const BinaryTree<Data>& tree) noexcept {
        return;
    }

    template <typename Data> void BTInOrderIterator<Data>::Reset() noexcept {
        suspended.Clear();
        current = root;
    }

    template <typename Data> ForwardIterator<Data>& BTInOrderIterator<Data>::operator++() {
        return *this;
    }





    /********************************************** BREADTH BINARYTREEITERATOR *************************************/

    template <typename Data> inline bool BTBreadthIterator<Data>::operator==(const BTBreadthIterator<Data>& other) const noexcept {
        return other.current == current;
    }

    template <typename Data> inline bool BTBreadthIterator<Data>::operator!=(const BTBreadthIterator<Data>& other) const noexcept {
        return other.current != current;
    }

    template <typename Data> BTBreadthIterator<Data>::BTBreadthIterator(const BinaryTree<Data>& tree) noexcept {
        suspended = lasd::QueueVec<Node const*>();
        current = root = &(tree.Root());
    }

    template <typename Data> void BTBreadthIterator<Data>::Reset() noexcept {
        suspended.Clear();
        current = root;
    }

    template <typename Data> ForwardIterator<Data>& BTBreadthIterator<Data>::operator++() {
        if (current == nullptr) throw std::out_of_range("attempt to increment a terminated iterator");
        if(current->HasLeftChild()) suspended.Enqueue(&(current->LeftChild()));
        if(current->HasRightChild()) suspended.Enqueue(&(current->RightChild()));
        current = (not suspended.Empty())? suspended.HeadNDequeue() : nullptr;
        return *this;
    }
}