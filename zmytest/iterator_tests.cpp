
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
        {"preorder_iterator_t1",    preorder_iterator_t1},
        {"preorder_iterator_t2",    preorder_iterator_t2},
        {"preorder_iterator_t3",    preorder_iterator_t3},
        {"preorder_iterator_t4",    preorder_iterator_t4},
        {"preorder_iterator_t5",    preorder_iterator_t5},
        {"breadth_iterator_t1",     breadth_iterator_t1},
        {"breadth_iterator_t2",     breadth_iterator_t2},
        {"breadth_iterator_t3",     breadth_iterator_t3},
        {"breadth_iterator_t4",     breadth_iterator_t4},
        {"breadth_iterator_t5",     breadth_iterator_t5},
    };
    execute_tests(iterator_test_procedures);  
}
