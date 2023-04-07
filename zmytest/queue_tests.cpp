
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../container/container.hpp"
#include "../container/testable.hpp"
#include "../container/foldable.hpp"
#include "../container/mappable.hpp"
#include "../container/linear.hpp"
#include "../queue/queue.hpp"
#include "../queue/lst/queuelst.hpp"
#include "../queue/vec/queuevec.hpp"


/* This file contains all the tests for the class lasd::QueueVec<?> and lasd::QueueLst<?> defined by the student
-- The tests are actually void procedures without parameters that are sequentially called 
-- one after the other by the procedure 'execute_tests' defined in 'test.cpp'
*/ 

void empty_queuelst(){
    auto empty = lasd::QueueLst<std::string>();
    expect(empty.Empty());
}




void queuelst_initialization(){
    auto queue = lasd::QueueLst<std::string>();
    queue.Enqueue("aa");
    queue.Enqueue("bb");
    queue.Enqueue("cc");
    expect(queue.Size() == 3);
}





void queuelst_pop_top_test(){
    auto queue = lasd::QueueLst<std::string>();
    queue.Enqueue("aa");
    queue.Enqueue("bb");
    queue.Enqueue("cc");
    expect(queue.HeadNDequeue() == "aa");
    expect(queue.HeadNDequeue() == "bb");
    expect(queue.HeadNDequeue() == "cc");
    expect(queue.Empty());
}




void queuelst_comparison(){
    auto xs = lasd::QueueLst<std::string>();
    xs.Enqueue("aa"); 
    xs.Enqueue("bb"); 
    xs.Enqueue("cc");
    auto ys = lasd::QueueLst<std::string>();
    ys.Enqueue("aa"); 
    ys.Enqueue("bb"); 
    ys.Enqueue("cc");
    expect(xs == ys);
    expect(not (xs != ys));
    expect(xs.HeadNDequeue() == ys.HeadNDequeue());
    expect(xs == ys);
    expect(not (xs != ys));
}




void queuelst_map_fold(){
    auto words = lasd::QueueLst<std::string>();
    words.Enqueue("aa"); 
    words.Enqueue("bb"); 
    words.Enqueue("cc");

    std::string concatenation;
    words.Map([](std::string& word){ word[0] = 'x'; });
    words.PreOrderFold([](const std::string& word, void* concatenation){ *((std::string*)concatenation) += word; }, &concatenation);

    expect(words.HeadNDequeue() == "xa");
    expect(words.HeadNDequeue() == "xb");
    expect(words.HeadNDequeue() == "xc");
    expect(concatenation == "xaxbxc");
}




void empty_queuevec(){
    auto empty = lasd::QueueVec<std::string>();
    expect(empty.Empty());
}




void queuevec_initialization(){
    auto queue = lasd::QueueVec<std::string>();
    queue.Enqueue("aa");
    queue.Enqueue("bb");
    queue.Enqueue("cc");
    expect(queue.Size() == 3);
}



void queuevec_pop_top_test(){
    auto queue = lasd::QueueVec<std::string>();
    queue.Enqueue("aa");
    queue.Enqueue("bb");
    queue.Enqueue("cc");
    expect(queue.HeadNDequeue() == "aa");
    expect(queue.HeadNDequeue() == "bb");
    expect(queue.HeadNDequeue() == "cc");
    expect(queue.Empty());
}




void queuevec_comparison(){
    auto xs = lasd::QueueVec<std::string>();
    xs.Enqueue("aa"); 
    xs.Enqueue("bb"); 
    xs.Enqueue("cc");
    auto ys = lasd::QueueVec<std::string>();
    ys.Enqueue("aa"); 
    ys.Enqueue("bb"); 
    ys.Enqueue("cc");
    expect(xs == ys);
    expect(not (xs != ys));
    expect(xs.HeadNDequeue() == ys.HeadNDequeue());
    expect(xs == ys);
    expect(not (xs != ys));
}




void queuevec_map_fold(){
    auto words = lasd::QueueVec<std::string>();
    words.Enqueue("aa"); 
    words.Enqueue("bb"); 
    words.Enqueue("cc");

    std::string concatenation;
    words.Map([](std::string& word){ word[0] = 'x'; });
    words.PreOrderFold([](const std::string& word, void* concatenation){ *((std::string*)concatenation) += word; }, &concatenation);

    expect(words.HeadNDequeue() == "xa");
    expect(words.HeadNDequeue() == "xb");
    expect(words.HeadNDequeue() == "xc");
    expect(concatenation == "xaxbxc");
}




void queuevec_multiple_enqueues(){
    auto queue = lasd::QueueVec<std::string>();
    queue.Enqueue("aa");
    queue.Enqueue("bb");
    queue.Enqueue("cc");
    expect(queue.HeadNDequeue() == "aa");
    expect(queue.Size() == 2);
    queue.Enqueue("dd");
    queue.Enqueue("ee");
    queue.Enqueue("ff");
    expect(queue.Size() == 5);
    expect(queue.HeadNDequeue() == "bb");
    expect(queue.Size() == 4);
    queue.Enqueue("gg");
    queue.Enqueue("hh");
    queue.Enqueue("ii");
    queue.Enqueue("ll");
    expect(queue.HeadNDequeue() == "cc");
    expect(queue.HeadNDequeue() == "dd");
    expect(queue.Size() == 6);
    expect(queue.HeadNDequeue() == "ee");
    expect(queue.HeadNDequeue() == "ff");
    expect(queue.HeadNDequeue() == "gg");
    queue.Enqueue("mm");
    expect(queue.HeadNDequeue() == "hh");
    expect(queue.HeadNDequeue() == "ii");
    expect(queue.Size() == 2);
    expect(queue.HeadNDequeue() == "ll");
    expect(queue.HeadNDequeue() == "mm");
    expect(queue.Size() == 0);
    expect(queue.Empty());
}




void queuevec_more_enqueues(){
    auto queue = lasd::QueueVec<std::string>();
    queue.Enqueue("aa");
    queue.Enqueue("bb");
    queue.Enqueue("cc");
    expect(queue.HeadNDequeue() == "aa");
    expect(queue.Size() == 2);
    queue.Enqueue("dd");
    queue.Enqueue("ee");
    queue.Enqueue("ff");
    expect(queue.Size() == 5);
    expect(queue.HeadNDequeue() == "bb");
    expect(queue.Size() == 4);
    queue.Enqueue("gg");
    queue.Enqueue("hh");
    queue.Enqueue("ii");
    queue.Enqueue("ll");
    queue.Enqueue("mm");
    queue.Enqueue("nn");
    queue.Enqueue("oo");
    expect(queue.HeadNDequeue() == "cc");
    expect(queue.HeadNDequeue() == "dd");
    expect(queue.Size() == 9);
    expect(queue.HeadNDequeue() == "ee");
    expect(queue.HeadNDequeue() == "ff");
    expect(queue.HeadNDequeue() == "gg");
    queue.Enqueue("pp");
    expect(queue.HeadNDequeue() == "hh");
    expect(queue.HeadNDequeue() == "ii");
    expect(queue.Size() == 5);
    expect(queue.HeadNDequeue() == "ll");
    expect(queue.HeadNDequeue() == "mm");
    expect(queue.Size() == 3);
    expect(queue.HeadNDequeue() == "nn");
    expect(queue.HeadNDequeue() == "oo");
    expect(queue.HeadNDequeue() == "pp");
    expect(queue.Size() == 0);
}




void execute_queue_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::QueueLst<T> and lasd::QueueVec<T> ↓↓↓ \n");
    UnitTest stack_test_procedures {
        {"empty_queuelst",              empty_queuelst},
        {"queuelst_initialization",     queuelst_initialization},
        {"queuelst_pop_top_test",       queuelst_pop_top_test},
        {"queuelst_comparison",         queuelst_comparison},
        {"queuelst_map_fold",           queuelst_map_fold},
        {"empty_queuevec",              empty_queuevec},
        {"queuevec_initialization",     queuevec_initialization},
        {"queuevec_pop_top_test",       queuelst_pop_top_test},
        {"queuevec_comparison",         queuevec_comparison},
        {"queuevec_map_fold",           queuevec_map_fold},
        {"queuevec_multiple_enqueues",  queuevec_multiple_enqueues},
        {"queuevec_more_enqueues",      queuevec_more_enqueues},
    };
    execute_tests(stack_test_procedures);  
}