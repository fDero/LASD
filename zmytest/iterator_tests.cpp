
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/foldable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"
#include "../vector/vector.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/lnk/binarytreelnk.hpp"
#include "../binarytree/binarytree.hpp"
#include "../binarytree/vec/binarytreevec.hpp"
#include "../bst/bst.hpp"



void emptytree_iterator_tests(){
    auto empty_tree = lasd::BST<int>();
    auto preit = lasd::BTPreOrderIterator<int>(empty_tree);
    auto postit = lasd::BTPostOrderIterator<int>(empty_tree);
    auto init = lasd::BTInOrderIterator<int>(empty_tree);
    auto brit = lasd::BTBreadthIterator<int>(empty_tree);
    expect(preit.Terminated());
    expect(postit.Terminated());
    expect(init.Terminated());
    expect(brit.Terminated());
    preit.Reset();
    postit.Reset();
    init.Reset();
    brit.Reset();
    expect(preit.Terminated());
    expect(postit.Terminated());
    expect(init.Terminated());
    expect(brit.Terminated());
}





void moveassignment_iterator_t1(){
    auto empty_tree = lasd::BST<int>();
    auto preit = lasd::BTPreOrderIterator<int>(empty_tree);
    auto postit = lasd::BTPostOrderIterator<int>(empty_tree);
    auto init = lasd::BTInOrderIterator<int>(empty_tree);
    auto brit = lasd::BTBreadthIterator<int>(empty_tree);
    
    auto mvdpreit  = lasd::BTPreOrderIterator<int>(std::move(preit));
    auto mvdpostit = lasd::BTPostOrderIterator<int>(std::move(postit));
    auto mvdinit   = lasd::BTInOrderIterator<int>(std::move(init));
    auto mvdbrit   = lasd::BTBreadthIterator<int>(std::move(brit));
    
    expect(preit.Terminated());
    expect(postit.Terminated());
    expect(init.Terminated());
    expect(brit.Terminated());
}




void moveassignment_iterator_t2(){
    auto tree = lasd::BinaryTreeVec<char>(generate_sample_vector(2));
    auto preit = lasd::BTPreOrderIterator<char>(tree);
    auto postit = lasd::BTPostOrderIterator<char>(tree);
    auto init = lasd::BTInOrderIterator<char>(tree);
    auto brit = lasd::BTBreadthIterator<char>(tree);
    
    auto mvdpreit  = lasd::BTPreOrderIterator<char>(std::move(preit));
    auto mvdpostit = lasd::BTPostOrderIterator<char>(std::move(postit));
    auto mvdinit   = lasd::BTInOrderIterator<char>(std::move(init));
    auto mvdbrit   = lasd::BTBreadthIterator<char>(std::move(brit));
    
    expect(preit.Terminated());
    expect(postit.Terminated());
    expect(init.Terminated());
    expect(brit.Terminated());
}



void preorder_iterator_t1(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(3));
    auto it = lasd::BTPreOrderIterator<char>(tree);
    expect(*it == 'A'); ++it;
    expect(*it == 'B'); ++it;
    expect(*it == 'C'); ++it;
    expect(it.Terminated());
}




void preorder_iterator_t2(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(9));
    auto it = lasd::BTPreOrderIterator<char>(tree);
    expect(*it == 'A'); ++it;
    expect(*it == 'B'); ++it;
    expect(*it == 'D'); ++it;
    expect(*it == 'H'); ++it;
    expect(*it == 'I'); ++it;
    expect(*it == 'E'); ++it;
    expect(*it == 'C'); ++it;
    expect(*it == 'F'); ++it;
    expect(*it == 'G'); ++it;
    expect(it.Terminated());
}





void preorder_iterator_t3(){
    auto tree = lasd::BST<int>();
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(15);
    tree.Insert(17);
    auto it = lasd::BTPreOrderIterator<int>(tree);
    expect(*it == 10); ++it;
    expect(*it == 5);  ++it;
    expect(*it == 3);  ++it;
    expect(*it == 15); ++it;
    expect(*it == 17); ++it;
    expect(it.Terminated());
}




void preorder_iterator_t4(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(4));
    auto it = lasd::BTPreOrderMutableIterator<char>(tree);
    expect(*it == 'A'); *it = 'a'; ++it;
    expect(*it == 'B'); *it = 'b'; ++it;
    expect(*it == 'D'); *it = 'd'; ++it;
    expect(*it == 'C'); *it = 'c'; ++it;
    expect(it.Terminated());
    it.Reset();
    expect(*it == 'a'); ++it;
    expect(*it == 'b'); ++it;
    expect(*it == 'd'); ++it;
    expect(*it == 'c'); ++it;
    expect(it.Terminated());
}




void preorder_iterator_t5(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(4));
    auto it = lasd::BTPreOrderMutableIterator<char>(tree);
    expect(*it == 'A'); *it = 'a'; ++it;
    expect(*it == 'B'); *it = 'b'; ++it;
    
    auto copied = it;    
    auto moved = std::move(it);
    
    expect(moved == copied);

    expect(*copied == 'D'); *copied = 'd'; ++copied;
    expect(*copied == 'C'); *copied = 'c'; ++copied;
    expect(copied.Terminated());
    
    expect(*moved == 'd'); ++moved;
    expect(*moved == 'c'); ++moved;
    expect(moved.Terminated());
}





void postorder_iterator_t1(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(3));
    auto it = lasd::BTPostOrderMutableIterator<char>(tree);
    expect(*it == 'B'); ++it;
    expect(*it == 'C'); ++it;
    expect(*it == 'A'); ++it;
    expect(it.Terminated());
}




void postorder_iterator_t2(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(9));
    auto it = lasd::BTPostOrderMutableIterator<char>(tree);
    expect(*it == 'H'); ++it;
    expect(*it == 'I'); ++it;
    expect(*it == 'D'); ++it;
    expect(*it == 'E'); ++it;
    expect(*it == 'B'); ++it;
    expect(*it == 'F'); ++it;
    expect(*it == 'G'); ++it;
    expect(*it == 'C'); ++it;
    expect(*it == 'A'); ++it;
    expect(it.Terminated());
}





void postorder_iterator_t3(){
    auto tree = lasd::BST<int>();
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(15);
    tree.Insert(17);
    auto it = lasd::BTPostOrderIterator<int>(tree);
    expect(*it == 3);  ++it;
    expect(*it == 5);  ++it;
    expect(*it == 17); ++it;
    expect(*it == 15); ++it;
    expect(*it == 10); ++it;
    expect(it.Terminated());
}




void postorder_iterator_t4(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(4));
    auto it = lasd::BTPostOrderMutableIterator<char>(tree);
    expect(*it == 'D'); *it = 'd'; ++it;
    expect(*it == 'B'); *it = 'b'; ++it;
    expect(*it == 'C'); *it = 'c'; ++it;
    expect(*it == 'A'); *it = 'a'; ++it;
    expect(it.Terminated());
    it.Reset();
    expect(*it == 'd'); ++it;
    expect(*it == 'b'); ++it;
    expect(*it == 'c'); ++it;
    expect(*it == 'a'); ++it;
    expect(it.Terminated());
}




void postorder_iterator_t5(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(4));
    auto it = lasd::BTPostOrderMutableIterator<char>(tree);
    expect(*it == 'D'); *it = 'd'; ++it;
    expect(*it == 'B'); *it = 'b'; ++it;
    
    auto copied = it;    
    auto moved = std::move(it);
    
    expect(moved == copied);

    expect(*copied == 'C'); *copied = 'c'; ++copied;
    expect(*copied == 'A'); *copied = 'a'; ++copied;
    expect(copied.Terminated());
    
    expect(*moved == 'c'); ++moved;
    expect(*moved == 'a'); ++moved;
    expect(moved.Terminated());
}





void inorder_iterator_t1(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(3));
    auto it = lasd::BTInOrderMutableIterator<char>(tree);
    expect(*it == 'B'); ++it;
    expect(*it == 'A'); ++it;
    expect(*it == 'C'); ++it;
    expect(it.Terminated());
}




void inorder_iterator_t2(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(9));
    auto it = lasd::BTInOrderMutableIterator<char>(tree);
    expect(*it == 'H'); ++it;
    expect(*it == 'D'); ++it;
    expect(*it == 'I'); ++it;
    expect(*it == 'B'); ++it;
    expect(*it == 'E'); ++it;
    expect(*it == 'A'); ++it;
    expect(*it == 'F'); ++it;
    expect(*it == 'C'); ++it;
    expect(*it == 'G'); ++it;
    expect(it.Terminated());
}





void inorder_iterator_t3(){
    auto tree = lasd::BST<int>();
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(15);
    tree.Insert(17);
    auto it = lasd::BTInOrderIterator<int>(tree);
    expect(*it == 3);  ++it;
    expect(*it == 5);  ++it;
    expect(*it == 10); ++it;
    expect(*it == 15); ++it;
    expect(*it == 17); ++it;
    expect(it.Terminated());
}




void inorder_iterator_t4(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(4));
    auto it = lasd::BTInOrderMutableIterator<char>(tree);
    expect(*it == 'D'); *it = 'd'; ++it;
    expect(*it == 'B'); *it = 'b'; ++it;
    expect(*it == 'A'); *it = 'a'; ++it;
    expect(*it == 'C'); *it = 'c'; ++it;
    expect(it.Terminated());
    it.Reset();
    expect(*it == 'd'); ++it;
    expect(*it == 'b'); ++it;
    expect(*it == 'a'); ++it;
    expect(*it == 'c'); ++it;
    expect(it.Terminated());
}




void inorder_iterator_t5(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(4));
    auto it = lasd::BTInOrderMutableIterator<char>(tree);
    expect(*it == 'D'); *it = 'd'; ++it;
    expect(*it == 'B'); *it = 'b'; ++it;
    
    auto copied = it;    
    auto moved = std::move(it);
    
    expect(moved == copied);

    expect(*copied == 'A'); *copied = 'a'; ++copied;
    expect(*copied == 'C'); *copied = 'c'; ++copied;
    expect(copied.Terminated());
    
    expect(*moved == 'a'); ++moved;
    expect(*moved == 'c'); ++moved;
    expect(moved.Terminated());
}




void breadth_iterator_t1(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(3));
    auto it = lasd::BTBreadthIterator<char>(tree);
    expect(*it == 'A'); ++it;
    expect(*it == 'B'); ++it;
    expect(*it == 'C'); ++it;
    expect(it.Terminated());
}




void breadth_iterator_t2(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(9));
    auto it = lasd::BTBreadthIterator<char>(tree);
    expect(*it == 'A'); ++it;
    expect(*it == 'B'); ++it;
    expect(*it == 'C'); ++it;
    expect(*it == 'D'); ++it;
    expect(*it == 'E'); ++it;
    expect(*it == 'F'); ++it;
    expect(*it == 'G'); ++it;
    expect(*it == 'H'); ++it;
    expect(*it == 'I'); ++it;
    expect(it.Terminated());
}




void breadth_iterator_t3(){
    auto tree = lasd::BST<int>();
    tree.Insert(10);
    tree.Insert(5);
    tree.Insert(3);
    tree.Insert(15);
    tree.Insert(17);
    auto it = lasd::BTBreadthIterator<int>(tree);
    expect(*it == 10); ++it;
    expect(*it == 5);  ++it;
    expect(*it == 15); ++it;
    expect(*it == 3);  ++it;
    expect(*it == 17); ++it;
    expect(it.Terminated());
}




void breadth_iterator_t4(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(4));
    auto it = lasd::BTBreadthMutableIterator<char>(tree);
    expect(*it == 'A'); *it = 'a'; ++it;
    expect(*it == 'B'); *it = 'b'; ++it;
    expect(*it == 'C'); *it = 'c'; ++it;
    expect(*it == 'D'); *it = 'd'; ++it;
    expect(it.Terminated());
    it.Reset();
    expect(*it == 'a'); ++it;
    expect(*it == 'b'); ++it;
    expect(*it == 'c'); ++it;
    expect(*it == 'd'); ++it;
    expect(it.Terminated());
}




void breadth_iterator_t5(){
    auto tree = lasd::BinaryTreeLnk<char>(generate_sample_vector(4));
    auto it = lasd::BTBreadthMutableIterator<char>(tree);
    expect(*it == 'A'); *it = 'a'; ++it;
    expect(*it == 'B'); *it = 'b'; ++it;
    
    auto copied = it;    
    auto moved = std::move(it);
    
    expect(moved == copied);

    expect(*copied == 'C'); *copied = 'c'; ++copied;
    expect(*copied == 'D'); *copied = 'd'; ++copied;
    expect(copied.Terminated());
    
    expect(*moved == 'c'); ++moved;
    expect(*moved == 'd'); ++moved;
    expect(moved.Terminated());
}




void execute_iterator_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for the all iterators on trees ↓↓↓ \n");
    UnitTest iterator_test_procedures {
        {"emptytree_iterator_tests",  emptytree_iterator_tests},
        {"move_assignment_iter_t1",   moveassignment_iterator_t1},
        {"move_assignment_iter_t2",   moveassignment_iterator_t2},
        {"preorder_iterator_t1",      preorder_iterator_t1},
        {"preorder_iterator_t2",      preorder_iterator_t2},
        {"preorder_iterator_t3",      preorder_iterator_t3},
        {"preorder_iterator_t4",      preorder_iterator_t4},
        {"preorder_iterator_t5",      preorder_iterator_t5},
        {"postorder_iterator_t1",     postorder_iterator_t1},
        {"postorder_iterator_t2",     postorder_iterator_t2},
        {"postorder_iterator_t3",     postorder_iterator_t3},
        {"postorder_iterator_t4",     postorder_iterator_t4},
        {"postorder_iterator_t5",     postorder_iterator_t5},
        {"inorder_iterator_t1",       inorder_iterator_t1},
        {"inorder_iterator_t2",       inorder_iterator_t2},
        {"inorder_iterator_t3",       inorder_iterator_t3},
        {"inorder_iterator_t4",       inorder_iterator_t4},
        {"inorder_iterator_t5",       inorder_iterator_t5},
        {"breadth_iterator_t1",       breadth_iterator_t1},
        {"breadth_iterator_t2",       breadth_iterator_t2},
        {"breadth_iterator_t3",       breadth_iterator_t3},
        {"breadth_iterator_t4",       breadth_iterator_t4},
        {"breadth_iterator_t5",       breadth_iterator_t5},
    };
    execute_tests(iterator_test_procedures);  
}
