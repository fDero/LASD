
#! /bin/bash

g++ -O3 -std=c++20 -o main main.cpp                                        \
  zmytest/vector_tests.cpp              zmytest/list_tests.cpp             \
  zmytest/queue_tests.cpp               zmytest/stack_tests.cpp            \
  zmytest/test.cpp                      zmytest/sort_tests.cpp             \
  zlasdtest/test.cpp                    zlasdtest/container/container.cpp  \
  zlasdtest/exercise1a/simpletest.cpp   zlasdtest/exercise1a/fulltest.cpp  \
  zlasdtest/exercise1b/simpletest.cpp   zlasdtest/exercise1b/fulltest.cpp  \