
// FRANCESCO DE ROSA N86004379

#pragma once

#include "iterator.hpp"
#include "../binarytree/binarytree.hpp"

namespace lasd {
  template <typename Data> class BTPreOrderIterator {
                            // Must extend ForwardIterator<Data>,
                            //             ResettableIterator<Data>
    public:

      // Specific constructors
      // BTPreOrderIterator(argument) specifiers; // An iterator over a given binary tree

      /* ************************************************************************ */

      // Copy constructor
      // BTPreOrderIterator(argument) specifiers;

      // Move constructor
      // BTPreOrderIterator(argument) specifiers;

      /* ************************************************************************ */

      // Destructor
      // ~BTPreOrderIterator() specifiers;

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

      // Specific member functions (inherited from Iterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)

      // type Terminated() specifiers; // (should not throw exceptions)

      /* ************************************************************************ */

      // Specific member functions (inherited from ForwardIterator)

      // type operator++() specifiers; // (throw std::out_of_range when terminated)

      /* ************************************************************************ */

      // Specific member functions (inherited from ResettableIterator)

      // type Reset() specifiers; // (should not throw exceptions)
  };


  template <typename Data>
  class BTPostOrderIterator {
                              // Must extend ForwardIterator<Data>,
                              //             ResettableIterator<Data>
    public:

      // Specific constructors
      // BTPostOrderIterator(argument) specifiers; // An iterator over a given binary tree

      /* ************************************************************************ */

      // Copy constructor
      // BTPostOrderIterator(argument) specifiers;

      // Move constructor
      // BTPostOrderIterator(argument) specifiers;

      /* ************************************************************************ */

      // Destructor
      // ~BTPostOrderIterator() specifiers;

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

      // Specific member functions (inherited from Iterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)

      // type Terminated() specifiers; // (should not throw exceptions)

      /* ************************************************************************ */

      // Specific member functions (inherited from ForwardIterator)

      // type operator++() specifiers; // (throw std::out_of_range when terminated)

      /* ************************************************************************ */

      // Specific member functions (inherited from ResettableIterator)

      // type Reset() specifiers; // (should not throw exceptions)

  };


  template <typename Data> class BTInOrderIterator {
                            // Must extend ForwardIterator<Data>,
                            //             ResettableIterator<Data>
    public:

      // Specific constructors
      // BTInOrderIterator(argument) specifiers; // An iterator over a given binary tree

      /* ************************************************************************ */

      // Copy constructor
      // BTInOrderIterator(argument) specifiers;

      // Move constructor
      // BTInOrderIterator(argument) specifiers;

      /* ************************************************************************ */

      // Destructor
      // ~BTInOrderIterator() specifiers;

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

      // Specific member functions (inherited from Iterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)

      // type Terminated() specifiers; // (should not throw exceptions)

      /* ************************************************************************ */

      // Specific member functions (inherited from ForwardIterator)

      // type operator++() specifiers; // (throw std::out_of_range when terminated)

      /* ************************************************************************ */

      // Specific member functions (inherited from ResettableIterator)

      // type Reset() specifiers; // (should not throw exceptions)
  };

  template <typename Data> class BTBreadthIterator {
                            // Must extend ForwardIterator<Data>,
                            //             ResettableIterator<Data>

    public:

      // Specific constructors
      // BTBreadthIterator(argument) specifiers; // An iterator over a given binary tree

      /* ************************************************************************ */

      // Copy constructor
      // BTBreadthIterator(argument) specifiers;

      // Move constructor
      // BTBreadthIterator(argument) specifiers;

      /* ************************************************************************ */

      // Destructor
      // ~BTBreadthIterator() specifiers;

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

      // Specific member functions (inherited from Iterator)

      // type operator*() specifiers; // (throw std::out_of_range when terminated)

      // type Terminated() specifiers; // (should not throw exceptions)

      /* ************************************************************************ */

      // Specific member functions (inherited from ForwardIterator)

      // type operator++() specifiers; // (throw std::out_of_range when terminated)

      /* ************************************************************************ */

      // Specific member functions (inherited from ResettableIterator)

      // type Reset() specifiers; // (should not throw exceptions)

  };
}