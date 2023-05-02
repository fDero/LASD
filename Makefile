
# FRANCESCO DE ROSA N86004379

.PHONY: sanitize-build build deploy

FILES = main.cpp build.sh Makefile
DIRECTORIES = \
	container list queue stack vector   \
	binarytree bst iterator             \
	zbinaries zmytest zlasdtest         \
	

ZMYTEST = \
	zmytest/vector_tests.cpp   zmytest/list_tests.cpp     \
    zmytest/queue_tests.cpp    zmytest/stack_tests.cpp    \
    zmytest/test.cpp           zmytest/sort_tests.cpp     \
	zmytest/treelnk_tests.cpp  zmytest/treevec_tests.cpp  \
	zmytest/bst_tests.cpp      zmytest/iterator_tests.cpp \

ZLASDTEST = \
	zlasdtest/test.cpp                    zlasdtest/container/container.cpp  \
	zlasdtest/exercise1a/simpletest.cpp   zlasdtest/exercise1a/fulltest.cpp  \
	zlasdtest/exercise1b/simpletest.cpp   zlasdtest/exercise1b/fulltest.cpp  \

build:
	@ g++ -std=c++20 -o main -O3 ${ZMYTEST} ${ZLASDTEST} main.cpp

sanitize-build:
	@ g++ -std=c++20 -fsanitize=address -o sanitizedmain -O3 ${ZMYTEST} ${ZLASDTEST} main.cpp

deploy:
	@ make clean
	@ mkdir -p 'LASD exercise-2'
	@ cp -r ${DIRECTORIES} 'LASD exercise-2'
	@ cp ${FILES} 'LASD exercise-2'
	@ tar -czvf 'De Rosa - Francesco - N86004379.tar.gz' 'LASD exercise-2'
	@ zip 'De Rosa - Francesco - N86004379.zip' 'LASD exercise-2'
	@ rm -rf 'LASD exercise-2'

clean:
	@ rm -rf '.vscode'
	@ rm -rf 'LASD exercise-2'
	@ rm -f 'De Rosa - Francesco - N86004379.tar.gz'
	@ rm -f 'De Rosa - Francesco - N86004379.zip'
	@ rm -f main
	@ rm -f sanitizedmain