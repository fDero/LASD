
// FRANCESCO DE ROSA N86004379

#pragma once

#include "iterator.hpp"
#include "../binarytree/binarytree.hpp"
#include "binarytree-const-iterators.hpp"

namespace lasd {

  template <typename Data> class BTPreOrderMutableIterator {
                                    // Must extend MutableIterator<Data>,
                                    //             BTPreOrderIterator<Data>
    public:

      // Specific constructors
      // BTPreOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree

      /* ************************************************************************ */

      // Copy constructor
      // BTPreOrderMutableIterator(argument) specifiers;

      // Move constructor
      // BTPreOrderMutableIterator(argument) specifiers;

      /* ************************************************************************ */

      // Destructor
      // ~BTPreOrderMutableIterator() specifiers;

      /* ************************************************************************ */

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      /* ************************************************************************ */

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      /* ************************************************************************ */

      // Specific member functions (inherited from MutableIterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)
  };


  template <typename Data> class BTPostOrderMutableIterator {
                                    // Must extend MutableIterator<Data>,
                                    //             BTPostOrderIterator<Data>
    public:

      // Specific constructors
      // BTPostOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree

      /* ************************************************************************ */

      // Copy constructor
      // BTPostOrderMutableIterator(argument) specifiers;

      // Move constructor
      // BTPostOrderMutableIterator(argument) specifiers;

      /* ************************************************************************ */

      // Destructor
      // ~BTPostOrderMutableIterator() specifiers;

      /* ************************************************************************ */

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      /* ************************************************************************ */

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      /* ************************************************************************ */

      // Specific member functions (inherited from MutableIterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)

  };

  template <typename Data> class BTInOrderMutableIterator {
                                    // Must extend MutableIterator<Data>,
                                    //             BTInOrderIterator<Data>
    public:

      // Specific constructors
      // BTInOrderMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree

      /* ************************************************************************ */

      // Copy constructor
      // BTInOrderMutableIterator(argument) specifiers;

      // Move constructor
      // BTInOrderMutableIterator(argument) specifiers;

      /* ************************************************************************ */

      // Destructor
      // ~BTInOrderMutableIterator() specifiers;

      /* ************************************************************************ */

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      /* ************************************************************************ */

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      /* ************************************************************************ */

      // Specific member functions (inherited from MutableIterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)

  };

  
  template <typename Data> class BTBreadthMutableIterator 
  {
                                    // Must extend MutableIterator<Data>,
                                    //             BTBreadthIterator<Data>
    public:

      // Specific constructors
      // BTBreadthMutableIterator(argument) specifiers; // An iterator over a given mutable binary tree

      /* ************************************************************************ */

      // Copy constructor
      // BTBreadthMutableIterator(argument) specifiers;

      // Move constructor
      // BTBreadthMutableIterator(argument) specifiers;

      /* ************************************************************************ */

      // Destructor
      // ~BTBreadthMutableIterator() specifiers;

      /* ************************************************************************ */

      // Copy assignment
      // type operator=(argument) specifiers;

      // Move assignment
      // type operator=(argument) specifiers;

      /* ************************************************************************ */

      // Comparison operators
      // type operator==(argument) specifiers;
      // type operator!=(argument) specifiers;

      /* ************************************************************************ */

      // Specific member functions (inherited from MutableIterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)
  };
}