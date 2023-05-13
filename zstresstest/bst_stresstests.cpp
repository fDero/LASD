
// FRANCESCO DE ROSA N86004379

#include "stresstest.hpp"
#include "../binarytree/binarytree.hpp"
#include "../bst/bst.hpp"
#include "../list/list.hpp"

bool correct_bst_tree(const lasd::BinaryTree<int>::Node& root){
    if (root.HasRightChild() and not correct_bst_tree(root.RightChild())) return false;
    if (root.HasLeftChild() and not correct_bst_tree(root.LeftChild())) return false;
    if (root.HasRightChild() and root.RightChild().Element() < root.Element()) return false;
    if (root.HasLeftChild() and root.LeftChild().Element() > root.Element()) return false;
    return true;
}

void bst_correctness_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 300; attempt++){
        while (tree.Size() < 300) tree.Insert(get_random_value());
        expect(correct_bst_tree(tree.Root()));
        tree.Clear();
    }
}

void bst_insertions_removal_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 300; attempt++){
        while (tree.Size() < 300) tree.Insert(get_random_value());
        for (int i = 0; i < 100; i++) {
            int randvalue = get_random_value();
            expect(tree.Exists(randvalue) == tree.Remove(randvalue)); 
            expect(not tree.Exists(randvalue));
        }
        expect(correct_bst_tree(tree.Root()));
        tree.Clear();
    }
}

void bst_predecessor_search_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 300; attempt++){
        while (tree.Size() < 200) tree.Insert(get_random_value());
        for (int i = 0; i < 100; i++) {
            int randvalue = get_random_value();
            int predecessor = randvalue;
            tree.BreadthMap([&predecessor, &randvalue](const int& x){
                if (x < randvalue and x > predecessor) predecessor = x;
            });
            if (predecessor != randvalue){
                expect(tree.Exists(predecessor));
                expect(tree.PredecessorNRemove(randvalue) == predecessor);
                expect(not tree.Exists(predecessor));
            }
        }
        expect(correct_bst_tree(tree.Root()));
        tree.Clear();
    }
}

void bst_successor_search_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 300; attempt++){
        while (tree.Size() < 200) tree.Insert(get_random_value());
        for (int i = 0; i < 100; i++) {
            int randvalue = get_random_value();
            int successor = randvalue;
            tree.BreadthMap([&successor, &randvalue](const int& x){
                if (x > randvalue and x < successor) successor = x;
            });
            if (successor != randvalue){
                expect(tree.Exists(successor));
                expect(tree.PredecessorNRemove(randvalue) == successor);
                expect(not tree.Exists(successor));
            }
        }
        expect(correct_bst_tree(tree.Root()));
        tree.Clear();
    }
}

void bst_min_search_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 400; attempt++){
        while (tree.Size() < 300) tree.Insert(get_random_value());
        int min = tree.Min();
        bool success = true;
        tree.BreadthMap([&min, &success](const int& x){ success &= (x >= min); });
        expect(success);
        tree.Clear();
    }
}

void bst_max_search_stresstest(){
    lasd::BST<int> tree;
    for (long attempt = 1; attempt <= 400; attempt++){
        while (tree.Size() < 300) tree.Insert(get_random_value());
        int max = tree.Max();
        bool success = true;
        tree.BreadthMap([&max, &success](const int& x){ success &= (x <= max); });
        expect(success);
        tree.Clear();
    }
}

void bst_copy_move_stresstest(){
    lasd::BST<int> tree1;
    lasd::BST<int> tree2;
    for (long attempt = 1; attempt <= 400; attempt++){
        while (tree1.Size() < get_random_value()%150) tree1.Insert(get_random_value());
        while (tree2.Size() < get_random_value()%150) tree2.Insert(get_random_value());
        tree1 = tree2;
        auto tree3 = std::move(tree2);
        expect(tree1 == tree3);
        tree1.Clear();
        tree2.Clear();
    }
}

void bst_removal_coherence_stresstest(){
    lasd::BST<int> bst;
    auto values = lasd::Vector<int>(250);
    auto removed_values = lasd::List<int>();
    for (long attempt = 1; attempt <= 400; attempt++){
        for (long i = 0; i < values.Size(); i++){
            values[i] = get_random_value();
            bst.Insert(values[i]);
        }
        
        for (long i = 0; i < values.Size(); i++){
            bst.Exists(values[i]);
            if (random_boolean_by_probability_percentage(20)){
                removed_values.InsertAtBack(values[i]);
                bst.Remove(values[i]);
                expect(not bst.Exists(values[i]));
            }
        }

        for (long i = 0; i < 250; i++){
            expect(bst.Exists(values[i]) == not removed_values.Exists(values[i]));
            expect(bst.Exists(values[i]) or removed_values.Exists(values[i]));
        }

        removed_values.Clear();
        bst.Clear();
    }
}

void bst_remove_exists_stresstest(){
    lasd::BST<int> bst;
    lasd::StackVec<int> values;

    for (long attempt = 1; attempt <= 400; attempt++){
        for (long i = 0; i < 200; i++){
            int generated = get_random_value();
            if(bst.Insert(generated)) values.Push(generated);
        }
        while (values.Size() > 100){
            int value = values.TopNPop();
            expect(bst.Exists(value));
            expect(bst.Remove(value));
            expect(not bst.Exists(value));
        }
        bst.Clear();
        values.Clear();
    }
}

void execute_bst_stresstests() {
    execute_test("bst_correctness_stresstest",         bst_correctness_stresstest);
    execute_test("bst_insertions_removal_stresstest",  bst_insertions_removal_stresstest);
    execute_test("bst_predecessor_search_stresstest",  bst_predecessor_search_stresstest);
    execute_test("bst_successor_search_stresstest",    bst_successor_search_stresstest);
    execute_test("bst_min_search_stresstest",          bst_min_search_stresstest);
    execute_test("bst_max_search_stresstest",          bst_max_search_stresstest);
    execute_test("bst_copy_move_stresstest",           bst_copy_move_stresstest);
    execute_test("bst_removal_coherence_stresstest",   bst_removal_coherence_stresstest);
    execute_test("bst_remove_exists_stresstest",       bst_remove_exists_stresstest);
}