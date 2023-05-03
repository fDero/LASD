
// FRANCESCO DE ROSA N86004379  

#pragma once

#include <map>
#include <functional>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <stdexcept>
#include "../vector/vector.hpp"

using TestProcedure = typename std::function<void(void)>;
using UnitTest = typename std::vector<std::pair<std::string,TestProcedure>>;

void expect(bool condition);

template<typename Exception> void expect_exception(TestProcedure action) {
    try { action(); } catch(const Exception&) { return; }
    throw std::runtime_error("TEST FALLITO");
}

void execute_tests(const UnitTest& tests);
void execute_vector_tests();
void execute_list_tests();
void execute_stack_tests();
void execute_queue_tests();
void execute_sort_tests();
void execute_student_test();
void execute_binarytreelnk_tests();
void execute_binarytreevec_tests();
void execute_bst_tests();
void execute_iterator_tests();

lasd::Vector<char> generate_sample_vector(lasd::sizetype);

std::string bold_red(const std::string& text);
std::string bold_green(const std::string& text);
std::string purple(const std::string& text);
std::string blue(const std::string& text);
