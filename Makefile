
# FRANCESCO DE ROSA N86004379

.PHONY: sanitize-build build deploy clean

FILES = main.cpp build.sh Makefile
DIRECTORIES = \
	container list queue stack vector   \
	binarytree bst iterator hashtable   \
	zbinaries zmytest zlasdtest         \
	zcli zstresstest                    \
	

ZMYTEST = \
	zmytest/vector_tests.cpp   zmytest/list_tests.cpp     \
    zmytest/queue_tests.cpp    zmytest/stack_tests.cpp    \
    zmytest/test.cpp           zmytest/sort_tests.cpp     \
	zmytest/treelnk_tests.cpp  zmytest/treevec_tests.cpp  \
	zmytest/bst_tests.cpp      zmytest/iterator_tests.cpp \
	zmytest/hashtable_closed_addressing_tests.cpp         \
	zmytest/hashtable_open_addressing_tests.cpp           \

ZLASDTEST = \
	zlasdtest/test.cpp                    zlasdtest/container/container.cpp  \
	zlasdtest/exercise1a/simpletest.cpp   zlasdtest/exercise1a/fulltest.cpp  \
	zlasdtest/exercise1b/simpletest.cpp   zlasdtest/exercise1b/fulltest.cpp  \
	zlasdtest/exercise2a/simpletest.cpp   zlasdtest/exercise2a/fulltest.cpp  \
	zlasdtest/exercise2b/simpletest.cpp   zlasdtest/exercise2b/fulltest.cpp  \
	zlasdtest/exercise3/simpletest.cpp    zlasdtest/exercise3/fulltest.cpp   \

ZSTRESSTEST = \
	zstresstest/stresstest.cpp             zstresstest/iterator_stresstests.cpp \
	zstresstest/binarytree_stresstests.cpp zstresstest/bst_stresstests.cpp      \
	zstresstest/stack_stresstests.cpp      zstresstest/queue_stresstests.cpp    \
	zstresstest/hashtable_stresstests.cpp  


build:
	@ g++ -std=c++20 -o main -O1 ${ZMYTEST} ${ZLASDTEST} ${ZSTRESSTEST} zcli/menu.cpp main.cpp

sanitize-build:
	@ g++ -std=c++20 -fsanitize=address -o sanitizedmain -O3 ${ZMYTEST} ${ZLASDTEST} ${ZSTRESSTEST} zcli/menu.cpp main.cpp

clang-build:
	@ clang++ -std=c++20 -o main -O1 ${ZMYTEST} ${ZLASDTEST} ${ZSTRESSTEST} zcli/menu.cpp main.cpp


deploy:
	@ make build 
	@ make sanitize-build
	@ mv main zbinaries/precompiled_main
	@ mv sanitizedmain zbinaries/precompiled_sanitizedmain
	@ make clean
	@ mkdir -p 'LASD exercise-3'
	@ cp -r ${DIRECTORIES} 'LASD exercise-3'
	@ cp ${FILES} 'LASD exercise-3'
	@ tar -czvf 'De Rosa - Francesco - N86004379.tar.gz' 'LASD exercise-3'
	@ zip -r 'De Rosa - Francesco - N86004379.zip' 'LASD exercise-3'
	@ rm -rf 'LASD exercise-3'

clean:
	@ rm -rf '.vscode'
	@ rm -rf 'LASD exercise-3'
	@ rm -f 'De Rosa - Francesco - N86004379.tar.gz'
	@ rm -f 'De Rosa - Francesco - N86004379.zip'
	@ rm -f main
	@ rm -f sanitizedmain