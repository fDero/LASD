
#! /bin/bash

g++  -std=c++17  -o test zmytest/main.cpp  zmytest/test.cpp \
 zmytest/vector_tests.cpp zmytest/list_tests.cpp && ./test && rm test