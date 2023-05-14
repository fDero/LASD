
// FRANCESCO DE ROSA N86004379

#include "test.hpp"
#include "../hashtable/hashtable.hpp"
#include "../hashtable/opnadr/htopnadr.hpp"

void empty_htopnadr_instanciation(){
    auto hashtable = lasd::HashTableOpnAdr<int>(); 
}




void htopnadr_insertions(){
    auto hashtable = lasd::HashTableOpnAdr<int>();
    expect(hashtable.Insert(15));
    expect(hashtable.Insert(25));
    expect(hashtable.Insert(39));
    expect(hashtable.Insert(75));
    expect(hashtable.Insert(99));
    expect(hashtable.Insert(14));

    expect(not hashtable.Insert(15));
    expect(not hashtable.Insert(25));
    expect(not hashtable.Insert(39));
    expect(not hashtable.Insert(75));
    expect(not hashtable.Insert(99));
    expect(not hashtable.Insert(14));

    expect(hashtable.Exists(15));
    expect(hashtable.Exists(25));
    expect(hashtable.Exists(39));
    expect(hashtable.Exists(75));
    expect(hashtable.Exists(99));
    expect(hashtable.Exists(14));

    expect(hashtable.Size() == 6);
    expect(not hashtable.Empty());
}





void htopnadr_deletions(){
    auto hashtable = lasd::HashTableOpnAdr<int>();
    expect(hashtable.Insert(15));
    expect(hashtable.Insert(25));
    expect(hashtable.Insert(39));
    expect(hashtable.Insert(75));
    expect(hashtable.Insert(99));
    expect(hashtable.Insert(14));

    expect(hashtable.Remove(15));
    expect(hashtable.Remove(25)); 
    expect(hashtable.Remove(39)); 
    expect(hashtable.Remove(75));  
    expect(hashtable.Remove(99)); 
    expect(hashtable.Remove(14)); 
     
    expect(not hashtable.Remove(15));
    expect(not hashtable.Remove(25)); 
    expect(not hashtable.Remove(39)); 
    expect(not hashtable.Remove(75));  
    expect(not hashtable.Remove(99)); 
    expect(not hashtable.Remove(14));

    expect(not hashtable.Exists(15));
    expect(not hashtable.Exists(25));
    expect(not hashtable.Exists(39));
    expect(not hashtable.Exists(75));
    expect(not hashtable.Exists(99));
    expect(not hashtable.Exists(14));

    expect(hashtable.Size() == 0);
    expect(hashtable.Empty());
}





void htopnadr_constructors_from_mappable(){
    lasd::Vector<char> vector = generate_sample_vector(9);
    auto hashtable = lasd::HashTableOpnAdr<char>(vector);
    expect(hashtable.Size() == 9);
    expect(hashtable.Exists('A'));
    expect(hashtable.Exists('B'));
    expect(hashtable.Exists('C'));
    expect(hashtable.Exists('D'));
    expect(hashtable.Exists('E'));
    expect(hashtable.Exists('F'));
    expect(hashtable.Exists('G'));
    expect(hashtable.Exists('H'));
    expect(hashtable.Exists('I'));
}





void htopnadr_constructors_from_mutmappable(){
    lasd::Vector<std::string> vector (6);
    vector[0] = "str1"; vector[3] = "str4";
    vector[1] = "str2"; vector[4] = "str5";
    vector[2] = "str3"; vector[5] = "str6";
    auto hashtable = lasd::HashTableOpnAdr<std::string>(std::move(vector));
    expect(hashtable.Size() == 6);
    expect(hashtable.Exists("str1"));
    expect(hashtable.Exists("str2"));
    expect(hashtable.Exists("str3"));
    expect(hashtable.Exists("str4"));
    expect(hashtable.Exists("str5"));
    expect(hashtable.Exists("str6"));
}





void htopnadr_comparison_t1(){
    lasd::Vector<std::string> vector (6);
    vector[0] = "str1"; vector[3] = "str4";
    vector[1] = "str2"; vector[4] = "str5";
    vector[2] = "str3"; vector[5] = "str6";
    auto hashtablex = lasd::HashTableOpnAdr<std::string>(vector);
    auto hashtabley = lasd::HashTableOpnAdr<std::string>(vector);
    vector.Resize(3);
    auto hashtablez = lasd::HashTableOpnAdr<std::string>(vector);
    expect(hashtablex == hashtabley);
    expect(hashtabley == hashtablex);
    expect(hashtablex != hashtablez);
    expect(hashtabley != hashtablez);
    expect(hashtablez != hashtablex);
    expect(hashtablez != hashtabley);
    expect(hashtablez == hashtablez);
    expect(hashtablex == hashtablex);
    expect(hashtabley == hashtabley);
}





void htopnadr_comparison_t2(){
    lasd::Vector<std::string> vector (6);
    vector[0] = "str1"; vector[3] = "str4";
    vector[1] = "str2"; vector[4] = "str5";
    vector[2] = "str3"; vector[5] = "str6";
    auto hashtablex = lasd::HashTableOpnAdr<std::string>(vector);
    vector[3] = "different_string";
    auto hashtablez = lasd::HashTableOpnAdr<std::string>(vector);
    expect(hashtablex != hashtablez);
    expect(hashtablez != hashtablex);
}





void htopnadr_comparison_t3(){
    auto hashtablex = lasd::HashTableOpnAdr<std::string>();
    auto hashtablez = lasd::HashTableOpnAdr<std::string>();
    expect(hashtablex == hashtablez);
    expect(hashtablez == hashtablex);
}





void htopnadr_comparison_t4(){
    lasd::Vector<std::string> vector (6);
    vector[0] = "str1"; vector[3] = "str4";
    vector[1] = "str2"; vector[4] = "str5";
    vector[2] = "str3"; vector[5] = "str6";
    auto hashtablex = lasd::HashTableOpnAdr<std::string>(300, vector);
    auto hashtabley = lasd::HashTableOpnAdr<std::string>(100, vector);
    vector.Resize(3);
    auto hashtablez = lasd::HashTableOpnAdr<std::string>(300, vector);
    expect(hashtablex == hashtabley);
    expect(hashtabley == hashtablex);
    expect(hashtablex != hashtablez);
    expect(hashtabley != hashtablez);
    expect(hashtablez != hashtablex);
    expect(hashtablez != hashtabley);
    expect(hashtablez == hashtablez);
    expect(hashtablex == hashtablex);
    expect(hashtabley == hashtabley);
}





void htopnadr_comparison_t5(){
    lasd::Vector<std::string> vector (6);
    vector[0] = "str1"; vector[3] = "str4";
    vector[1] = "str2"; vector[4] = "str5";
    vector[2] = "str3"; vector[5] = "str6";
    auto hashtablex = lasd::HashTableOpnAdr<std::string>(300, vector);
    vector[3] = "different_string";
    auto hashtablez = lasd::HashTableOpnAdr<std::string>(100, vector);
    expect(hashtablex != hashtablez);
    expect(hashtablez != hashtablex);
}




void htopnadr_resize(){
    lasd::Vector<std::string> vector (6);
    vector[0] = "str1"; vector[3] = "str4";
    vector[1] = "str2"; vector[4] = "str5";
    vector[2] = "str3"; vector[5] = "str6";
    auto hashtablex = lasd::HashTableOpnAdr<std::string>(100, vector);
    auto hashtabley = lasd::HashTableOpnAdr<std::string>(100, vector);

    hashtablex.Map([](const std::string& x){ std::cerr << x << " "; }); std::cerr << "\n";
    hashtabley.Map([](const std::string& x){ std::cerr << x << " "; }); std::cerr << "\n";

    hashtabley.Resize(1000);

    hashtablex.Map([](const std::string& x){ std::cerr << x << " "; }); std::cerr << "\n";
    hashtabley.Map([](const std::string& x){ std::cerr << x << " "; }); std::cerr << "\n";

    expect(hashtablex == hashtabley);
    expect(hashtabley == hashtablex);
    hashtablex.Resize(300);
    expect(hashtablex == hashtabley);
    expect(hashtabley == hashtablex);
    hashtabley.Resize(100);
    expect(hashtablex == hashtabley);
    expect(hashtabley == hashtablex);
}





void execute_htopnadr_tests(){
    std::cout << blue("\n\t ↓↓↓ tests for lasd::HashTableClsAdr<Data>  ↓↓↓ \n");
    UnitTest htopnadr_test_procedures {
        {"empty_htopnadr_instanciation",           empty_htopnadr_instanciation},
        {"htopnadr_insertions",                    htopnadr_insertions},
        {"htopnadr_deletions",                     htopnadr_deletions},
        {"htopnadr_constructors_from_mappable",    htopnadr_constructors_from_mappable},
        {"htopnadr_constructors_from_mutmappable", htopnadr_constructors_from_mutmappable},
        {"htopnadr_comparison_t1",                 htopnadr_comparison_t1},
        {"htopnadr_comparison_t2",                 htopnadr_comparison_t2},
        {"htopnadr_comparison_t3",                 htopnadr_comparison_t3},
        {"htopnadr_comparison_t4",                 htopnadr_comparison_t4},
        {"htopnadr_comparison_t5",                 htopnadr_comparison_t5},
        {"htopnadr_resize",                        htopnadr_resize},
    };
    execute_tests(htopnadr_test_procedures);  
}