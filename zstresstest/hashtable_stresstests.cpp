
// FRANCESCO DE ROSA N86004379

#include "stresstest.hpp"
#include "../hashtable/clsadr/htclsadr.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"


template<typename MappableDictionaryContainer1, typename MappableDictionaryContainer2> 
bool dictionaries_are_equal(MappableDictionaryContainer1& xx, MappableDictionaryContainer2& yy){
    bool equality = true;
    xx.Map([&equality, &yy](const auto& x) { equality &= (yy.Exists(x)); });
    return equality;
}


void hashtable_massive_insert_remove_stresstests(){
    lasd::HashTableOpnAdr<int> openhashtable;
    lasd::HashTableClsAdr<int> closedhashtable;

    for (long attempt = 1; attempt <= 1000; attempt++){
        
        for (long insertion = 0; insertion < 350; insertion++){
            int test_value = get_random_value();
            expect(openhashtable.Insert(test_value) == closedhashtable.Insert(test_value));
            expect(openhashtable.Size() == closedhashtable.Size());
            if (random_boolean_by_probability_percentage(30)) expect(dictionaries_are_equal(openhashtable,closedhashtable));
        }
        
        for (long existence = 0; existence < 300; existence++){
            int test_value = get_random_value();
            expect(openhashtable.Exists(test_value) == closedhashtable.Exists(test_value));
        }

        for (long remotion = 0; remotion < 150; remotion++) {
            int test_value = get_random_value();
            expect(openhashtable.Remove(test_value) == closedhashtable.Remove(test_value));
            expect(openhashtable.Size() == closedhashtable.Size());
            if (random_boolean_by_probability_percentage(30)) expect(dictionaries_are_equal(openhashtable,closedhashtable));
        }
    
        openhashtable.Clear();
        closedhashtable.Clear();
    }
}

void execute_hashtable_stresstests(){
    execute_stresstests({
        {"hashtable_massive_insert_remove_stresstests#1", hashtable_massive_insert_remove_stresstests},
        {"hashtable_massive_insert_remove_stresstests#2", hashtable_massive_insert_remove_stresstests},
        {"hashtable_massive_insert_remove_stresstests#3", hashtable_massive_insert_remove_stresstests},
        {"hashtable_massive_insert_remove_stresstests#4", hashtable_massive_insert_remove_stresstests},
        {"hashtable_massive_insert_remove_stresstests#5", hashtable_massive_insert_remove_stresstests},
    });
}