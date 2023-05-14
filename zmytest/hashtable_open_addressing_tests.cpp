
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../hashtable/hashtable.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

void empty_htopnadr_instanciation() {
    lasd::HashTableOpnAdr<int>();
}

void execute_htopnadr_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::HashTableOpnAdr<Data>  ↓↓↓ \n");
    UnitTest htclsadr_test_procedures {
        {"empty_htopnadr_instanciation",           empty_htopnadr_instanciation},
    };
    execute_tests(htclsadr_test_procedures);  
}