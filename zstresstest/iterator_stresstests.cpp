
// FRANCESCO DE ROSA N86004379

#include "stresstest.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../bst/bst.hpp"

void binarytree_breadth_iteratation_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 1000; attempt++){
        while (tree.Size() < 1000) tree.Insert(get_random_value());
        auto it = lasd::BTBreadthIterator<int>(tree);
        tree.BreadthMap([&it](const int& x){
            expect(*it == x);
            ++it;
        });
    }
}

void binarytree_preorder_iteratation_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 100; attempt++){
        while (tree.Size() < 100) tree.Insert(get_random_value());
        auto it = lasd::BTPreOrderIterator<int>(tree);
        tree.PreOrderMap([&it](const int& x){
            expect(*it == x);
            ++it;
        });
    }
}

void binarytree_postorder_iteratation_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 100; attempt++){
        while (tree.Size() < 100) tree.Insert(get_random_value());
        auto it = lasd::BTPostOrderIterator<int>(tree);
        tree.PostOrderMap([&it](const int& x){
            expect(*it == x);
            ++it;
        });
    }
}

void binarytree_inorder_iteratation_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 100; attempt++){
        while (tree.Size() < 100) tree.Insert(get_random_value());
        auto it = lasd::BTInOrderIterator<int>(tree);
        tree.InOrderMap([&it](const int& x){
            expect(*it == x);
            ++it;
        });
    }
}

void execute_iterators_stresstests(){
    execute_test("binarytree_breadth_iteratation_stresstest",   binarytree_breadth_iteratation_stresstest);
    execute_test("binarytree_preorder_iteratation_stresstest",  binarytree_preorder_iteratation_stresstest);
    execute_test("binarytree_postorder_iteratation_stresstest", binarytree_postorder_iteratation_stresstest);
    execute_test("binarytree_inorder_iteratation_stresstest",   binarytree_inorder_iteratation_stresstest);
}