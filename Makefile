
# FRANCESCO DE ROSA N86004379

.PHONY: sanitize-build build deploy

COMPRESS = \
	container list queue stack vector   \
	zbinaries zmytest zlasdtest         \
	build.sh main.cpp Makefile          \

ZMYTEST = \
	zmytest/vector_tests.cpp       zmytest/list_tests.cpp  \
    zmytest/queue_tests.cpp        zmytest/stack_tests.cpp \
    zmytest/test.cpp               zmytest/sort_tests.cpp  \

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
	@ tar -czvf 'De Rosa - Francesco - N86004379.tar.gz' ${COMPRESS}
	@ zip 'De Rosa - Francesco - N86004379.zip' ${COMPRESS}
	
clean:
	@ rm -rf '.vscode'
	@ rm -f 'De Rosa - Francesco - N86004379.tar.gz'
	@ rm -f 'De Rosa - Francesco - N86004379.zip'
	@ rm -f main
	@ rm -f sanitizedmain