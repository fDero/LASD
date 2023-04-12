
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/foldable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../stack/stack.hpp"
#include "../stack/lst/stacklst.hpp"
#include "../stack/vec/stackvec.hpp"


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




void empty_stackvec(){
    auto empty = lasd::StackVec<std::string>();
    expect(empty.Empty());
    expect(empty.Size() == 0);
}




void first_stackvec_push(){
    auto stack = lasd::StackVec<std::string>();
    stack.Push("x");
    expect(not stack.Empty());
    expect(stack.Size() == 1);
    expect(stack.Top() == "x");
}




void first_stackvec_pop(){
    auto stack = lasd::StackVec<std::string>();
    stack.Push("x");
    stack.Pop();
    expect(stack.Empty());
    expect(stack.Size() == 0);
}




void ten_stackvec_push(){
    auto stack = lasd::StackVec<std::string>();
    stack.Push("01");  stack.Push("02");
    stack.Push("03");  stack.Push("04");
    stack.Push("05");  stack.Push("06");
    stack.Push("07");  stack.Push("08");
    stack.Push("09");  stack.Push("10");
    expect(stack.Size() == 10);
    expect(stack.TopNPop() == "10");
    expect(stack.TopNPop() == "09");
    expect(stack.TopNPop() == "08");
    expect(stack.Size() == 7);
    expect(stack.TopNPop() == "07");
    expect(stack.TopNPop() == "06");
    expect(stack.TopNPop() == "05");
    expect(stack.Size() == 4);
    expect(stack.TopNPop() == "04");
    expect(stack.TopNPop() == "03");
    expect(stack.TopNPop() == "02");
    expect(stack.Size() == 1);
    expect(stack.TopNPop() == "01");
    expect(stack.Empty());
    expect(stack.Size() == 0);
}




void stackvec_multiple_pushes(){
    auto stack = lasd::StackVec<std::string>();
    stack.Push("01");  stack.Push("02");
    stack.Push("03");  stack.Push("04");
    stack.Push("05");  stack.Push("06");
    stack.Push("07");  stack.Push("08");
    stack.Push("09");  stack.Push("10");
    expect(stack.Size() == 10);
    expect(stack.TopNPop() == "10");
    expect(stack.TopNPop() == "09");
    expect(stack.TopNPop() == "08");
    expect(stack.Size() == 7);
    expect(stack.TopNPop() == "07");
    expect(stack.TopNPop() == "06");
    expect(stack.TopNPop() == "05");
    expect(stack.Size() == 4);
    stack.Push("05");
    stack.Push("06");
    stack.Push("07");
    expect(stack.TopNPop() == "07");
    expect(stack.TopNPop() == "06");
    expect(stack.TopNPop() == "05");
    expect(stack.Size() == 4);
    expect(stack.TopNPop() == "04");
    expect(stack.TopNPop() == "03");
    expect(stack.TopNPop() == "02");
    expect(stack.Size() == 1);
    expect(stack.TopNPop() == "01");
    expect(stack.Empty());
    expect(stack.Size() == 0);
}




void stackvec_non_trivial_comparison(){
    auto xs = lasd::StackVec<int>();
    auto ys = lasd::StackVec<int>();
    xs.Push(1);  xs.Push(2);
    xs.Push(3);  xs.Push(4);
    ys.Push(1);  ys.Push(2);
    ys.Push(3);  ys.Push(4);
    expect(xs == ys);
    xs.Push(5); xs.Push(6);
    xs.Push(7); xs.Push(8);
    expect(xs != ys);
    xs.Pop();   xs.Pop();
    xs.Pop();   xs.Pop();
    expect(xs == ys);
    xs.Resize(15);
    expect(xs == ys);
}




void stackvec_assignments_t1(){
    auto xs = lasd::StackVec<int>();
    auto ys = lasd::StackVec<int>();
    auto zs = lasd::StackVec<int>();
    xs.Push(1);  xs.Push(2);
    xs.Push(3);  xs.Push(4);
    ys = xs;
    expect(ys == xs);
    zs = std::move(xs);
    expect(ys == zs);
}




void stackvec_assignments_t2(){
    auto xs = lasd::StackVec<int>();
    auto ys = xs;
    auto zs = std::move(ys);
    expect(ys == xs);
    expect(ys == zs);
}




void stackvec_constructors_t1(){
    auto xs = lasd::StackVec<int>();
    auto ys = lasd::StackVec<int>();
    auto zs = lasd::StackVec<int>();
    xs.Push(1);  xs.Push(2);
    xs.Push(3);  xs.Push(4);
    ys = lasd::StackVec<int>(xs);
    expect(ys == xs);
    zs = lasd::StackVec<int>(std::move(xs));
    expect(ys == zs);
}



void stackvec_constructors_t2(){
    auto xs = lasd::StackVec<int>();
    auto ys = lasd::StackVec<int>(xs);
    auto zs = lasd::StackVec<int>(std::move(ys));
    expect(ys == xs);
    expect(ys == zs);
}





void stackvec_constructors_t3(){
    auto ys = lasd::Vector<int>(3); 
    ys[0] = 0; ys[1] = 1; ys[2] = 2;
    auto xs = lasd::StackVec<int>(ys);
}




void execute_stack_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::StackLst<T> and lasd::StackVec<T> ↓↓↓ \n");
    UnitTest stack_test_procedures {
        {"empty_stacklst",                  empty_stacklst},
        {"stacklst_initialization",         stacklst_initialization},
        {"stacklst_pop_top_test",           stacklst_pop_top_test},
        {"stacklst_comparison",             stacklst_comparison},
        {"stacklst_map_fold",               stacklst_map_fold},
        {"empty_stackvec",                  empty_stackvec},
        {"first_stackvec_push",             first_stackvec_push},
        {"first_stackvec_pop",              first_stackvec_pop},
        {"ten_stackvec_push",               ten_stackvec_push},
        {"stackvec_multiple_pushes",        stackvec_multiple_pushes},
        {"stackvec_non_trivial_comparison", stackvec_non_trivial_comparison},
        {"stackvec_assignments_t1",         stackvec_assignments_t1},
        {"stackvec_assignments_t2",         stackvec_assignments_t2},
        {"stackvec_constructors_t1",        stackvec_constructors_t1},
        {"stackvec_constructors_t2",        stackvec_constructors_t2},
        {"stackvec_constructors_t3",        stackvec_constructors_t3},
    };
    execute_tests(stack_test_procedures);  
}