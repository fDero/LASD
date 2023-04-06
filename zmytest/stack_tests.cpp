
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/foldable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../stack/stack.hpp"
#include "../stack/lst/stacklst.hpp"


/* This file contains all the tests for the class lasd::StackVec<?> and lasd::StackLst<?> defined by the student
-- The tests are actually void procedures without parameters that are sequentially called 
-- one after the other by the procedure 'execute_tests' defined in 'test.cpp'
*/ 


void empty_stacklst(){
    auto empty = lasd::StackLst<std::string>();
    expect(empty.Empty());
}




void stacklst_initialization(){
    auto stack = lasd::StackLst<std::string>();
    stack.Push("aa");
    stack.Push("bb");
    stack.Push("cc");
    expect(stack.Size() == 3);
}





void stacklst_pop_top_test(){
    auto stack = lasd::StackLst<std::string>();
    stack.Push("aa");
    stack.Push("bb");
    stack.Push("cc");
    expect(stack.TopNPop() == "cc");
    expect(stack.TopNPop() == "bb");
    expect(stack.TopNPop() == "aa");
    expect(stack.Empty());
}




void stacklst_comparison(){
    auto xs = lasd::StackLst<std::string>();
    xs.Push("aa"); 
    xs.Push("bb"); 
    xs.Push("cc");
    auto ys = lasd::StackLst<std::string>();
    ys.Push("aa"); 
    ys.Push("bb"); 
    ys.Push("cc");
    expect(xs == ys);
    expect(not (xs != ys));
    expect(xs.TopNPop() == ys.TopNPop());
    expect(xs == ys);
    expect(not (xs != ys));
    ys = xs;
}




void stacklst_map_fold(){
    auto words = lasd::StackLst<std::string>();
    words.Push("aa"); 
    words.Push("bb"); 
    words.Push("cc");

    std::string concatenation;
    words.Map([](std::string& word){ word[0] = 'x'; });
    words.PreOrderFold([](const std::string& word, void* concatenation){ *((std::string*)concatenation) += word; }, &concatenation);

    expect(words.TopNPop() == "xc");
    expect(words.TopNPop() == "xb");
    expect(words.TopNPop() == "xa");
    expect(concatenation == "xcxbxa");
}





void execute_stack_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::StackLst<T> and lasd::StackVec<T> ↓↓↓ \n");
    UnitTest stack_test_procedures {
        {"empty_stacklst",              empty_stacklst},
        {"stacklst_initialization",     stacklst_initialization},
        {"stacklst_pop_top_test",       stacklst_pop_top_test},
        {"stacklst_comparison",         stacklst_comparison},
        {"stacklst_map_fold",           stacklst_map_fold},
    };
    execute_tests(stack_test_procedures);  
}