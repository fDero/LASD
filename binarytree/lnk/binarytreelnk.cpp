
// FRANCESCO DE ROSA N86004379

#pragma once

#include "binarytreelnk.hpp"
#include "../../queue/vec/queuevec.hpp"
#include "../../container/mappable.hpp"
#include <cassert>

namespace lasd {

    /************************************************* NODELNK **********************************************/

    template <typename Data> BinaryTreeLnk<Data>::NodeLnk::NodeLnk(const Data& elem) noexcept { value = elem; }
    template <typename Data> BinaryTreeLnk<Data>::NodeLnk::NodeLnk(Data&& elem) noexcept { value = std::move(elem); }
    template <typename Data> BinaryTreeLnk<Data>::NodeLnk::~NodeLnk() noexcept { delete left; delete right; }

    template <typename Data> const Data& BinaryTreeLnk<Data>::NodeLnk::Element() const noexcept { return value; }
    template <typename Data> Data& BinaryTreeLnk<Data>::NodeLnk::Element() noexcept { return value; }

    template <typename Data> const BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::RightChild() const { 
        if (right != nullptr) return *right;
        throw std::length_error("illegal requeste for a non-present node's right child");
    }

    template <typename Data> const BinaryTree<Data>::Node& BinaryTreeLnk<Data>::NodeLnk::LeftChild() const { 
        if (left != nullptr) return *left;
        throw std::length_error("illegal requeste for a non-present node's left child");
    }

    template <typename Data> MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::RightChild() { 
        if (right != nullptr) return *right;
        throw std::length_error("illegal requeste for a non-present node's right child");
    }

    template <typename Data> MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::NodeLnk::LeftChild() { 
        if (left != nullptr) return *left;
        throw std::length_error("illegal requeste for a non-present node's left child");
    }

    template <typename Data> const BinaryTree<Data>::Node& BinaryTreeLnk<Data>::Root() const { 
        if (root == nullptr or size == 0) throw std::length_error("attempt to get the root from an empty tree");
        return *root; 
    }

    template <typename Data> MutableBinaryTree<Data>::MutableNode& BinaryTreeLnk<Data>::Root() { 
        if (root == nullptr or size == 0) throw std::length_error("attempt to get the root from an empty tree");
        return *root; 
    }




    /********************************************** CONSTRUCTORS *********************************************/

    template <typename Data> BinaryTreeLnk<Data>::BinaryTreeLnk(const MappableContainer<Data>& source) noexcept {
        QueueVec<NodeLnk*> nodes;
        source.Map([&nodes, this](const Data& value){ this->BuildFromMappable<const Data&>(value, nodes); });
        size = source.Size(); 
    }

    template <typename Data> BinaryTreeLnk<Data>::BinaryTreeLnk(MutableMappableContainer<Data>&& source) noexcept {
        QueueVec<NodeLnk*> nodes;
        source.Map([&nodes, this](Data& value){ this->BuildFromMappable<Data&&>(std::move(value), nodes); });
        size = source.Size(); 
    }

    template <typename Data> BinaryTreeLnk<Data>::BinaryTreeLnk(const BinaryTreeLnk<Data>& other) noexcept {
        this->operator=(other);
    }

    
    template <typename Data> BinaryTreeLnk<Data>::BinaryTreeLnk(BinaryTreeLnk<Data>&& other) noexcept {
        this->operator=(std::move(other));
    }

        template<typename Data> BinaryTreeLnk<Data>::~BinaryTreeLnk() noexcept {
        delete root;
    }





    /****************************************************** OVERRIDES ****************************************/

    template<typename Data> void BinaryTreeLnk<Data>::Clear() {
        delete root;
        root = nullptr;
        size = 0;
    }




    /***************************************************** ASSIGNMENTS ***************************************/

    template<typename Data> BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(const BinaryTreeLnk<Data>& other) noexcept {
        ReplaceSubtree(root,other.root);
        size = other.size;
        return *this;
    }

    template<typename Data> BinaryTreeLnk<Data>& BinaryTreeLnk<Data>::operator=(BinaryTreeLnk<Data>&& other) noexcept {
        std::swap(root, other.root);
        std::swap(size, other.size);
        return *this;
    }




    /****************************************************** COMPARISON ******************************************/

    template<typename Data> inline bool BinaryTreeLnk<Data>::operator==(const BinaryTreeLnk<Data>& other) const noexcept {
        return BinaryTree<Data>::operator==(other);
    }

    template<typename Data> inline bool BinaryTreeLnk<Data>::operator!=(const BinaryTreeLnk<Data>& other) const noexcept {
        return BinaryTree<Data>::operator==(other);
    }




    /******************************************** PRIVATE HELPER FUNCTIONS *********************************************/
    
    template<typename Data> template <typename InputType>
    void BinaryTreeLnk<Data>::BuildFromMappable(InputType&& value, QueueVec<NodeLnk*>& nodes) noexcept {    
        if (nodes.Empty()) { 
            assert (root == nullptr);
            root = new NodeLnk{ std::forward<InputType>(value) }; 
            nodes.Enqueue(root); 
            assert (root != nullptr);
        }
        else if (nodes.Head()->IsLeaf()) {
            assert (nodes.Head()->left == nullptr);
            assert (nodes.Head()->right == nullptr);
            nodes.Head()->left = new NodeLnk{ std::forward<InputType>(value) };
            nodes.Enqueue(nodes.Head()->left);
        } 
        else {
            assert (nodes.Head()->right == nullptr);
            nodes.Head()->right = new NodeLnk{ std::forward<InputType>(value) };
            nodes.Enqueue(nodes.Head()->right);
            nodes.Dequeue();
        }
    }

    template<typename Data> BinaryTreeLnk<Data>::NodeLnk* BinaryTreeLnk<Data>::CloneSubtree(NodeLnk* node){
        if (node == nullptr) return nullptr;
        NodeLnk* out = new NodeLnk{ node->value };
        out->left = CloneSubtree(node->left);
        out->right = CloneSubtree(node->right);
        return out;
    } 

    template<typename Data> void BinaryTreeLnk<Data>::ReplaceSubtree(NodeLnk*& oldtree, NodeLnk* newtree){
        if (oldtree == nullptr) oldtree = CloneSubtree(newtree);
        else if (newtree != nullptr) { 
            oldtree->value = newtree->value;
            ReplaceSubtree(oldtree->left, newtree->left);
            ReplaceSubtree(oldtree->right, newtree->right);
        } else {
            delete oldtree;
            oldtree = nullptr;
        }
    }    
}
