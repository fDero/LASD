
// FRANCESCO DE ROSA N86004379

#include "stresstest.hpp"
#include <cstdlib>
#include <random>
#include <cassert>

void execute_stresstest(){
    
    std::cout << "\n\n" << blue("\t stress testing: repeated operations on lasd containers many many times with random values ");
    std::cout << "\n"   << blue("\t the outcome of these tests vary on runtime-conditions and it's non-deterministic ") << "\n\n";
    std::cout << "\n"   << blue("\t !!!!!!!!!! IF THE TEST SEEMS TO BE STUCK JUST WAIT A COUPLE OF SECONDS !!!!!!!!!!");
    std::cout << "\n"   << blue("\t          ---> IT'S DOING THOUSENDS OF COMPUTATIONS IT TAKES SOME TIME <---") << "\n\n";

    execute_stack_stresstests();
    execute_queue_stresstests();
    execute_binarytree_stresstests();
    execute_bst_stresstests();
    execute_iterators_stresstests();
}

int get_random_value(){
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(-1000,1000);
    return dist(rng);
}

bool random_boolean_by_probability_percentage(unsigned short percentage) {
    assert (percentage >= 0);
    assert (percentage <= 100);
    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<std::mt19937::result_type> dist(0,100);
    int number = dist(rng);
    return (number < percentage) ;
}
