
// FRANCESCO DE ROSA N86004379

#pragma once

#include "list.hpp"
#include "../container/container.hpp"
#include "../container/mappable.hpp"
#include "../container/dictionary.hpp"
#include "../container/linear.hpp"

namespace lasd {

    template<typename Data> List<Data>::List(const List& list){
        this->operator=(list);
    }

    template<typename Data> List<Data>::List(List&& list){
        this->operator=(list);
    }

    template<typename Data> List<Data>::~List(){
        this->Clear();
    }

    template<typename Data> List<Data>::List(const MutableMappableContainer<Data>& container){
        container.Map([this](Data& value){ this->InsertAtBack(value); });
    }

    
    template<typename Data> List<Data>::List(const MappableContainer<Data>& container){
        container.Map([this](const Data& value){ this->InsertAtBack(value); });
    }

    template<typename Data> void List<Data>::InsertAtBack(const Data& value){ 
        Node* node = new Node(value);
        node->prev = tail;
        if (tail != nullptr) tail->next = node; 
        else head = node;
        tail = node;
        size++;
    }

    template<typename Data> void List<Data>::InsertAtBack(Data&& value){ 
        Node* node = new Node(value);
        node->prev = tail;
        if (tail != nullptr) tail->next = node; 
        else head = node;
        tail = node;
        size++;
    }

    template<typename Data> void List<Data>::InsertAtFront(const Data& value){ 
        Node* node = new Node(value);
        node->next = head;
        if (tail != nullptr) head->prev = node; 
        else tail = node;
        head = node;
        size++;
    }

    
    template<typename Data> void List<Data>::InsertAtFront(Data&& value){ 
        Node* node = new Node(value);
        node->next = head;
        if (tail != nullptr) head->prev = node; 
        else tail = node;
        head = node;
        size++;
    }

    template<typename Data> bool List<Data>::operator==(const List<Data>& list) const {
        if (size != list.size) return false;
        Node* at = head; 
        Node* bt = list.head;
        while (at != nullptr and bt != nullptr) {
            if (at->value != bt->value) return false;
            at = at->next;
            bt = bt->next;
        } 
        return (at == nullptr) and (bt == nullptr);
    }

    template<typename Data> bool List<Data>::operator!=(const List<Data>& list) const { 
        return not (this->operator==(list));
    }

    template<typename Data> List<Data>& List<Data>::operator=(const List<Data>& list) {
        Clear();
        list.Map([this](const Data& value){ this->InsertAtBack(value); });
    }

    template<typename Data> List<Data>& List<Data>::operator=(List<Data>&& list) {
        head = list.head;
        tail = list.tail;
        size = list.size; 
        list.head = nullptr;
        list.tail = nullptr;
    }

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

    template<typename Data> void List<Data>::Clear(){
        for (Node* it = head; it != nullptr; it = it->next) delete it->prev;  
        delete tail;
        size = 0;
        head = nullptr;
        tail = nullptr;
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

    template<typename Data> void List<Data>::PreOrderMap(MutableMapFunctor functor) {
        for (Node* it = head; it != nullptr; it = it->next) functor(it->value);
    }

    template<typename Data> void List<Data>::PostOrderMap(MutableMapFunctor functor) {
        for (Node* it = tail; it != nullptr; it = it->prev) functor(it->value);
    }


    template<typename Data> bool List<Data>::Exists(const Data& target) const noexcept {
        for (Node* it = head; it != nullptr; it = it->next) 
            if(it->value == target) return true;
        return false;
    }

    template <typename Data> bool List<Data>::Insert(const Data& value){
        for (Node* it = head; it != nullptr; it = it->next) 
            if (it->value == value) 
                return false;
        InsertAtBack(value);
        return true;
    }

    template <typename Data> bool List<Data>::Insert(Data&& value){
        for (Node* it = head; it != nullptr; it = it->next) 
            if (it->value == value) 
                return false;
        InsertAtBack(value);
        return true;
    }

    template <typename Data> bool List<Data>::Remove(const Data& value){
        for (Node* it = head; it != nullptr; it = it->next) 
            if (it->value == value) {
                if (it->prev != nullptr) it->prev->next = it->next;
                if (it->next != nullptr) it->next->prev = it->prev;
                delete it;
                size--;
                return true; 
            }
        return false;
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
}
