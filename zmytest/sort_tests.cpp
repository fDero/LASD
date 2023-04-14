
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/foldable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"




void insertion_sort_t1(){
    lasd::Vector<int> vec = lasd::Vector<int>(10);
    vec[0] = 4; vec[1] = 7; vec[2] = 3; vec[3] = 4; vec[4] = 0;
    vec[5] = 9; vec[6] = 1; vec[7] = 1; vec[8] = 6; vec[9] = 6;
    expect(not vec.Sorted());
    vec.InsertionSort();
    expect(vec.Sorted());
}




void insertion_sort_t2(){
    lasd::Vector<int> vec = lasd::Vector<int>(10);
    vec[0] = 4; vec[1] = 9; vec[2] = 7; vec[3] = 4; vec[4] = 0;
    vec[5] = 9; vec[6] = 2; vec[7] = 7; vec[8] = 6; vec[9] = 7;
    expect(not vec.Sorted());
    vec.InsertionSort();
    expect(vec.Sorted());
}




void insertion_sort_t3(){
    lasd::Vector<int> vec = lasd::Vector<int>(5);
    vec[0] = 1; vec[1] = 2; vec[2] = 3; vec[3] = 4; vec[4] = 5;
    expect(vec.Sorted());
    vec.InsertionSort();
    expect(vec.Sorted());
}




void selection_sort_t1(){
    lasd::Vector<int> vec = lasd::Vector<int>(10);
    vec[0] = 4; vec[1] = 7; vec[2] = 3; vec[3] = 4; vec[4] = 0;
    vec[5] = 9; vec[6] = 1; vec[7] = 1; vec[8] = 6; vec[9] = 6;
    expect(not vec.Sorted());
    vec.SelectionSort();
    expect(vec.Sorted());
}




void selection_sort_t2(){
    lasd::Vector<int> vec = lasd::Vector<int>(10);
    vec[0] = 4; vec[1] = 9; vec[2] = 7; vec[3] = 4; vec[4] = 0;
    vec[5] = 9; vec[6] = 2; vec[7] = 7; vec[8] = 6; vec[9] = 7;
    expect(not vec.Sorted());
    vec.SelectionSort();
    expect(vec.Sorted());
}




void selection_sort_t3(){
    lasd::Vector<int> vec = lasd::Vector<int>(5);
    vec[0] = 1; vec[1] = 2; vec[2] = 3; vec[3] = 4; vec[4] = 5;
    expect(vec.Sorted());
    vec.SelectionSort();
    expect(vec.Sorted());
}




void quick_sort_t1(){
    lasd::Vector<int> vec = lasd::Vector<int>(10);
    vec[0] = 3; vec[1] = 2; vec[2] = 5; vec[3] = 0; vec[4] = 1;
    vec[5] = 8; vec[6] = 7; vec[7] = 6; vec[8] = 9; vec[9] = 4;
    expect(not vec.Sorted());
    vec.QuickSort();
    expect(vec.Sorted());
}




void quick_sort_t2(){
    lasd::Vector<int> vec = lasd::Vector<int>(10);
    vec[0] = 4; vec[1] = 9; vec[2] = 7; vec[3] = 4; vec[4] = 0;
    vec[5] = 9; vec[6] = 2; vec[7] = 7; vec[8] = 6; vec[9] = 7;
    expect(not vec.Sorted());
    vec.QuickSort();
    expect(vec.Sorted());
}




void quick_sort_t3(){
    lasd::Vector<int> vec = lasd::Vector<int>(5);
    vec[0] = 1; vec[1] = 2; vec[2] = 3; vec[3] = 4; vec[4] = 5;
    expect(vec.Sorted());
    vec.QuickSort();
    expect(vec.Sorted());
}



void merge_sort_t1(){
    lasd::Vector<int> vec = lasd::Vector<int>(6);
    vec[0] = 1; vec[1] = 4; vec[2] = 5;
    vec[3] = 0; vec[4] = 1; vec[5] = 9;
    expect(not vec.Sorted());
    vec.MergeSort();
    expect(vec.Sorted());
}



void merge_sort_t2(){
    lasd::Vector<int> vec = lasd::Vector<int>(10);
    vec[0] = 3; vec[1] = 2; vec[2] = 5; vec[3] = 0; vec[4] = 1;
    vec[5] = 8; vec[6] = 7; vec[7] = 6; vec[8] = 9; vec[9] = 4;
    expect(not vec.Sorted());
    vec.MergeSort();
    expect(vec.Sorted());
}




void merge_sort_t3(){
    lasd::Vector<int> vec = lasd::Vector<int>(10);
    vec[0] = 4; vec[1] = 9; vec[2] = 7; vec[3] = 4; vec[4] = 0;
    vec[5] = 9; vec[6] = 2; vec[7] = 7; vec[8] = 6; vec[9] = 7;
    expect(not vec.Sorted());
    vec.MergeSort();
    expect(vec.Sorted());
}




void merge_sort_t4(){
    lasd::Vector<int> vec = lasd::Vector<int>(5);
    vec[0] = 1; vec[1] = 2; vec[2] = 3; vec[3] = 4; vec[4] = 5;
    expect(vec.Sorted());
    vec.MergeSort();
    expect(vec.Sorted());
}



void execute_sort_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::SortableContainer<T> ↓↓↓ \n");
    UnitTest sort_test_procedures {
       {"insertion_sort_t1",           insertion_sort_t1},
       {"insertion_sort_t2",           insertion_sort_t2},
       {"insertion_sort_t3",           insertion_sort_t3},
       {"selection_sort_t1",           selection_sort_t1},
       {"selection_sort_t2",           selection_sort_t2},
       {"selection_sort_t3",           selection_sort_t3},
       {"quick_sort_t1",               quick_sort_t1},
       {"quick_sort_t2",               quick_sort_t2},
       {"quick_sort_t3",               quick_sort_t3},
       {"merge_sort_t1",               merge_sort_t1},
       {"merge_sort_t2",               merge_sort_t2},
       {"merge_sort_t3",               merge_sort_t3},
       {"merge_sort_t4",               merge_sort_t4},

    };
    execute_tests(sort_test_procedures);  
}