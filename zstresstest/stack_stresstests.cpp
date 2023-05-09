
// FRANCESCO DE ROSA N86004379

#include "stresstest.hpp"
#include "../stack/vec/stackvec.hpp"
#include "../stack/lst/stacklst.hpp"

void massive_stack_push_pop_stresstest(){
    lasd::StackVec<int> stackvec;
    lasd::StackLst<int> stacklst;
    lasd::sizetype expected_size = 0;

    for (long attempt = 1; attempt <= 10000; attempt++){
        
        int test_value = get_random_value();
        stackvec.Push(test_value);
        stacklst.Push(test_value);
        expected_size++;
        
        expect(stacklst.Size() == expected_size);
        expect(stackvec.Size() == expected_size);
        
        while(random_boolean_by_probability_percentage(30) and expected_size != 0) {
            stacklst.Pop();
            stackvec.Pop();
            expected_size--;
        }

        if (random_boolean_by_probability_percentage(10)) {
            stacklst.Clear();
            stackvec.Clear();
            expected_size = 0;
            expect(stacklst.Empty());
            expect(stackvec.Empty());
        }

        expect(stacklst.Size() == expected_size);
        expect(stackvec.Size() == expected_size);
    }

    while (expected_size != 0){
        expect(stacklst.TopNPop() == stackvec.TopNPop());
        expected_size--;
    }

    expect(stacklst.Empty());
    expect(stackvec.Empty());
}

void execute_stack_stresstests(){
    execute_test("massive_stack_push_pop_stresstest - 1", massive_stack_push_pop_stresstest);
    execute_test("massive_stack_push_pop_stresstest - 2", massive_stack_push_pop_stresstest);
    execute_test("massive_stack_push_pop_stresstest - 3", massive_stack_push_pop_stresstest);
}