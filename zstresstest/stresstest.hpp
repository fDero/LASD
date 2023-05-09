
// FRANCESCO DE ROSA N86004379  

#pragma once

#include <map>
#include <functional>
#include <string>
#include <vector>
#include <stack>
#include <iostream>
#include <stdexcept>
#include "../zmytest/test.hpp"

int  get_random_value();
bool random_boolean_by_probability_percentage(unsigned short);

void execute_stresstest();
void execute_stack_stresstests();
void execute_queue_stresstests();
void execute_binarytree_stresstests();
void execute_bst_stresstests();
void execute_iterators_stresstests();