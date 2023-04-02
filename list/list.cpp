
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

    template<typename Data> void List<Data>::InsertAtFront(const Data& value){ 
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
        for (Node* it = list.head; it != nullptr; it = it->next) this->InsertAtBack(it->value);
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

    template<typename Data> void List<Data>::PreOrderMap(MapFunctor functor) const { 
        for (Node* it = head; it != nullptr; it = it->next) functor(it->value); 
    }
    
    template<typename Data> void List<Data>::PostOrderMap(MapFunctor functor) const { 
        for (Node* it = tail; it != nullptr; it = it->prev) functor(it->value); 
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
}
