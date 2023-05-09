
// FRANCESCO DE ROSA N86004379

#include <iostream>
#include <string>
#include <utility>

void display_fancy_asciiart(){
    std::cout << "\n\t  .----------------.  .----------------.  .----------------.  .----------------.      "; 
    std::cout << "\n\t | .--------------. || .--------------. || .--------------. || .--------------. |     "; 
    std::cout << "\n\t | |   _____      | || |      __      | || |    _______   | || |  ________    | |     "; 
    std::cout << "\n\t | |  |_   _|     | || |     /  \\     | || |   /  ___  |  | || | |_   ___ `.  | |    "; 
    std::cout << "\n\t | |    | |       | || |    / /\\ \\    | || |  |  (__ \\_|  | || |   | |   `. \\ | | "; 
    std::cout << "\n\t | |    | |   _   | || |   / ____ \\   | || |   '.___`-.   | || |   | |    | | | |    "; 
    std::cout << "\n\t | |   _| |__/ |  | || | _/ /    \\ \\_ | || |  |`\\____) |  | || |  _| |___.' / | |  "; 
    std::cout << "\n\t | |  |________|  | || ||____|  |____|| || |  |_______.'  | || | |________.'  | |     ";
    std::cout << "\n\t | |              | || |              | || |              | || |              | |     ";
    std::cout << "\n\t | '--------------' || '--------------' || '--------------' || '--------------' |     ";
    std::cout << "\n\t  '----------------'  '----------------'  '----------------'  '----------------'      ";
}

void goodbye() { 
    std::cout << "\n Goodbye then! \n"; 
}

void input_error() { 
    std::cout << "\n Unrecognized option! please try again \n"; 
}

short get_user_choice() {
  try { 
    std::string input;
    std::getline(std::cin, input);
    return std::stoi(input); 
  } 
  catch(...) { return -1; }
}