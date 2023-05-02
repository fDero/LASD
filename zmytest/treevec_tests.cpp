
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
#include "../binarytree/vec/binarytreevec.hpp"



void construct_trees_from_mappable_t1(){
    auto empty_tree         = lasd::BinaryTreeVec<int>(lasd::Vector<int>(0));
    auto one_element_tree   = lasd::BinaryTreeVec<int>(lasd::Vector<int>(1));
    auto three_element_tree = lasd::BinaryTreeVec<int>(lasd::Vector<int>(3));
    auto five_element_tree  = lasd::BinaryTreeVec<int>(lasd::Vector<int>(5));
    auto nine_element_tree  = lasd::BinaryTreeVec<int>(lasd::Vector<int>(9));
}




void construct_trees_from_mappable_t2(){
    auto empty_vec          = lasd::Vector<int>(0);
    auto one_element_vec    = lasd::Vector<int>(1);
    auto three_element_vec  = lasd::Vector<int>(3);
    auto five_element_vec   = lasd::Vector<int>(5);
    auto nine_element_vec   = lasd::Vector<int>(9);

    auto empty_tree         = lasd::BinaryTreeVec<int>(empty_vec);
    auto one_element_tree   = lasd::BinaryTreeVec<int>(one_element_vec);
    auto three_element_tree = lasd::BinaryTreeVec<int>(three_element_vec);
    auto five_element_tree  = lasd::BinaryTreeVec<int>(five_element_vec);
    auto nine_element_tree  = lasd::BinaryTreeVec<int>(nine_element_vec);
}




void construct_trees_from_mappable_t3(){
    auto empty_vec          = lasd::Vector<int>(0);
    auto one_element_vec    = lasd::Vector<int>(1);
    auto three_element_vec  = lasd::Vector<int>(3);
    auto five_element_vec   = lasd::Vector<int>(5);
    auto nine_element_vec   = lasd::Vector<int>(9);

    auto empty_tree         = lasd::BinaryTreeVec<int>(std::move(empty_vec));
    auto one_element_tree   = lasd::BinaryTreeVec<int>(std::move(one_element_vec));
    auto three_element_tree = lasd::BinaryTreeVec<int>(std::move(three_element_vec));
    auto five_element_tree  = lasd::BinaryTreeVec<int>(std::move(five_element_vec));
    auto nine_element_tree  = lasd::BinaryTreeVec<int>(std::move(nine_element_vec));
}





void inspection_of_binarytreevec(){
  lasd::BinaryTreeVec<char> empty_tree         { generate_sample_vector(0) };
  lasd::BinaryTreeVec<char> one_element_tree   { generate_sample_vector(1) };
  lasd::BinaryTreeVec<char> three_element_tree { generate_sample_vector(3) };
  lasd::BinaryTreeVec<char> five_element_tree  { generate_sample_vector(5) };
  lasd::BinaryTreeVec<char> nine_element_tree  { generate_sample_vector(9) };
  
  expect(one_element_tree.Root().Element() == 'A');
  
  
  expect(three_element_tree.Root().LeftChild().Element() == 'B');
  expect(three_element_tree.Root().RightChild().Element() == 'C');
  
  expect(five_element_tree.Root().LeftChild().LeftChild().Element() == 'D');
  expect(five_element_tree.Root().LeftChild().RightChild().Element() == 'E');
  
  expect(nine_element_tree.Root().RightChild().LeftChild().Element() == 'F');
  expect(nine_element_tree.Root().RightChild().RightChild().Element() == 'G');
  expect(nine_element_tree.Root().LeftChild().LeftChild().LeftChild().Element() == 'H');
  expect(nine_element_tree.Root().LeftChild().LeftChild().RightChild().Element() == 'I');
}




void inspection_of_binarytreevec_copies_t1(){
  auto empty_vec         = generate_sample_vector(0);
  auto one_element_vec   = generate_sample_vector(1);
  auto three_element_vec = generate_sample_vector(3);
  auto five_element_vec  = generate_sample_vector(5);
  auto nine_element_vec  = generate_sample_vector(9);

  lasd::BinaryTreeVec<char> empty_tree         { empty_vec };
  lasd::BinaryTreeVec<char> one_element_tree   { one_element_vec };
  lasd::BinaryTreeVec<char> three_element_tree { three_element_vec };
  lasd::BinaryTreeVec<char> five_element_tree  { five_element_vec };
  lasd::BinaryTreeVec<char> nine_element_tree  { nine_element_vec };
  
  lasd::BinaryTreeVec<char> copied_empty_tree         = empty_tree;
  lasd::BinaryTreeVec<char> copied_one_element_tree   = one_element_tree;
  lasd::BinaryTreeVec<char> copied_three_element_tree = three_element_tree;
  lasd::BinaryTreeVec<char> copied_five_element_tree  = five_element_tree;
  lasd::BinaryTreeVec<char> copied_nine_element_tree  = nine_element_tree;
  

  expect(copied_one_element_tree.Root().Element() == 'A');
  
  expect(copied_three_element_tree.Root().LeftChild().Element() == 'B');
  expect(copied_three_element_tree.Root().RightChild().Element() == 'C');
  
  expect(copied_five_element_tree.Root().LeftChild().LeftChild().Element() == 'D');
  expect(copied_five_element_tree.Root().LeftChild().RightChild().Element() == 'E');
  
  expect(copied_nine_element_tree.Root().RightChild().LeftChild().Element() == 'F');
  expect(copied_nine_element_tree.Root().RightChild().RightChild().Element() == 'G');
  expect(copied_nine_element_tree.Root().LeftChild().LeftChild().LeftChild().Element() == 'H');
  expect(copied_nine_element_tree.Root().LeftChild().LeftChild().RightChild().Element() == 'I');
}




void inspection_of_binarytreevec_copies_t2(){
  auto empty_vec         = generate_sample_vector(0);
  auto one_element_vec   = generate_sample_vector(1);
  auto three_element_vec = generate_sample_vector(3);
  auto five_element_vec  = generate_sample_vector(5);
  auto nine_element_vec  = generate_sample_vector(9);

  lasd::BinaryTreeVec<char> empty_tree         { empty_vec };
  lasd::BinaryTreeVec<char> one_element_tree   { one_element_vec };
  lasd::BinaryTreeVec<char> three_element_tree { three_element_vec };
  lasd::BinaryTreeVec<char> five_element_tree  { five_element_vec };
  lasd::BinaryTreeVec<char> nine_element_tree  { nine_element_vec };
  
  lasd::BinaryTreeVec<char> copied_empty_tree         = empty_tree;
  lasd::BinaryTreeVec<char> copied_one_element_tree   = one_element_tree;
  lasd::BinaryTreeVec<char> copied_three_element_tree = three_element_tree;
  lasd::BinaryTreeVec<char> copied_five_element_tree  = five_element_tree;
  lasd::BinaryTreeVec<char> copied_nine_element_tree  = nine_element_tree;
  
  empty_tree         = copied_empty_tree;
  one_element_tree   = copied_one_element_tree;
  three_element_tree = copied_three_element_tree;
  five_element_tree  = copied_five_element_tree;
  nine_element_tree  = copied_nine_element_tree;


  expect(one_element_tree.Root().Element() == 'A');
  
  expect(three_element_tree.Root().LeftChild().Element() == 'B');
  expect(three_element_tree.Root().RightChild().Element() == 'C');
  
  expect(five_element_tree.Root().LeftChild().LeftChild().Element() == 'D');
  expect(five_element_tree.Root().LeftChild().RightChild().Element() == 'E');
  
  expect(nine_element_tree.Root().RightChild().LeftChild().Element() == 'F');
  expect(nine_element_tree.Root().RightChild().RightChild().Element() == 'G');
  expect(nine_element_tree.Root().LeftChild().LeftChild().LeftChild().Element() == 'H');
  expect(nine_element_tree.Root().LeftChild().LeftChild().RightChild().Element() == 'I');
}




void inspection_of_binarytreevec_copies_t3(){
  auto three_element_vec = generate_sample_vector(3);
  auto nine_element_vec  = generate_sample_vector(9);

  auto tree = lasd::BinaryTreeVec<char>{ three_element_vec };
  auto bigger  = lasd::BinaryTreeVec<char> { nine_element_vec };
  tree = bigger;

  expect(tree.Root().Element() == 'A');
  
  expect(tree.Root().LeftChild().Element() == 'B');
  expect(tree.Root().RightChild().Element() == 'C');
  
  expect(tree.Root().LeftChild().LeftChild().Element() == 'D');
  expect(tree.Root().LeftChild().RightChild().Element() == 'E');

  expect(tree.Root().RightChild().LeftChild().Element() == 'F');
  expect(tree.Root().RightChild().RightChild().Element() == 'G');
  expect(tree.Root().LeftChild().LeftChild().LeftChild().Element() == 'H');
  expect(tree.Root().LeftChild().LeftChild().RightChild().Element() == 'I');
}



void inspection_of_binarytreevec_copies_t4(){
  auto three_element_vec = generate_sample_vector(3);
  auto nine_element_vec  = generate_sample_vector(9);

  auto tree = lasd::BinaryTreeVec<char>{ nine_element_vec };
  auto smaller  = lasd::BinaryTreeVec<char> { three_element_vec };
  tree = smaller;

  expect(tree.Root().Element() == 'A');
  
  expect(tree.Root().LeftChild().Element() == 'B');
  expect(tree.Root().RightChild().Element() == 'C');
}



void compare_empty_treevecs(){
  auto atree = lasd::BinaryTreeVec<char>{ generate_sample_vector(0) };
  auto btree = lasd::BinaryTreeVec<char>{ generate_sample_vector(0) };
  expect(atree == btree);
}



void compare_nontrivial_treevecs(){
  auto atree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  auto btree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  expect(atree == btree);
}




void treevec_breadth_fold_map(){ 
  auto tree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  const auto ctree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  std::string concatenation_by_fold;
  std::string concatenation_by_map;
  ctree.BreadthFold([](char c, void* acc){ ((std::string*)acc)->push_back(c); }, &concatenation_by_fold);
  tree.BreadthMap([&concatenation_by_map](char& c){ concatenation_by_map.push_back(c); c = 'X'; });
  tree.BreadthMap([&concatenation_by_map](char c){ concatenation_by_map.push_back(c); });
  expect(concatenation_by_fold == "ABCDEFGHI");
  expect(concatenation_by_map == "ABCDEFGHIXXXXXXXXX");
}




void treevec_preorder_fold_map(){
  auto tree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  const auto ctree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  std::string concatenation_by_fold;
  std::string concatenation_by_map;
  ctree.PreOrderFold([](char c, void* acc){ ((std::string*)acc)->push_back(c); }, &concatenation_by_fold);
  tree.PreOrderMap([&concatenation_by_map](char& c){ concatenation_by_map.push_back(c); c = 'X'; });
  tree.PreOrderMap([&concatenation_by_map](char c){ concatenation_by_map.push_back(c); });
  expect(concatenation_by_fold == "ABDHIECFG");
  expect(concatenation_by_map == "ABDHIECFGXXXXXXXXX");
}



void treevec_postorder_fold_map(){
  auto tree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  const auto ctree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  std::string concatenation_by_fold;
  std::string concatenation_by_map;
  ctree.PostOrderFold([](char c, void* acc){ ((std::string*)acc)->push_back(c); }, &concatenation_by_fold);
  tree.PostOrderMap([&concatenation_by_map](char& c){ concatenation_by_map.push_back(c); c = 'X'; });
  tree.PostOrderMap([&concatenation_by_map](char c){ concatenation_by_map.push_back(c); });
  expect(concatenation_by_fold == "HIDEBFGCA");
  expect(concatenation_by_map == "HIDEBFGCAXXXXXXXXX");
}




void treevec_inorder_fold_map(){
  auto tree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  const auto ctree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  std::string concatenation_by_fold;
  std::string concatenation_by_map;
  ctree.InOrderFold([](char c, void* acc){ ((std::string*)acc)->push_back(c); }, &concatenation_by_fold);
  tree.InOrderMap([&concatenation_by_map](char& c){ concatenation_by_map.push_back(c); c = 'X'; });
  tree.InOrderMap([&concatenation_by_map](char c){ concatenation_by_map.push_back(c); });
  expect(concatenation_by_fold == "HDIBEAFCG");
  expect(concatenation_by_map == "HDIBEAFCGXXXXXXXXX");
}




void check_treevec_sizes_and_clear(){
  expect(lasd::BinaryTreeVec<int>(lasd::Vector<int>(0)).Size() == 0);
  expect(lasd::BinaryTreeVec<int>(lasd::Vector<int>(2)).Size() == 2);
  expect(lasd::BinaryTreeVec<int>(lasd::Vector<int>(7)).Size() == 7);
  expect(lasd::BinaryTreeVec<int>(lasd::Vector<int>(9)).Size() == 9);
  expect(lasd::BinaryTreeVec<int>(lasd::Vector<int>(4)).Size() == 4);
  auto tree = lasd::BinaryTreeVec<char>{ generate_sample_vector(9) };
  auto copied = tree;
  auto moved = std::move(tree);
  expect(copied.Size() == 9);
  expect(moved.Size() == 9);
  copied.Clear();
  moved.Clear();
  expect(copied.Empty());
  expect(moved.Empty());
  expect(copied.Size() == 0);
  expect(moved.Size() == 0);
}



void execute_binarytreevec_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::BinaryTreeVec<T> ↓↓↓ \n");
    UnitTest binarytreevec_test_procedures {
        {"construct_trees_from_mappable_t1",       construct_trees_from_mappable_t1},
        {"construct_trees_from_mappable_t2",       construct_trees_from_mappable_t2},
        {"construct_trees_from_mappable_t3",       construct_trees_from_mappable_t3},
        {"inspection_of_binarytreevec",            inspection_of_binarytreevec},
        {"inspection_of_binarytreevec_copies_t1",  inspection_of_binarytreevec_copies_t1},
        {"inspection_of_binarytreevec_copies_t2",  inspection_of_binarytreevec_copies_t2},
        {"inspection_of_binarytreevec_copies_t3",  inspection_of_binarytreevec_copies_t3},
        {"inspection_of_binarytreevec_copies_t4",  inspection_of_binarytreevec_copies_t4},
        {"compare_empty_treevecs",                 compare_empty_treevecs},
        {"compare_nontrivial_treevecs",            compare_nontrivial_treevecs},
        {"treevec_preorder_fold_map",              treevec_preorder_fold_map},
        {"treevec_postorder_fold_map",             treevec_postorder_fold_map},
        {"treevec_inorder_fold_map",               treevec_inorder_fold_map},
        {"treevec_breadth_fold_map",               treevec_breadth_fold_map},
        {"check_treevec_sizes_and_clear",          check_treevec_sizes_and_clear},
    };
    execute_tests(binarytreevec_test_procedures);  
}