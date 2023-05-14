
// FRANCESCO DE ROSA N86004379

#include "zmytest/test.hpp"
#include "zlasdtest/test.hpp"
#include "zstresstest/stresstest.hpp"
#include "zcli/menu.hpp"

int main() {
    display_fancy_asciiart();

    for (int choice = 0; choice != 4; choice = (choice == 0)? -1 : choice) {

        std::string prompt = (choice != 0) 
            ?       "\n\n ┍━ would you like to do something else?" 
            :       "\n\n ┍━ Hi there, what you would like to do?";
        
        std::cout << prompt;
        std::cout << "\n │   [1] Perform the teacher's tests";
        std::cout << "\n │   [2] Perform the student's tests";
        std::cout << "\n │   [3] Perform stress tests";
        std::cout << "\n │   [4] Quit";
        std::cout << "\n └─────────> ";
    
        switch (choice = get_user_choice()) {
            case 1 : lasdtest();                      break;
            case 2 : execute_student_test();          break;
            case 3 : execute_stresstest();            break;
            case 4 : goodbye();                       break;
            default: input_error();                   break;
        }
    }
}
