
# FRANCESCO DE ROSA N86004379

#!/bin/bash

g++ -O3 -std=c++20 -fsanitize=address -o   main                                   \
  main.cpp                                 zcli/menu.cpp                          \
  zmytest/vector_tests.cpp                 zmytest/list_tests.cpp                 \
  zmytest/queue_tests.cpp                  zmytest/stack_tests.cpp                \
  zmytest/test.cpp                         zmytest/sort_tests.cpp                 \
  zmytest/treevec_tests.cpp                zmytest/treelnk_tests.cpp              \
  zmytest/iterator_tests.cpp               zmytest/bst_tests.cpp                  \
  zlasdtest/test.cpp                       zlasdtest/container/container.cpp      \
  zlasdtest/exercise1a/simpletest.cpp      zlasdtest/exercise1a/fulltest.cpp      \
  zlasdtest/exercise1b/simpletest.cpp      zlasdtest/exercise1b/fulltest.cpp      \
  zlasdtest/exercise2b/simpletest.cpp      zlasdtest/exercise2b/fulltest.cpp      \
  zlasdtest/exercise2a/simpletest.cpp      zlasdtest/exercise2a/fulltest.cpp      \
  zlasdtest/exercise3/simpletest.cpp       zlasdtest/exercise3/fulltest.cpp       \
  zstresstest/stresstest.cpp               zstresstest/bst_stresstests.cpp        \
  zstresstest/binarytree_stresstests.cpp   zstresstest/iterator_stresstests.cpp   \
  zstresstest/queue_stresstests.cpp        zstresstest/stack_stresstests.cpp      \
  zstresstest/hashtable_stresstests.cpp                                           \
  zmytest/hashtable_open_addressing_tests.cpp                                     \
  zmytest/hashtable_closed_addressing_tests.cpp                                   \
  