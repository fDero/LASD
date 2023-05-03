
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"
#include "../bst/bst.hpp"



void empty_bst_allocation(){
    auto empty_bst = lasd::BST<int>();
    expect(empty_bst.Empty());
    expect(empty_bst.Size() == 0);
}



void bst_insertions_t1(){
    auto bst = lasd::BST<int>();
    bst.Insert(6);
    bst.Insert(4);
    bst.Insert(8);
    expect(not bst.Empty());
    expect(bst.Size() == 3);
}



void bst_insertions_t2(){
    auto bst = lasd::BST<int>();
    bst.Insert(6);
    bst.Insert(4);
    bst.Insert(8);
    
    expect(bst.Root().Element() == 6);
    expect(bst.Root().LeftChild().Element() == 4);
    expect(bst.Root().RightChild().Element() == 8);
}




void bst_insertions_t3(){
    auto bst = lasd::BST<int>();
    bst.Insert(4);
    bst.Insert(2);
    bst.Insert(6);
    bst.Insert(1);
    bst.Insert(3);
    bst.Insert(5);
    bst.Insert(7);
    
    expect(bst.Root().Element() == 4);
    expect(bst.Root().LeftChild().Element() == 2);
    expect(bst.Root().RightChild().Element() == 6);

    expect(bst.Root().LeftChild().LeftChild().Element() == 1);
    expect(bst.Root().LeftChild().RightChild().Element() == 3);

    expect(bst.Root().RightChild().LeftChild().Element() == 5);
    expect(bst.Root().RightChild().RightChild().Element() == 7);
}




void bst_deletions_t1(){
    auto bst = lasd::BST<int>();
    bst.Insert(4);
    bst.Insert(2);
    bst.Insert(6);
    bst.Insert(1);
    bst.Insert(3);
    bst.Insert(5);
    bst.Insert(7);
    expect(bst.Remove(2));
    expect(bst.Root().Element() == 4);
    expect(bst.Root().LeftChild().Element() == 3);
}




void bst_deletions_t2(){
    auto bst = lasd::BST<int>();
    bst.Insert(4);
    bst.Insert(2);
    bst.Insert(6);
    bst.Insert(1);
    bst.Insert(3);
    bst.Insert(5);
    bst.Insert(7);
    expect(bst.Remove(4));
    expect(bst.Root().Element() == 5);
    expect(bst.Root().LeftChild().Element() == 2);
}




void bst_deletions_t3(){
    auto bst = lasd::BST<int>();
    bst.Insert(4);
    bst.Insert(2);
    bst.Insert(6);
    bst.Insert(1);
    bst.Insert(3);
    bst.Insert(5);
    bst.Insert(7);
    expect(bst.Remove(1));
    expect(bst.Root().Element() == 4);
    expect(bst.Root().LeftChild().Element() == 2);
}




void bst_deletions_t4(){
    auto bst = lasd::BST<int>();
    bst.Insert(4);
    expect(bst.Remove(4));
}




void bst_deletions_t5(){
    auto bst = lasd::BST<int>();
    bst.Insert(4);
    bst.Insert(3);
    bst.Insert(2);
    expect(bst.Remove(3));
    expect(bst.Root().Element() == 4);
    expect(bst.Root().LeftChild().Element() == 2);
}




void bst_deletions_t6(){
    auto bst = lasd::BST<int>();
    bst.Insert(4);
    bst.Insert(3);
    bst.Insert(2);
    expect(bst.Remove(3));
    expect(bst.Root().Element() == 4);
    expect(bst.Root().LeftChild().Element() == 2);
    expect(bst.Remove(4));
    expect(bst.Root().Element() == 2);
    expect(bst.Remove(2));
}




void bst_min_max_exists(){
    auto bst = lasd::BST<int>();
    bst.Insert(8);
    bst.Insert(9);
    bst.Insert(3);
    bst.Insert(0);
    bst.Insert(6);
    bst.Insert(4);
    expect(bst.Min() == 0);
    expect(bst.Max() == 9);
    expect(bst.Exists(4));
    expect(not bst.Exists(5));
}




void predecessors_t1(){
    auto bst = lasd::BST<int>();
    bst.Insert(8);
    bst.Insert(9);
    bst.Insert(3);
    bst.Insert(0);
    bst.Insert(6);
    bst.Insert(4);
    expect(bst.Predecessor(5) == 4);
    expect(bst.Predecessor(4) == 3);
    expect(bst.Predecessor(3) == 0);
    expect(bst.Predecessor(9) == 8);
}




void predecessors_t2(){
    auto bst = lasd::BST<int>();
    bst.Insert(7);
    bst.Insert(8);   
    expect(bst.Predecessor(8) == 7);
}





void predecessors_t3(){
    auto bst = lasd::BST<int>();
    bst.Insert(7);
    bst.Insert(8);
    bst.Insert(9);   
    expect(bst.Predecessor(8) == 7);
    expect(bst.Predecessor(9) == 8);
}



void predecessors_t4(){
    auto bst = lasd::BST<int>();
    bst.Insert(100);
    bst.Insert(50);
    bst.Insert(75);
    bst.Insert(65);   
    expect(bst.Predecessor(75) == 65);
}





void predecessors_t5(){
    expect_exception<std::length_error>([](){
        auto bst = lasd::BST<int>();
        bst.Insert(7);
        bst.Insert(6);
        bst.Insert(5);   
        bst.Predecessor(5);    
    });
}




void predecessors_t6(){
    auto bst = lasd::BST<int>();
    bst.Insert(7);
    bst.Insert(6);
    bst.Insert(5);
    bst.Insert(4);
    bst.Insert(3);
    bst.Insert(2);
    bst.Insert(1);   
    expect(bst.Predecessor(8) == 7);
    expect(bst.Predecessor(7) == 6);
    expect(bst.Predecessor(6) == 5);
    expect(bst.Predecessor(5) == 4);
    expect(bst.Predecessor(4) == 3);
    expect(bst.Predecessor(3) == 2);
    expect(bst.Predecessor(2) == 1);
    expect(bst.Predecessor(0) == 1);
}




void successors_t1(){
    auto bst = lasd::BST<int>();
    bst.Insert(8);
    bst.Insert(9);
    bst.Insert(3);
    bst.Insert(0);
    bst.Insert(6);
    bst.Insert(4);
    expect(bst.Successor(6) == 8);
    expect(bst.Successor(4) == 6);
    expect(bst.Successor(5) == 6);
    expect(bst.Successor(0) == 3);
    expect(bst.Successor(8) == 9);
}




void successors_t2(){
    auto bst = lasd::BST<int>();
    bst.Insert(7);
    bst.Insert(8);   
    expect(bst.Successor(7) == 8);
}




void successors_t3(){
    auto bst = lasd::BST<int>();
    bst.Insert(7);
    bst.Insert(8);
    bst.Insert(9);   
    expect(bst.Successor(8) == 9);
    expect(bst.Successor(7) == 8);
}




void successors_t4(){
    auto bst = lasd::BST<int>();
    bst.Insert(100);
    bst.Insert(150);
    bst.Insert(200);
    bst.Insert(165);   
    expect(bst.Successor(165) == 200);
    expect(bst.Successor(150) == 165);
}





void successors_t5(){
    expect_exception<std::length_error>([](){
        auto bst = lasd::BST<int>();
        bst.Insert(7);
        bst.Insert(8);
        bst.Insert(9);   
        bst.Successor(9);    
    });
}




void successors_t6(){
    auto bst = lasd::BST<int>();
    bst.Insert(1);
    bst.Insert(2);
    bst.Insert(3);
    bst.Insert(4);
    bst.Insert(5);
    bst.Insert(6);
    bst.Insert(8);   
    expect(bst.Successor(0) == 1);
    expect(bst.Successor(1) == 2);
    expect(bst.Successor(2) == 3);
    expect(bst.Successor(3) == 4);
    expect(bst.Successor(4) == 5);
    expect(bst.Successor(5) == 6);
    expect(bst.Successor(6) == 8);
    expect(bst.Successor(7) == 8);
}




void maxNremove_t1(){
    auto bst = lasd::BST<int>();
    bst.Insert(1);
    bst.Insert(2);
    bst.Insert(3);
    expect(bst.MaxNRemove() == 3);
    expect(bst.MaxNRemove() == 2);
    expect(bst.MaxNRemove() == 1);
    expect(bst.Empty());
}




void maxNremove_t2(){
    auto bst = lasd::BST<int>();
    bst.Insert(3);
    bst.Insert(2);
    bst.Insert(1);
    expect(bst.MaxNRemove() == 3);
    expect(bst.MaxNRemove() == 2);
    expect(bst.MaxNRemove() == 1);
    expect(bst.Empty());
}



void maxNremove_t3(){
    auto bst = lasd::BST<int>();
    bst.Insert(2);
    bst.Insert(1);
    bst.Insert(3);
    expect(bst.MaxNRemove() == 3);
    expect(bst.MaxNRemove() == 2);
    expect(bst.MaxNRemove() == 1);
    expect(bst.Empty());
}




void minNremove_t1(){
    auto bst = lasd::BST<int>();
    bst.Insert(1);
    bst.Insert(2);
    bst.Insert(3);
    expect(bst.MinNRemove() == 1);
    expect(bst.MinNRemove() == 2);
    expect(bst.MinNRemove() == 3);
    expect(bst.Empty());
}




void minNremove_t2(){
    auto bst = lasd::BST<int>();
    bst.Insert(3);
    bst.Insert(2);
    bst.Insert(1);
    expect(bst.MinNRemove() == 1);
    expect(bst.MinNRemove() == 2);
    expect(bst.MinNRemove() == 3);
    expect(bst.Empty());
}




void minNremove_t3(){
    auto bst = lasd::BST<int>();
    bst.Insert(2);
    bst.Insert(1);
    bst.Insert(3);
    expect(bst.MinNRemove() == 1);
    expect(bst.MinNRemove() == 2);
    expect(bst.MinNRemove() == 3);
    expect(bst.Empty());
}





void execute_bst_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::BST<T> ↓↓↓ \n");
    UnitTest bst_test_procedures {
       {"empty_bst_allocation",        empty_bst_allocation}, 
       {"bst_insertions_t1",           bst_insertions_t1},
       {"bst_insertions_t2",           bst_insertions_t2}, 
       {"bst_insertions_t3",           bst_insertions_t3}, 
       {"bst_deletions_t1",            bst_deletions_t1}, 
       {"bst_deletions_t2",            bst_deletions_t2}, 
       {"bst_deletions_t3",            bst_deletions_t3}, 
       {"bst_deletions_t4",            bst_deletions_t4}, 
       {"bst_deletions_t5",            bst_deletions_t5}, 
       {"bst_deletions_t6",            bst_deletions_t6}, 
       {"bst_min_max_exists",          bst_min_max_exists}, 
       {"predecessors_t1",             predecessors_t1}, 
       {"predecessors_t2",             predecessors_t2},
       {"predecessors_t3",             predecessors_t3}, 
       {"predecessors_t4",             predecessors_t4}, 
       {"predecessors_t5",             predecessors_t5}, 
       {"predecessors_t6",             predecessors_t6}, 
       {"successors_t1",               successors_t1},
       {"successors_t2",               successors_t2},
       {"successors_t3",               successors_t3},
       {"successors_t4",               successors_t4},
       {"successors_t5",               successors_t5},
       {"successors_t6",               successors_t6}, 
       {"minNremove_t1",               minNremove_t1},
       {"minNremove_t2",               minNremove_t2},
       {"minNremove_t3",               minNremove_t3},
       {"maxNremove_t1",               maxNremove_t1},
       {"maxNremove_t2",               maxNremove_t2},
       {"maxNremove_t3",               maxNremove_t3}, 
    };
    execute_tests(bst_test_procedures);  
}