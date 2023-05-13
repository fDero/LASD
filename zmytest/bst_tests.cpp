
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




void bst_deletions_t7(){
    auto bst = lasd::BST<int>();
    bst.Insert(100);
    bst.Insert(200);
    bst.Insert(300);
    bst.Insert(250);
    bst.Insert(50);
    bst.Insert(75);
    bst.Insert(25);
    bst.Insert(10);
    bst.Insert(5);

    expect(bst.Remove(10));
    expect(bst.Remove(25));
    expect(bst.Remove(200));
    expect(bst.Remove(100));
    
    expect(bst.Root().Element() == 250);
    expect(bst.Root().RightChild().Element() == 300);
    expect(bst.Root().LeftChild().Element() == 50);
    expect(bst.Root().LeftChild().LeftChild().Element() == 5);
    expect(bst.Root().LeftChild().RightChild().Element() == 75);

    expect(not bst.Exists(200));
    expect(bst.Exists(5));
}




void bst_deletions_t8(){
    auto bst = lasd::BST<int>();
    bst.Insert(50);
    bst.Insert(100);
    bst.Insert(70);
    bst.Insert(25);
    bst.Insert(10);
    expect(bst.Remove(50));
    expect(bst.Root().Element() == 25);
    expect(bst.Root().LeftChild().Element() == 10);
    expect(bst.Root().RightChild().Element() == 100);
    expect(bst.Root().RightChild().LeftChild().Element() == 70);
}




void bst_deletions_t9(){
    auto bst = lasd::BST<int>();
    bst.Insert(2000);
    bst.Insert(1000);
    bst.Insert(3000);
    bst.Insert(2500);
    bst.Insert(7000);
    bst.Insert(8000);
    bst.Insert(5000);
    bst.Insert(4000);
    bst.Insert(4500);
    bst.Insert(4250);
    bst.Insert(4700);
    expect(bst.Remove(7000));
    expect(bst.Exists(2000));
    expect(bst.Exists(1000));
    expect(bst.Exists(3000));
    expect(bst.Exists(2500));
    expect(bst.Exists(8000));
    expect(bst.Exists(5000));
    expect(bst.Exists(4000));
    expect(bst.Exists(4500));
    expect(bst.Exists(4250));
    expect(bst.Exists(4700));
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




void predecessors_t7(){
    auto bst = lasd::BST<int>();
    bst.Insert(100);
    bst.Insert(50);
    bst.Insert(30);
    bst.Insert(45);
    bst.Insert(40);
    expect(bst.Predecessor(100) == 50);
    expect(bst.Predecessor(90) == 50);
    expect(bst.Predecessor(50) == 45);
    expect(bst.Predecessor(51) == 50);
    expect(bst.Predecessor(40) == 30);
    bst.Insert(60);
    bst.Insert(59);
    bst.Insert(58);
    expect(bst.Predecessor(61) == 60);
    expect(bst.Predecessor(60) == 59);
    expect(bst.Predecessor(59) == 58);
    expect(bst.Predecessor(58) == 50);
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




void successors_t7(){
    auto bst = lasd::BST<int>();
    bst.Insert(100);
    bst.Insert(150);
    bst.Insert(130);
    bst.Insert(145);
    bst.Insert(200);
    bst.Insert(250);
    expect(bst.Successor(200) == 250);
    expect(bst.Successor(215) == 250);
    expect(bst.Successor(130) == 145);
    expect(bst.Successor(135) == 145);
    expect(bst.Successor(150) == 200);
    expect(bst.Successor(160) == 200);
    expect(bst.Successor(100) == 130);
    expect(bst.Successor(110) == 130);
    bst.Insert(160);
    bst.Insert(230);
    expect(bst.Successor(150) == 160);
    expect(bst.Successor(155) == 160);
    expect(bst.Successor(200) == 230);
    expect(bst.Successor(225) == 230);
}




void successors_t8(){
    auto bst = lasd::BST<int>();
    bst.Insert(100);
    bst.Insert(150);
    bst.Insert(120);
    bst.Insert(130);
    bst.Insert(125);
    bst.Insert(110);
    expect(bst.Successor(100) == 110);
    expect(bst.Successor(105) == 110);
    expect(bst.Successor(110) == 120);
    expect(bst.Successor(115) == 120);
}




void successorNremove(){
    auto bst = lasd::BST<int>();
    bst.Insert(100);
    bst.Insert(150);
    bst.Insert(130);
    bst.Insert(145);
    bst.Insert(200);
    bst.Insert(250);
    expect(bst.SuccessorNRemove(150) == 200);
    expect(bst.SuccessorNRemove(130) == 145);
    expect(bst.SuccessorNRemove(100) == 130);
    expect(not bst.Exists(130));
    expect(not bst.Exists(145));
    expect(not bst.Exists(200));
}



void predecessorNremove(){
    auto bst = lasd::BST<int>();
    bst.Insert(100);
    bst.Insert(50);
    bst.Insert(30);
    bst.Insert(45);
    bst.Insert(40);
    expect(bst.PredecessorNRemove(45) == 40);
    expect(bst.PredecessorNRemove(45) == 30);
    expect(bst.PredecessorNRemove(60) == 50);
    expect(bst.Size() == 2);
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




void bst_copyassignment_t1(){
    auto bst = lasd::BST<int>();
    bst.Insert(100);
    bst.Insert(200);
    bst.Insert(300);
    bst.Insert(250);
    bst.Insert(50);
    bst.Insert(75);
    bst.Insert(25);
    bst.Insert(10);
    bst.Insert(5);
    auto copied = bst;
    expect(copied == bst);
    expect(bst == copied);
    lasd::BinaryTree<int>& casted_bst = bst;
    lasd::BinaryTree<int>& casted_copy = bst;
    expect(casted_bst == casted_copy);
    expect(casted_copy == casted_bst);
}




void bst_copyassignment_t2(){
    auto bst1 = lasd::BST<int>();
    auto bst2 = lasd::BST<int>();
    bst1.Insert(100);
    bst1.Insert(200);
    bst1.Insert(300);
    bst1.Insert(250);
    bst1.Insert(50);
    bst1.Insert(75);
    bst1.Insert(25);
    bst1.Insert(10);
    bst1.Insert(5);
    bst2.Insert(100);
    bst2.Insert(200);
    bst2.Insert(300);
    bst2.Insert(400);
    bst2.Insert(350);
    bst2.Insert(450);
    bst2.Insert(500);
    bst2 = bst1;
    expect(bst2 == bst1);
    expect(bst1 == bst2);
    lasd::BinaryTree<int>& casted_bst1 = bst1;
    lasd::BinaryTree<int>& casted_bst2 = bst2;
    expect(casted_bst1 == casted_bst2);
    expect(casted_bst2 == casted_bst1);
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
        {"bst_deletions_t7",            bst_deletions_t7}, 
        {"bst_deletions_t8",            bst_deletions_t8}, 
        {"bst_deletions_t9",            bst_deletions_t9}, 
        {"bst_min_max_exists",          bst_min_max_exists}, 
        {"predecessors_t1",             predecessors_t1}, 
        {"predecessors_t2",             predecessors_t2},
        {"predecessors_t3",             predecessors_t3}, 
        {"predecessors_t4",             predecessors_t4}, 
        {"predecessors_t5",             predecessors_t5}, 
        {"predecessors_t6",             predecessors_t6}, 
        {"predecessors_t7",             predecessors_t7}, 
        {"successors_t1",               successors_t1},
        {"successors_t2",               successors_t2},
        {"successors_t3",               successors_t3},
        {"successors_t4",               successors_t4},
        {"successors_t5",               successors_t5},
        {"successors_t6",               successors_t6}, 
        {"successors_t7",               successors_t7}, 
        {"successors_t8",               successors_t8}, 
        {"minNremove_t1",               minNremove_t1},
        {"minNremove_t2",               minNremove_t2},
        {"minNremove_t3",               minNremove_t3},
        {"maxNremove_t1",               maxNremove_t1},
        {"maxNremove_t2",               maxNremove_t2},
        {"maxNremove_t3",               maxNremove_t3}, 
        {"bst_copyassignment_t1",       bst_copyassignment_t1},
        {"bst_copyassignment_t2",       bst_copyassignment_t2},  
        {"predecessorNremove",          predecessorNremove},
        {"successorNremove",            successorNremove},
        
    };
    execute_tests(bst_test_procedures);  
}