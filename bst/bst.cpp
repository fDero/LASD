
// FRANCESCO DE ROSA N86004379

#pragma once

#include "../container/mappable.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "bst.hpp"
#include <cassert>

namespace lasd {

    /************************************************* CONSTRUCTORS ***************************************/

    template <typename Data> BST<Data>::BST(const BST& other) noexcept : BinaryTreeLnk<Data>(other) {}
    template <typename Data> BST<Data>::BST(BST&& other) noexcept : BinaryTreeLnk<Data>(std::move(other)) {}
    
    template <typename Data> BST<Data>::BST(const MappableContainer<Data>& source) noexcept {
        source.Map([this](const Data& value){ this->Insert(value); });
    }
    
    template <typename Data> BST<Data>::BST(MutableMappableContainer<Data>&& source) noexcept {
        source.Map([this](Data& value){ this->Insert(std::move(value)); });
    }
    



    /************************************************** ASSIGNMENTS ****************************************/

    template<typename Data> BST<Data>& BST<Data>::operator=(const BST<Data>& other) noexcept {
        BinaryTreeLnk<Data>::operator=(other);
        return *this;
    } 

    template<typename Data> BST<Data>& BST<Data>::operator=(BST<Data>&& other) noexcept {
        BinaryTreeLnk<Data>::operator=(std::move(other));
        return *this;
    } 




    /************************************************** COMPARISON ****************************************/

    template <typename Data> inline bool BST<Data>::operator==(const BST<Data>& other) const noexcept { 
        if (size != other.size) return false;
        if (size == 0) return true;
        BTInOrderIterator thisit (*this);
        BTInOrderIterator thatit (other);
        for (sizetype i = 0; i < size; i++){
            if (*thisit != *thatit) return false;
            ++thisit;
            ++thatit;
        }
        return true;
    }
    
    template <typename Data> inline bool BST<Data>::operator!=(const BST<Data>& other) const noexcept { 
        return not operator==(other);
    }   
    




    /******************************************** INSERTIONS / DELETIONS *********************************/

    template <typename Data> inline bool BST<Data>::Insert(const Data& value) noexcept { return InsertHelper(value); }
    template <typename Data> inline bool BST<Data>::Insert(Data&& value) noexcept { return InsertHelper(std::move(value)); }

    template<typename Data> template<typename Value> bool BST<Data>::InsertHelper(Value&& value){
        NodeLnk*& target = FindNodePointer(value, root);
        if (target == nullptr) {
            size++;
            target = new NodeLnk(std::forward<Value>(value));
            return true;    
        }
        return false;
    }

    template<typename Data> bool BST<Data>::Remove(const Data& value) noexcept {
        NodeLnk*& target = FindNodePointer(value, root);
        if (target == nullptr) return false;
        Detach(target);
        return true;
    }

    template<typename Data> void BST<Data>::Detach(NodeLnk*& target) {
        if (target->right != nullptr and target->right->left == nullptr){
            NodeLnk* dead = target;
            target->right->left = target->left;
            target = target->right;
            DeleteJustThisNode(dead);
        }
        else if (target->left != nullptr and target->left->right == nullptr){
            NodeLnk* dead = target;
            target->left->right = target->right;
            target = target->left;
            DeleteJustThisNode(dead);
        }
        else if (target->right != nullptr) {
            NodeLnk*& replacement = FindMinInSubtree(target->right);
            std::swap(replacement->value, target->value);
            NodeLnk* dead = replacement;
            replacement = replacement->right;
            DeleteJustThisNode(dead);
        } 
        else if (target->left != nullptr) {
            NodeLnk*& replacement = FindMaxInSubtree(target->left);
            std::swap(replacement->value, target->value);
            NodeLnk* dead = replacement;
            replacement = replacement->left;
            DeleteJustThisNode(dead);
        }
        else {
            delete target;
            target = nullptr;
        }
        size--;
    }

    template<typename Data> void BST<Data>::DeleteJustThisNode(NodeLnk*& node){
        node->left = nullptr;
        node->right = nullptr;
        delete node;
    }
    



    /******************************************* MIN / MAX SEARCH ***********************************/

    template<typename Data> BST<Data>::NodeLnk*& BST<Data>::FindMinInSubtree(NodeLnk*& subroot){
        if (subroot == nullptr or subroot->left == nullptr) return subroot; 
        return FindMinInSubtree(subroot->left);
    }

    template<typename Data> BST<Data>::NodeLnk*& BST<Data>::FindMaxInSubtree(NodeLnk*& subroot){
        if (subroot == nullptr or subroot->right == nullptr) return subroot; 
        return FindMaxInSubtree(subroot->right);
    }

    template<typename Data> const Data& BST<Data>::Min() const {
        if (size == 0) throw std::length_error("attempt to get minimum from empty tree");
        auto* const_casted = const_cast<BST<Data>*>(this);
        return const_casted->FindMinInSubtree(const_casted->root)->value;
    }

    template<typename Data> const Data& BST<Data>::Max() const {
        if (size == 0) throw std::length_error("attempt to get the maximum value from an empty tree");
        auto* const_casted = const_cast<BST<Data>*>(this);
        return const_casted->FindMaxInSubtree(const_casted->root)->value;
    }

    template<typename Data> void BST<Data>::RemoveMax() {
        if (size == 0) throw std::length_error("attempt to get the maximum value from an empty tree");
        NodeLnk*& max = FindMaxInSubtree(root);
        Detach(max);
    }

    template<typename Data> void BST<Data>::RemoveMin() {
        if (size == 0) throw std::length_error("attempt to get the maximum value from an empty tree");
        NodeLnk*& min = FindMinInSubtree(root);
        Detach(min);
    }

    template<typename Data> Data BST<Data>::MinNRemove() {
        if (size == 0) throw std::length_error("attempt to get the maximum value from an empty tree");
        NodeLnk*& min = FindMinInSubtree(root);
        Data value = std::move(min->value);
        Detach(min);
        return value;
    }

    template<typename Data> Data BST<Data>::MaxNRemove() {
        if (size == 0) throw std::length_error("attempt to get the maximum value from an empty tree");
        NodeLnk*& max = FindMaxInSubtree(root);
        Data value = std::move(max->value);
        Detach(max);
        return value;
    }




    /************************************* SPECIFIC VALUE / NODE SEARCH *****************************/

    template<typename Data> BST<Data>::NodeLnk*& BST<Data>::FindNodePointer(const Data& value, NodeLnk*& ptr) {
        if (ptr == nullptr)      return ptr;
        if (value > ptr->value)  return FindNodePointer(value, ptr->right);
        if (value < ptr->value)  return FindNodePointer(value, ptr->left);
        return ptr;
    }

    template<typename Data> BST<Data>::NodeLnk*& BST<Data>::FindPredecessorPointer(const Data& value, NodeLnk*& ptr) {
        if (ptr == nullptr) return ptr;
        if (value > ptr->value) {
            NodeLnk*& x = FindPredecessorPointer(value, ptr->right);
            return (x == nullptr or x->value >= value)? ptr : x;
        }
        if (value < ptr->value) {
            NodeLnk*& x = FindPredecessorPointer(value, ptr->left);
            return (x == nullptr)? ptr : x;
        }
        if (ptr->left != nullptr) return FindMaxInSubtree(ptr->left);
        return ptr;
    }

    template<typename Data> BST<Data>::NodeLnk*& BST<Data>::FindSuccessorPointer(const Data& value, NodeLnk*& ptr) {
        if (ptr == nullptr) return ptr;
        if (value > ptr->value) {
            NodeLnk*& x = FindSuccessorPointer(value, ptr->right);
            return (x == nullptr)? ptr : x;
        }
        if (value < ptr->value) {
            NodeLnk*& x = FindSuccessorPointer(value, ptr->left);
            return (x == nullptr or x->value <= value)? ptr : x;
        }
        if (ptr->right != nullptr) return FindMinInSubtree(ptr->right);
        return ptr;
    }

    template<typename Data> inline bool BST<Data>::Exists(const Data& value) const noexcept {
        auto* const_casted = const_cast<BST<Data>*>(this);
        return (const_casted->FindNodePointer(value, const_casted->root) != nullptr);
    }

    template<typename Data> const Data& BST<Data>::Successor(const Data& value) const { 
        auto* const_casted = const_cast<BST<Data>*>(this);
        auto succ = const_casted->FindSuccessorPointer(value, const_casted->root);
        if (succ == nullptr or succ->value <= value) throw std::length_error("attempt to get successor failed");
        return succ->value;
    }

    template<typename Data> const Data& BST<Data>::Predecessor(const Data& value) const {
        auto* const_casted = const_cast<BST<Data>*>(this);
        auto pred = const_casted->FindPredecessorPointer(value, const_casted->root);
        if (pred == nullptr or pred->value >= value) throw std::length_error("attempt to get predecessor failed");
        return pred->value;
    }

    template<typename Data> void BST<Data>::RemoveSuccessor(const Data& value) { 
        auto* const_casted = const_cast<BST<Data>*>(this);
        NodeLnk*& succ = const_casted->FindSuccessorPointer(value, const_casted->root);
        if (succ == nullptr or succ->value <= value) throw std::length_error("attempt to remove successor failed");
        Detach(succ);
    }

    template<typename Data> void BST<Data>::RemovePredecessor(const Data& value) {
        auto* const_casted = const_cast<BST<Data>*>(this);
        NodeLnk*& pred = const_casted->FindPredecessorPointer(value, const_casted->root);
        if (pred == nullptr or pred->value >= value) throw std::length_error("attempt to remove predecessor failed");
        Detach(pred);
    }

    
    template<typename Data> Data BST<Data>::SuccessorNRemove(const Data& value) { 
        auto* const_casted = const_cast<BST<Data>*>(this);
        NodeLnk*& succ = const_casted->FindSuccessorPointer(value, const_casted->root);
        if (succ == nullptr or succ->value <= value) throw std::length_error("attempt to remove successor failed");
        Data succvalue = std::move(succ->value);
        Detach(succ);
        return succvalue;
    }

    template<typename Data> Data BST<Data>::PredecessorNRemove(const Data& value) {
        auto* const_casted = const_cast<BST<Data>*>(this);
        NodeLnk*& pred = const_casted->FindPredecessorPointer(value, const_casted->root);
        if (pred == nullptr or pred->value >= value) throw std::length_error("attempt to remove predecessor failed");
        Data predvalue = std::move(pred->value);
        Detach(pred);
        return predvalue;
    }
}