
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/foldable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../vector/vector.hpp"


/* This file contains all the tests for the class lasd::Vector<?> defined by the student
-- The tests are actually void procedures without parameters that are sequentially called 
-- one after the other by the procedure 'execute_tests' defined in 'test.cpp'
*/ 


void integer_vector_values_initiaization(){
    auto xs = lasd::Vector<int>(6);
    xs[0] = 0; xs[1] = 1;
    xs[2] = 2; xs[3] = 3;
    xs[4] = 4; xs[5] = 5;

    expect(xs[0] == 0);  expect(xs[1] == 1);
    expect(xs[2] == 2);  expect(xs[3] == 3);
    expect(xs[4] == 4);  expect(xs[5] == 5);
}




void integer_vector_fold_and_map(){
  int sum = 0;
  lasd::Vector<int> xs = lasd::Vector<int>(6);
  xs[0] = 0; xs[1] = 1;
  xs[2] = 2; xs[3] = 3;
  xs[4] = 4; xs[5] = 5;

  xs.Map([](int& value){ value = value * value; });
  xs.Fold([](const int& value, void* accumulator){ (int&)*((int*)accumulator) += value; }, &sum);
  
  expect(xs[0] == 0);
  expect(xs[1] == 1);
  expect(xs[2] == 4);
  expect(xs[3] == 9); 
  expect(xs[4] == 16);
  expect(xs[5] == 25);
  expect(sum == 55);
}





void vector_index_out_of_bounds(){
    expect_exception<std::out_of_range>([](){ 
        lasd::Vector<int> xs = lasd::Vector<int>(10); 
        xs[20] = 0;
    });
}





void empty_vector_front_method_call_t1(){
    expect_exception<std::length_error>([](){ 
        lasd::Vector<int> xs = lasd::Vector<int>(0); 
        xs.Front(); }
    );
}





void empty_vector_front_method_call_t2(){ 
    expect_exception<std::length_error>([](){ 
        lasd::Vector<int> xs = lasd::Vector<int>(); 
        xs.Front(); 
    });
}




void empty_vector_front_method_call_t3(){ 
    expect_exception<std::length_error>([](){ 
        lasd::Vector<int> xs = lasd::Vector<int>(10); 
        xs.Resize(0); 
        xs.Front();
    });
}





void empty_vector_back_method_call_t1(){
    expect_exception<std::length_error>([](){ 
        lasd::Vector<int> xs = lasd::Vector<int>(0);
        xs.Back();
    });
}





void empty_vector_back_method_call_t2(){
    expect_exception<std::length_error>([](){ 
        lasd::Vector<int> xs = lasd::Vector<int>();
        xs.Back();
    });
}





void empty_vector_back_method_call_t3(){
    expect_exception<std::length_error>([](){ 
        lasd::Vector<int> xs = lasd::Vector<int>(10);
        xs.Resize(0);
        xs.Back();
    });
}





void empty_vectors_comparison(){
    lasd::Vector<int> xs;
    lasd::Vector<int> ys;
    expect(xs == ys);
    expect(not (xs != ys));
}





void different_sizes_vector_comparison(){
    lasd::Vector<int> xs = lasd::Vector<int>(5);
    lasd::Vector<int> ys = lasd::Vector<int>(7);
    expect(xs != ys);
    expect(not (xs == ys));
}





void non_trivial_vector_comparison(){
    lasd::Vector<int> xs = lasd::Vector<int>(3);
    lasd::Vector<int> ys = lasd::Vector<int>(3);
    xs[0] = 0; xs[1] = 1; xs[2] = 2;
    ys[0] = 0; ys[1] = 1; ys[2] = 2;
    expect(xs == ys);
    expect(not (xs != ys));
}






void vector_postorder_fold(){
    lasd::Vector<std::string> words = lasd::Vector<std::string>(3);
    words[0] = "aa"; words[1] = "bb"; words[2] = "cc";
    std::string postorder_concatenation;
    auto concatenation = [](const std::string& word, void* accumulator){ *((std::string*)accumulator) += word; };
    words.PostOrderFold(concatenation, &postorder_concatenation);
    expect(postorder_concatenation == "ccbbaa");
}





void vector_preorder_fold(){
    lasd::Vector<std::string> words = lasd::Vector<std::string>(3);
    words[0] = "aa"; words[1] = "bb"; words[2] = "cc";
    std::string preorder_concatenation;
    auto concatenation = [](const std::string& word, void* accumulator){ *((std::string*)accumulator) += word; };
    words.PreOrderFold(concatenation, &preorder_concatenation);
    expect(preorder_concatenation == "aabbcc");
}






void vector_postorder_map(){
    lasd::Vector<std::string> words = lasd::Vector<std::string>(3);
    words[0] = "aa"; words[1] = "bb"; words[2] = "cc";
    std::string post_order_concatenation;
    auto concatenation = [&post_order_concatenation](const std::string& word){ post_order_concatenation += word; };
    words.PreOrderMap(concatenation);
    expect(post_order_concatenation == "aabbcc");
}





void vector_preorder_map(){
    lasd::Vector<std::string> words = lasd::Vector<std::string>(3);
    words[0] = "aa"; words[1] = "bb"; words[2] = "cc";
    std::string post_order_concatenation;
    auto concatenation = [&post_order_concatenation](const std::string& word){ post_order_concatenation += word; };
    words.PreOrderMap(concatenation);
    expect(post_order_concatenation == "aabbcc");
}








void vector_mutable_postorder_map(){
    lasd::Vector<std::string> words = lasd::Vector<std::string>(3);
    words[0] = "aa"; words[1] = "bb"; words[2] = "cc";
    std::string post_order_concatenation;
    auto concatenation = [&post_order_concatenation](std::string& word){ post_order_concatenation += word; word.clear(); };
    words.PostOrderMap(concatenation);
    expect(post_order_concatenation == "ccbbaa");
    expect(words[0].empty());
    expect(words[1].empty());
    expect(words[2].empty());
}





void vector_mutable_preorder_map(){
    lasd::Vector<std::string> words = lasd::Vector<std::string>(3);
    words[0] = "aa"; words[1] = "bb"; words[2] = "cc";
    std::string post_order_concatenation;
    auto concatenation = [&post_order_concatenation](std::string& word){ post_order_concatenation += word; word.clear(); };
    words.PreOrderMap(concatenation);
    expect(post_order_concatenation == "aabbcc");
    expect(words[0].empty());
    expect(words[1].empty());
    expect(words[2].empty());
}





void vector_sort_test(){
    lasd::Vector<int> numbers = lasd::Vector<int>(4);
    numbers[0] = 8;  numbers[1] = 7;
    numbers[2] = 9;  numbers[3] = 0;
    numbers.Sort();
    expect(numbers[0] == 0); expect(numbers[1] == 7);
    expect(numbers[2] == 8); expect(numbers[3] == 9);
}





void vector_resize_t1(){
    lasd::Vector<int> numbers = lasd::Vector<int>(4);
    numbers[0] = 8;  numbers[1] = 7;
    numbers[2] = 9;  numbers[3] = 0;
    numbers.Resize(3);
    expect(numbers.Back() == 9);
    numbers.Resize(2);
    expect(numbers.Back() == 7);
    numbers.Resize(1);
    expect(numbers.Back() == 8);
    numbers.Resize(0);
    expect(numbers.Size() == 0);
}




void vector_resize_t1(){
    lasd::Vector<int> numbers = lasd::Vector<int>(4);
    numbers[0] = 8;  numbers[1] = 7;
    numbers[2] = 9;  numbers[3] = 0;
    numbers.Resize(3);
 
}

void execute_vector_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::Vector<T> ↓↓↓ \n");
    UnitTest vector_test_procedures {
       {"integer_vector_values_initiaization", integer_vector_values_initiaization}, 
       {"integer_vector_fold_and_map",         integer_vector_fold_and_map},
       {"vector_index_out_of_bounds",          vector_index_out_of_bounds},
       {"empty_vector_front_method_call_t1",   empty_vector_front_method_call_t1},
       {"empty_vector_front_method_call_t2",   empty_vector_front_method_call_t2},
       {"empty_vector_front_method_call_t3",   empty_vector_front_method_call_t3},
       {"empty_vector_back_method_call_t1",    empty_vector_back_method_call_t1},
       {"empty_vector_back_method_call_t2",    empty_vector_back_method_call_t2},
       {"empty_vector_back_method_call_t3",    empty_vector_back_method_call_t3},
       {"empty_vectors_comparison",            empty_vectors_comparison},
       {"different_sizes_vector_comparison",   different_sizes_vector_comparison},
       {"non_trivial_vector_comparison",       non_trivial_vector_comparison},
       {"vector_postorder_fold",               vector_postorder_fold},
       {"vector_preorder_fold",                vector_preorder_fold},
       {"vector_postorder_map",                vector_postorder_map},
       {"vector_preorder_map",                 vector_preorder_map},
       {"vector_mutable_postorder_map",        vector_mutable_postorder_map},
       {"vector_mutable_preorder_map",         vector_mutable_preorder_map},
       {"vector_sort_test",                    vector_sort_test},
       {"vector_resize_t1",                    vector_resize_t1},
    };
    execute_tests(vector_test_procedures);  
}