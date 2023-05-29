
// FRANCESCO DE ROSA N86004379

#include "stresstest.hpp"
#include "../zcli/menu.hpp"
#include <cstdlib>
#include <random>
#include <cassert>
#include <iostream>
#include <chrono>
#include <thread>

void execute_student_stresstest(){
    
    std::cout << "\n\t" << blue(" stress testing: repeated operations on lasd containers thousands of times with random values ");
    std::cout << "\n\t" << blue("      the outcome of these tests vary on runtime-conditions and it's non-deterministic        ");

    std::cout << std::endl << std::endl;
    
    std::cout << "\n\t" << yellow("          !! THESE TESTS ARE COMPUTATIONALLY EXPENSIVE, THEY TAKE SOME TIME  !!             ");
    std::cout << "\n\t" << yellow("      IT'S SUGGESTED TO NOT EXECUTE THESE TESTS IF RUNNING VALGRIND OR F-SANITIZER          ");
    std::cout << "\n\t" << yellow("   BECAUSE THE ADDED OVERHEAD OF THESE TOOLS IS ENAUGH TO SLOW THINGS DOWN DRASTICALLY      ");
    
    std::cout << std::endl << std::endl;

    for (int choice = 0; choice != 2; choice = -1) {

        std::cout << "\n ┍━ are you sure?";
        std::cout << "\n │   [1] Yes, Go ahead with stresstesting";
        std::cout << "\n │   [2] Go back to main menu";
        std::cout << "\n └─────────> ";
    
        choice = get_user_choice();
        if (choice != 1 and choice != 2) input_error();
        if (choice == 1) break;
        if (choice == 2) return;
    }

    std::cout << std::endl << std::endl;
    
    execute_stack_stresstests();
    execute_queue_stresstests();
    execute_binarytree_stresstests();
    execute_bst_stresstests();
    execute_iterators_stresstests();
    execute_hashtable_stresstests();
}




void execute_stresstest(const std::string& testname, TestProcedure test){
    std::cout << "\n";

    bool finished = false;
    bool succeded = true;
    
    std::thread test_runner([&succeded, &finished, &test](){ 
        try {
            test();
            succeded = true;
            finished = true;
        } catch(...){
            succeded = false;
            finished = true;
        }
    });
    
    test_runner.detach();
    
    std::string waitingstrings[3];
    waitingstrings[0] = ".  ";
    waitingstrings[1] = ".. ";
    waitingstrings[2] = "...";
    
    for (short i = 0; not finished; ++i %= 3){
        std::cout << bold_yellow("TESTING") << waitingstrings[i] << "         ";
        std::cout.flush();
        std::this_thread::sleep_for(std::chrono::milliseconds(300)); 
        std::cout << "\r";
        std::cout.flush();        
    }
    std::cout << ((succeded)? bold_green("SUCCESS") : bold_red("FAILURE")) << " " << purple(testname) << "\n";
}




void execute_stresstests(UnitTest tests){
    for (auto current_test = tests.begin(); current_test != tests.end(); current_test++){
        execute_stresstest(current_test->first, current_test->second);
    }
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
