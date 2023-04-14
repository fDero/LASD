
// FRANCESCO DE ROSA N86004379

#include <map>
#include <functional>
#include <string>
#include <stack>
#include <iostream>
#include "test.hpp"




void expect(bool condition){ if (not condition) throw std::runtime_error("TEST FALLITO"); }


std::string bold_red(const std::string& text)   { return std::string("\e[1;31m") + text + std::string("\e[0;0m"); }
std::string bold_green(const std::string& text) { return std::string("\e[1;32m") + text + std::string("\e[0;0m"); }
std::string purple(const std::string& text)     { return std::string("\e[0;35m") + text + std::string("\e[0;0m"); }
std::string blue(const std::string& text)       { return std::string("\e[0;34m") + text + std::string("\e[0;0m"); }


void execute_student_test(){
    execute_vector_tests();
    execute_list_tests();
    execute_stack_tests();
    execute_queue_tests();
    execute_sort_tests();
}

void execute_tests(const UnitTest& tests){
    for (auto current_test = tests.begin(); current_test != tests.end(); current_test++){
        try {current_test->second();} catch (...) {
            std::cout << "\n\n" << bold_red("FAILURE") << "\t" <<  purple(current_test->first); 
            continue;
        }
        std::cout << "\n\n" << bold_green("SUCCESS") << "\t" << purple(current_test->first);
    }
    std::cout << std::endl << std::endl;
}