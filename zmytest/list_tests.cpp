
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/foldable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../container/dictionary.hpp"
#include "../list/list.hpp"

/* This file contains all the tests for the class lasd::List<?> defined by the student
-- The tests are actually void procedures without parameters that are sequentially called 
-- one after the other by the procedure 'execute_tests' defined in 'test.cpp'
*/ 


void empty_list_allocation(){
    lasd::List<int> xs = lasd::List<int>();
    expect(xs.Size() == 0);
    expect(not xs.Exists(5));
}




void list_back_insertions(){
    lasd::List<int> xs = lasd::List<int>();
    xs.InsertAtBack(1);
    xs.InsertAtBack(2);
    xs.InsertAtBack(3);
    expect(xs.Size() == 3);
}





void list_access_by_index(){
    lasd::List<int> xs = lasd::List<int>();
    xs.InsertAtBack(1);
    xs.InsertAtBack(2);
    xs.InsertAtBack(3);
    expect(xs[0] == 1);
    expect(xs[1] == 2);
    expect(xs[2] == 3);
}





void list_front_back_use(){
    lasd::List<int> xs = lasd::List<int>();
    xs.InsertAtBack(1);
    xs.InsertAtBack(2);
    xs.InsertAtBack(3);
    expect(xs.Front() == 1);
    expect(xs.Back() == 3);
}




void list_index_out_bounds_t1(){
    expect_exception<std::out_of_range>([](){
        lasd::List<int> xs = lasd::List<int>();
        xs.InsertAtBack(1);
        xs.InsertAtBack(2);
        xs.InsertAtBack(3);
        xs[25] = 10;
    });
}





void list_index_out_bounds_t2(){
    expect_exception<std::out_of_range>([](){
        lasd::List<int> xs = lasd::List<int>();
        xs.InsertAtBack(1);
        xs.InsertAtBack(2);
        xs.InsertAtBack(3);
        xs[-10] = 10;
    });
}




void list_index_out_bounds_t3(){
    expect_exception<std::out_of_range>([](){
        lasd::List<int> xs = lasd::List<int>();
        xs[0] = 10;
    });
}





void empty_list_front_method(){
    expect_exception<std::length_error>([](){
        lasd::List<int> xs = lasd::List<int>();
        xs.Front() = 10;
    });
}





void empty_list_back_method(){
    expect_exception<std::length_error>([](){
        lasd::List<int> xs = lasd::List<int>();
        xs.Back() = 10;
    });
}





void list_preorder_fold(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    std::string preorder_concatenated_words;
    auto concatenation = [](const std::string& word,void* accumulator) { *((std::string*)accumulator) += word; };
    words.PreOrderFold(concatenation, &preorder_concatenated_words);
    expect(preorder_concatenated_words == "aabbcc");
}





void list_postorder_fold(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    std::string postorder_concatenated_words;
    auto concatenation = [](const std::string& word,void* accumulator) { *((std::string*)accumulator) += word; };
    words.PostOrderFold(concatenation, &postorder_concatenated_words);
    expect(postorder_concatenated_words == "ccbbaa");
}





void list_preorder_map(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    std::string preorder_concatenated_words;
    auto concatenation = [&preorder_concatenated_words](const std::string& word) { preorder_concatenated_words += word; };
    words.PreOrderMap(concatenation);
    expect(preorder_concatenated_words == "aabbcc");
}





void list_postorder_map(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    std::string postorder_concatenated_words;
    auto concatenation = [&postorder_concatenated_words](const std::string& word) { postorder_concatenated_words += word; };
    words.PostOrderMap(concatenation);
    expect(postorder_concatenated_words == "ccbbaa");
}






void list_preorder_mutable_map(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    std::string preorder_concatenated_words;
    auto concatenation = [&preorder_concatenated_words](std::string& word) { preorder_concatenated_words += word; word.clear(); };
    words.PreOrderMap(concatenation);
    expect(preorder_concatenated_words == "aabbcc");
    expect(words.Front().empty());
    expect(words[2].empty());
    expect(words.Front().empty());
}





void list_postorder_mutable_map(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    std::string postorder_concatenated_words;
    auto concatenation = [&postorder_concatenated_words](std::string& word) { postorder_concatenated_words += word; word.clear(); };
    words.PostOrderMap(concatenation);
    expect(postorder_concatenated_words == "ccbbaa");
    expect(words.Front().empty());
    expect(words[2].empty());
    expect(words.Front().empty());
}








void list_insert_dictionary_test(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    expect(not words.Insert("aa"));
    expect(words.Insert("dd"));
    expect(words.Size() == 4);
}






void list_remove_dictionary_test(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    expect(not words.Remove("dd"));
    expect(words.Remove("aa"));
    expect(words.Size() == 2);
}





void list_insert_front_test(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    words.InsertAtFront("xx");
    expect(words.Front() == "xx");
    expect(words.Size() == 4);
}





void list_clear_t1(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.Clear();
    expect(words.Size() == 0);
    expect(words.Empty());  
}





void list_remove_back_t1(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    words.RemoveFromBack();
    expect(words.Size() == 2);
    expect(words.Back() == "bb");
}





void list_remove_back_t2(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.RemoveFromBack();
    expect(words.Size() == 0);
    expect(words.Empty());
}





void list_remove_back_t3(){
    expect_exception<std::length_error>([](){
        lasd::List<std::string> words = lasd::List<std::string>();
        words.RemoveFromBack();    
    });
}





void list_remove_front_t1(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.InsertAtBack("bb");
    words.InsertAtBack("cc");
    words.RemoveFromFront();
    expect(words.Size() == 2);
    expect(words.Front() == "bb");
}





void list_remove_front_t2(){
    lasd::List<std::string> words = lasd::List<std::string>();
    words.InsertAtBack("aa");
    words.RemoveFromFront();
    expect(words.Size() == 0);
    expect(words.Empty());
}




void list_remove_front_t3(){
    expect_exception<std::length_error>([](){
        lasd::List<std::string> words = lasd::List<std::string>();
        words.RemoveFromFront();    
    });
}




void list_insert_all_t1(){
    lasd::List<int> values = lasd::List<int>();
    values.InsertAtBack(7);
    values.InsertAtBack(8);
    values.InsertAtBack(9);
    lasd::List<int> destination = lasd::List<int>();
    destination.InsertAtBack(5);
    destination.InsertAtBack(6);
    expect(destination.InsertAll(values));
    expect(destination.Size() == 5);
}




void list_insert_all_t2(){
    lasd::List<int> values = lasd::List<int>();
    values.InsertAtBack(7);
    values.InsertAtBack(8);
    values.InsertAtBack(9);
    lasd::List<int> destination = lasd::List<int>();
    destination.InsertAtBack(8);
    destination.InsertAtBack(9);
    expect(not destination.InsertAll(values));
    expect(destination.Size() == 3);
}




void list_insert_all_t3(){
    lasd::List<int> values = lasd::List<int>();
    values.InsertAtBack(7);
    values.InsertAtBack(8);
    values.InsertAtBack(9);
    lasd::List<int> destination = lasd::List<int>();
    destination.InsertAtBack(0);
    destination.InsertAtBack(9);
    expect(not destination.InsertAll(values));
    expect(destination.Size() == 4);
}




void list_insert_some_t1(){
    lasd::List<int> values = lasd::List<int>();
    values.InsertAtBack(7);
    values.InsertAtBack(8);
    values.InsertAtBack(9);
    lasd::List<int> destination = lasd::List<int>();
    destination.InsertAtBack(5);
    destination.InsertAtBack(6);
    expect(destination.InsertSome(values));
    expect(destination.Size() == 5);
}





void list_insert_some_t2(){
    lasd::List<int> values = lasd::List<int>();
    values.InsertAtBack(8);
    values.InsertAtBack(9);
    lasd::List<int> destination = lasd::List<int>();
    destination.InsertAtBack(8);
    destination.InsertAtBack(9);
    expect(not destination.InsertSome(values));
    expect(destination.Size() == 2);
}




void list_insert_some_t3(){
    lasd::List<int> values = lasd::List<int>();
    values.InsertAtBack(7);
    values.InsertAtBack(8);
    values.InsertAtBack(9);
    lasd::List<int> destination = lasd::List<int>();
    destination.InsertAtBack(0);
    destination.InsertAtBack(9);
    expect(destination.InsertSome(values));
    expect(destination.Size() == 4);
}




void execute_list_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::List<T> ↓↓↓ \n");
    UnitTest list_test_procedures {
       {"empty_list_allocation",        empty_list_allocation}, 
       {"list_back_insertions",         list_back_insertions},
       {"list_access_by_index",         list_access_by_index},
       {"list_front_back_use",          list_front_back_use},
       {"list_index_out_bounds_t1",     list_index_out_bounds_t1},
       {"list_index_out_bounds_t2",     list_index_out_bounds_t2},
       {"list_index_out_bounds_t3",     list_index_out_bounds_t3},
       {"empty_list_front_method",      empty_list_front_method},
       {"empty_list_back_method",       empty_list_back_method},
       {"list_preorder_fold",           list_preorder_fold},
       {"list_postorder_fold",          list_postorder_fold},
       {"list_preorder_map",            list_preorder_map},
       {"list_postorder_map",           list_postorder_map},
       {"list_preorder_mutable_map",    list_preorder_mutable_map},
       {"list_postorder_mutable_map",   list_postorder_mutable_map},
       {"list_insert_dictionary_test",  list_insert_dictionary_test},
       {"list_remove_dictionary_test",  list_remove_dictionary_test},
       {"list_insert_front_test",       list_insert_front_test},
       {"list_clear_t1",                list_clear_t1},
       {"list_remove_back_t1",          list_remove_back_t1},
       {"list_remove_back_t2",          list_remove_back_t2},
       {"list_remove_back_t3",          list_remove_back_t3},
       {"list_remove_front_t1",         list_remove_front_t1},
       {"list_remove_front_t2",         list_remove_front_t2},
       {"list_insert_all_t1",           list_insert_all_t1},
       {"list_insert_all_t2",           list_insert_all_t2},
       {"list_insert_all_t3",           list_insert_all_t3},
       {"list_insert_some_t1",          list_insert_some_t1},
       {"list_insert_some_t2",          list_insert_some_t2},
       {"list_insert_some_t3",          list_insert_some_t3},
    };
    execute_tests(list_test_procedures);  
}