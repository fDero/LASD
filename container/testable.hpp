
// FRANCESCO DE ROSA N86004379  

#pragma once

#include "container.hpp"

namespace lasd {
  template <typename Data> class TestableContainer : public virtual Container {
    public:
      TestableContainer() = default;
      TestableContainer(const TestableContainer&) = default;
      TestableContainer(TestableContainer&&) = default;
      virtual ~TestableContainer() = default;

      bool virtual operator==(const Container&) const noexcept = delete;
      bool virtual operator!=(const Container&) const noexcept = delete;

      Container& operator=(const Container&) = delete;
      Container& operator=(Container&&) = delete;

      virtual bool Exists(const Data&) const noexcept = 0;
  };
}