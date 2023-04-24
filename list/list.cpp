
// FRANCESCO DE ROSA N86004379

#pragma once

#include "list.hpp"
#include "../container/container.hpp"
#include "../container/mappable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"
#include <cassert>

namespace lasd {

    /********************************* CONSTRUCTORS AND DESTRUCTORS *******************************/
    // in order to satisfy at best the DRY policy (don't repeat yourself) constructors and desctructors
    // are just calls to existing methods/operators. This way the possible places in wich an error 
    // might occur are limited to those methods. In particular since clearing the list and destroyng
    // the list, both requires the deallocation of every node, a method "Dealloc" wich deallocates 
    // every node has been provided and is called in both the destructor and the Clear method

    template<typename Data> List<Data>::List(const List& list){ operator=(list); }

    template<typename Data> List<Data>::List(List&& list){ operator=(std::move(list)); }

    template<typename Data> List<Data>::~List(){ Dealloc(); }

    template<typename Data> List<Data>::List(MutableMappableContainer<Data>&& container){
        container.Map([this](Data& value){ this->InsertAtBack(std::move(value)); });
    }

    template<typename Data> List<Data>::List(const MappableContainer<Data>& container){
        container.Map([this](const Data& value){ this->InsertAtBack(value); });
    }
    
    template<typename Data> void List<Data>::Dealloc(){
        for (Node* it = head; it != nullptr; it = it->next) delete it->prev;  
        delete tail;
    }

    template<typename Data> void List<Data>::Clear(){
        Dealloc();
        size = 0;
        head = nullptr;
        tail = nullptr;
    }



    /************************************ ASSIGNMENT OPERATORS *********************************/
    // note that the copy-assignment operator does its best to avoid useless allocation by 
    // not deallocating existing nodes and instead uses them to provide a place to put the new values

    template<typename Data> List<Data>& List<Data>::operator=(const List<Data>& list) {
        Node* it = head;
        Node* src = list.head;
        while (it != nullptr and src != nullptr){
            it->value = src->value;
            it = it->next;
            src = src->next;
        }
        while (src == nullptr and (size - list.Size()) != 0) RemoveFromBack();
        while (src != nullptr and (size - list.Size()) != 0) { InsertAtBack(src->value); src = src->next; }
        return *this;
    }

    template<typename Data> List<Data>& List<Data>::operator=(List<Data>&& list) {
        std::swap(head, list.head);
        std::swap(tail, list.tail);
        std::swap(size, list.size);
        return *this;
    }




    /*********************************** COMPARISON OPERATORS ********************************/

    template<typename Data> bool List<Data>::operator==(const List<Data>& list) const {
        if (size != list.size) return false;
        Node* at = head; 
        Node* bt = list.head;
        while (at != nullptr and bt != nullptr) {
            if (at->value != bt->value) return false;
            at = at->next;
            bt = bt->next;
        } 
        assert (at == nullptr and bt == nullptr);
        return true;
    }

    template<typename Data> bool inline List<Data>::operator!=(const List<Data>& list) const { 
        return not (this->operator==(list));
    }


    

    /********************************** INSERTIONS AND DELETIONS *****************************/
    // since insertion an deletion are very similar either by copy or by rvalue-reference, the 
    // piece of code that is reapeted has been factored out in "EmplaceAtBack" and "EmplaceAtFront"

    template<typename Data> void List<Data>::EmplaceAtBack(Node* node){
        node->prev = tail;
        if (tail != nullptr) tail->next = node; 
        else head = node;
        tail = node;
        size++;
    }

    template<typename Data> void List<Data>::EmplaceAtFront(Node* node){
        node->next = head;
        if (tail != nullptr) head->prev = node; 
        else tail = node;
        head = node;
        size++;
    }

    template<typename Data> void List<Data>::InsertAtBack(const Data& value){ 
        Node* node = new Node(value);
        EmplaceAtBack(node);
    }

    template<typename Data> void List<Data>::InsertAtBack(Data&& value){ 
        Node* node = new Node(std::move(value));
        EmplaceAtBack(node);
    }

    template<typename Data> void List<Data>::InsertAtFront(const Data& value){ 
        Node* node = new Node(value);
        EmplaceAtFront(node);
    }
    
    template<typename Data> void List<Data>::InsertAtFront(Data&& value){ 
        Node* node = new Node(std::move(value));
        EmplaceAtFront(node);
    }

    template <typename Data> bool List<Data>::Insert(const Data& value){
        if (Exists(value)) return false;
        InsertAtBack(value);
        return true;
    }

    template <typename Data> bool List<Data>::Insert(Data&& value){
        if (Exists(value)) return false;
        InsertAtBack(std::move(value));
        return true;
    }

    template <typename Data> bool List<Data>::Remove(const Data& value){
        bool flag = (size != 0 and (this->Front() == value or this->Back() == value));

        while (size != 0 and this->Front() == value) this->RemoveFromFront(); 
        while (size != 0 and this->Back() == value)  this->RemoveFromBack();
        
        for (Node* it = head; it != nullptr; it = it->next) 
            if (it->value == value) {
                it->prev->next = it->next;
                it->next->prev = it->prev; 
                Node* dead = it;
                it = it->prev;
                delete dead;
                size--;
                flag = true;
            }
        return flag;
    }

    template <typename Data> void List<Data>::RemoveFromFront(){
        if (size == 0) throw std::length_error("RemoveFromFront() method invoked on empty list");
        if (size == 1) return Clear();
        head = head->next;
        delete head->prev;
        head->prev = nullptr;
        size--;   
    }

    template <typename Data> void List<Data>::RemoveFromBack(){
        if (size == 0) throw std::length_error("RemoveFromBack() method invoked on empty list");
        if (size == 1) return Clear();
        tail = tail->prev;
        delete tail->next;
        tail->next = nullptr;
        size--;   
    }

    template <typename Data> Data List<Data>::FrontNRemove(){
        if (size == 0) throw std::length_error("FrontNRemove() method invoked on empty list");
        Data tmp = std::move(head->value);
        RemoveFromFront();
        return tmp;   
    }

    template <typename Data> Data List<Data>::BackNRemove(){
        if (size == 0) throw std::length_error("BackNRemove() method invoked on empty list");
        Data tmp = std::move(tail->value);
        RemoveFromBack();
        return tmp;
    }



    /****************************** DATA ACCESS METHODS/OPERATORS **************************/

    template<typename Data> const Data& List<Data>::operator[](sizetype index) const {
        if (index >= size) throw std::out_of_range("index exceeds the current size");
        sizetype counter = 0;
        for (Node* it = head; it != nullptr; it = it->next, counter++)
            if (counter == index) return it->value;
        throw std::out_of_range("index exceeds the current size");
    }

    template<typename Data> Data& List<Data>::operator[](sizetype index) {
        if (index >= size) throw std::out_of_range("index exceeds the current size");
        sizetype counter = 0;
        for (Node* it = head; it != nullptr; it = it->next, counter++)
            if (counter == index) return it->value;
        throw std::out_of_range("index exceeds the current size");
    }

    template<typename Data> const Data& List<Data>::Front() const {
        if (size == 0) throw std::length_error("Front() method invoked on an empty container");
        return head->value;
    }

    template<typename Data> Data& List<Data>::Front() {
        if (size == 0) throw std::length_error("Front() method invoked on an empty container");
        return head->value;
    }

    
    template<typename Data> const Data& List<Data>::Back() const {
        if (size == 0) throw std::length_error("Back() method invoked on an empty container");
        return tail->value;
    }

    template<typename Data> Data& List<Data>::Back() {
        if (size == 0) throw std::length_error("Back() method invoked on an empty container");
        return tail->value;
    }

    template<typename Data> bool List<Data>::Exists(const Data& target) const noexcept {
        for (Node* it = head; it != nullptr; it = it->next) 
            if(it->value == target) 
                return true;
        return false;
    }


    /*************************************** MAPS *******************************************/
    // note that the const version are implicitly derived from PreOrderMappableContainer and 
    // PostOrderMappableContainer, and are both defined in "mappable.cpp"

    template<typename Data> void List<Data>::PreOrderMap(MutableMapFunctor functor) {
        for (Node* it = head; it != nullptr; it = it->next) functor(it->value);
    }

    template<typename Data> void List<Data>::PostOrderMap(MutableMapFunctor functor) {
        for (Node* it = tail; it != nullptr; it = it->prev) functor(it->value);
    }
}