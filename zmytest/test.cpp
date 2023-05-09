
// FRANCESCO DE ROSA N86004379

#include <map>
#include <functional>
#include <string>
#include <stack>
#include <iostream>
#include "test.hpp"
#include "../vector/vector.hpp"




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
    execute_binarytreelnk_tests();
    execute_binarytreevec_tests();
    execute_bst_tests();
    execute_iterator_tests();
}

void execute_test(const std::string& test_name, const TestProcedure& testfunc){
    try { 
        testfunc(); 
        std::cout << bold_green("SUCCESS") << "\t" << purple(test_name);
        std::cout << std::endl << std::endl;
    } 
    catch (...) {
        std::cout << bold_red("FAILURE") << "\t" <<  purple(test_name); 
        std::cout << std::endl << std::endl;
    }
}

void execute_tests(const UnitTest& tests){
    std::cout << "\n";
    for (auto current_test = tests.begin(); current_test != tests.end(); current_test++){
        execute_test(current_test->first, current_test->second);
    }
    std::cout << "\n";
}

lasd::Vector<char> generate_sample_vector(lasd::sizetype size){
  auto vec = lasd::Vector<char>(size);
  for (lasd::sizetype i = 0; i < size; i++) vec[i] = ('A' + i);
  return vec;
}