
#! /bin/bash

g++  -std=c++17  -o student_tests_bin.out zmytest/main.cpp  zmytest/test.cpp \
 zmytest/vector_tests.cpp zmytest/list_tests.cpp zmytest/stack_tests_vec.cpp && ./student_tests_bin.out && rm student_tests_bin.out