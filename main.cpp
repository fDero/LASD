
// FRANCESCO DE ROSA N86004379

#include "zmytest/test.hpp"
#include "zlasdtest/test.hpp"
#include <iostream>

#include "vector/vector.hpp"

int main() {

  short choice = 0;
  while (choice != 3) {

    std::cout << "\n Hi there, what you would like to do? \n";
    std::cout << "\t [1] Perform the teacher's tests \n";
    std::cout << "\t [2] Perform the student's tests \n";
    std::cout << "\t [3] Quit \n";

    std::string input;
    std::getline(std::cin, input);

    try { choice = std::stoi(input); } catch(...) { choice = -1; }

    if (choice == 1) lasdtest();
    else if (choice == 2) execute_student_test();
    else if (choice == 3) std::cout << "\n Goodbye then! \n"; 
    else std::cout << "\n Unrecognized input, please try again \n";
  }  
}