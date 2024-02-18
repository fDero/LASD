
# LASD
This library provides a collection of generic data structures implemented in C++. It has been developed as a university project for the Data-Structures class, and part of the assignment consisted of implementing the data-structures themselves in such a way for them to be compliant with an API the teacher enstablished.

The folder `zlasdtest` is a test-suite the teacher provided us, and was used to grade our projects. On the other hand `zmytest` and `zstresstest` are two other test-suites
i added to the project for the sake of completeness.

## Features

- Implementation of commonly used data structures such as:
  - `Vector<T>` a dynamic array that expands and contracts automatically in a time and memory efficient way
  - `List<T>` a doubly linked list 
  - `StackVec<T>` a Stack implementation that internally works like a dynamic array
  - `StackLst<T>` a Stack implementation that internally works like a linked list
  - `QueueVec<T>` a Queue implementation that internally works like a dynamic array
  - `QueueLst<T>` a Queue implementation that internally works like a linked list
  - `HashTableClsAdr<T>` a closed addressing hash-table, being indeed a dynamic array of linked lists
  - `HashTableOpnAdr<T>` an open addressing hash-table, being indeed a dynamic array
  - `TreeVec<T>` a binary tree implementation that internally works like linked dynamically allocated graph, that supports iteration in pre-order, post-order and in-order
  - `TreeLnk<T>` a binary tree implementation that internally works like a dynamic array, that supports iteration in pre-order, post-order and in-order
  - `BST<T>` a binary search tree implementation, that internally relies on a `TreeLnk<T>` offering logarithmic time search.
- Developed with the test-driven-development methodology
- Easy-to-use and intuitive APIs
- Completley generic code


## Example usage
The following code illustrates how to use an open addressing hash-table in your every-day code
```c++
int main(){
    lasd::HashTableOpnAdr<int> hashtable;
    hashtable.Insert(15);
    hashtable.Insert(25);
    hashtable.Insert(39);
    hashtable.Insert(75);

    static_assert(hashtable.Exists(14) == false);
    static_assert(hashtable.Exists(39) == true);
    static_assert(hashtable.Size() == 3);
}
```