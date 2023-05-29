
// FRANCESCO DE ROSA N86004379

#include "stresstest.hpp"
#include "../queue/vec/queuevec.hpp"
#include "../queue/lst/queuelst.hpp"

void queue_massive_enqueue_dequeue_stresstests(){
    lasd::QueueVec<int> queuevec;
    lasd::QueueLst<int> queuelst;
    lasd::sizetype expected_size = 0;

    for (long attempt = 1; attempt <= 10000; attempt++){
        
        int test_value = get_random_value();
        queuevec.Enqueue(test_value);
        queuelst.Enqueue(test_value);
        expected_size++;
        
        expect(queuelst.Size() == expected_size);
        expect(queuevec.Size() == expected_size);
        
        while(random_boolean_by_probability_percentage(30) and expected_size != 0) {
            queuelst.Dequeue();
            queuevec.Dequeue();
            expected_size--;
        }

        if (random_boolean_by_probability_percentage(10)) {
            queuelst.Clear();
            queuevec.Clear();
            expected_size = 0;
            expect(queuelst.Empty());
            expect(queuevec.Empty());
        }

        expect(queuelst.Size() == expected_size);
        expect(queuevec.Size() == expected_size);
    }

    while (expected_size != 0){
        expect(queuelst.HeadNDequeue() == queuevec.HeadNDequeue());
        expected_size--;
    }

    expect(queuelst.Empty());
    expect(queuevec.Empty());
}

void execute_queue_stresstests(){
    execute_stresstests({
        {"queue_massive_enqueue_dequeue_stresstests#1", queue_massive_enqueue_dequeue_stresstests},
        {"queue_massive_enqueue_dequeue_stresstests#2", queue_massive_enqueue_dequeue_stresstests},
        {"queue_massive_enqueue_dequeue_stresstests#3", queue_massive_enqueue_dequeue_stresstests},
    });
}