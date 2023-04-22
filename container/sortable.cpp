
// FRANCESCO DE ROSA N86004379  

#pragma once

#include <stdexcept>
#include <cassert>

namespace lasd {

    template<typename Data> bool SortableLinearContainer<Data>::Sorted() const {
        for (int i = 1; i < size; i++) {
            if (operator[](i-1) > operator[](i)) return false;
        }
        return true;
    }


    template<typename Data> inline void SortableLinearContainer<Data>::Sort()      { QuickSort(0,size); }
    template<typename Data> inline void SortableLinearContainer<Data>::QuickSort() { QuickSort(0,size); }
    template<typename Data> inline void SortableLinearContainer<Data>::MergeSort() { MergeSort(0,size); }


    template<typename Data> void SortableLinearContainer<Data>::InsertionSort() {
        for (int current = 0; current < size; current++){
            for (int i = current; i > 0 and this->operator[](i) < this->operator[](i-1); i--){
                std::swap(operator[](i), operator[](i-1));
            }
        }
    }

    
    template<typename Data> void SortableLinearContainer<Data>::SelectionSort() {
        for (int current = 0; current < size; current++){
            for (int i = current; i < size; i++){
                if (operator[](i) < operator[](current)){
                    std::swap(operator[](i), operator[](current));
                }
            }
        }
    }


    template<typename Data> void SortableLinearContainer<Data>::QuickSort(sizetype begin, sizetype end){
        if (end - begin < 2) return;
        const Data& pivot = operator[](end-1);
        sizetype current_index = begin - 1;
        sizetype swap_marker = begin - 1;
       
        while (++current_index < end){
            if (operator[](current_index) <= pivot){
                if (current_index > ++swap_marker) {
                    std::swap(operator[](current_index), operator[](swap_marker));
                }
            }    
        }
        
        QuickSort(begin, swap_marker);
        QuickSort(swap_marker + 1, end);
    }


    template<typename Data> void SortableLinearContainer<Data>::MergeSort(sizetype begin, sizetype end){
        if (end - begin < 2) return;
        sizetype pivot = (begin + end)/2;
        MergeSort(begin, pivot);
        MergeSort(pivot, end);
        
        Data* tmp = new Data [end - begin];
        sizetype lx = begin;
        sizetype rx = pivot;
        sizetype kx = 0;

        while (lx < pivot and rx < end){
            tmp[kx++] = (operator[](lx) <= operator[](rx))? operator[](lx++) : operator[](rx++);
        }
        
        while (lx < pivot) tmp[kx++] = operator[](lx++);
        while (rx < end)   tmp[kx++] = operator[](rx++);
        while (kx-- > 0)   (*this)[kx + begin] = tmp[kx];
        delete [] tmp;
    }
}