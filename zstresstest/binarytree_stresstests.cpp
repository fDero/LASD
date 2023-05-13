
// FRANCESCO DE ROSA N86004379

#include "stresstest.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../bst/bst.hpp"

void binarytree_vec_lnk_construction_stresstest(){
    auto vec = lasd::Vector<int>(100);
    for (long attempt = 1; attempt <= 100; attempt++){
        vec.Map([](int& x){ x = get_random_value(); });
        auto btlnk = lasd::BinaryTreeLnk<int>(vec);
        auto btvec = lasd::BinaryTreeVec<int>(vec);
        lasd::BinaryTree<int>& btlnkref  = btlnk;
        lasd::BinaryTree<int>& btvecref  = btvec;
        expect(btvecref == btlnkref);    
    }
}

void binarytree_vec_lnk_assignment_stresstest(){
    auto vec = lasd::Vector<int>(100);
    for (long attempt = 1; attempt <= 100; attempt++){
        vec.Map([](int& x){ x = get_random_value(); });
        auto btlnk = lasd::BinaryTreeLnk<int>(vec);
        auto btvec = lasd::BinaryTreeVec<int>(vec);
        lasd::BinaryTreeLnk<int> btlnkcopy  = btlnk;
        lasd::BinaryTreeVec<int> btveccopy  = btvec;
        lasd::BinaryTreeLnk<int> btlnkmvd  = std::move(btlnk);
        lasd::BinaryTreeVec<int> btvecmvd  = std::move(btvec);
        expect(btveccopy == btvecmvd);
        expect(btlnkcopy == btlnkmvd);
    }
}

void execute_binarytree_stresstests(){
    execute_test("binarytree_vec_lnk_construction_stresstest - 1",  binarytree_vec_lnk_construction_stresstest);
    execute_test("binarytree_vec_lnk_construction_stresstest - 2",  binarytree_vec_lnk_construction_stresstest);
    execute_test("binarytree_vec_lnk_assignment_stresstest - 1",    binarytree_vec_lnk_assignment_stresstest);
    execute_test("binarytree_vec_lnk_assignment_stresstest - 2",    binarytree_vec_lnk_assignment_stresstest);
}