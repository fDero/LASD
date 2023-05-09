
// FRANCESCO DE ROSA N86004379

#pragma once 

#include "../container/container.hpp"
#include "../container/mappable.hpp"

namespace lasd {

  template <typename Data> class BinaryTree 
    : public virtual PreOrderMappableContainer<Data>
    , public virtual PostOrderMappableContainer<Data>
    , public virtual InOrderMappableContainer<Data>
    , public virtual BreadthMappableContainer<Data>
  {
    protected:
      using Container::size;
    public:
      BinaryTree() = default;
      BinaryTree(const BinaryTree&) = default;
      BinaryTree(BinaryTree&&) = default;
      virtual ~BinaryTree() = default;

      BinaryTree& operator=(const BinaryTree&) noexcept = delete;
      BinaryTree& operator=(BinaryTree&&) noexcept = delete;

      bool operator==(const BinaryTree&) const noexcept;
      bool operator!=(const BinaryTree&) const noexcept;

      using Container::Size;
      using Container::Empty;

      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      
      virtual inline void Fold(FoldFunctor, void*) const override;
      virtual inline void Map(MapFunctor) const override;
      virtual inline void PreOrderMap(MapFunctor) const override;
      virtual inline void PostOrderMap(MapFunctor) const override;
      virtual inline void InOrderMap(MapFunctor) const override;
      virtual inline void BreadthMap(MapFunctor) const override;

      struct Node {
        Node() = default;
        Node(const Node&) = default;
        Node(Node&&) = default;
        virtual ~Node() = default;

        virtual Node& operator=(const Node&) = delete;
        virtual Node& operator=(Node&&) = delete;

        virtual const Data& Element() const noexcept = 0;

        bool inline IsLeaf() const noexcept;
        bool HasLeftChild() const noexcept;
        bool HasRightChild() const noexcept;

        virtual const Node& LeftChild() const = 0;
        virtual const Node& RightChild() const = 0;
      };

      virtual const Node& Root() const = 0;

    private:
      void PreOrderMapOnSubtree(MapFunctor, const Node&) const;
      void PostOrderMapOnSubtree(MapFunctor, const Node&) const;
      void InOrderMapOnSubtree(MapFunctor, const Node&) const;
      void BreadthMapOnSubtree(MapFunctor, const Node&) const;
      bool CompareSubtrees(const Node&, const Node&) const noexcept;
  };



  template <typename Data> class MutableBinaryTree 
    : public virtual ClearableContainer
    , public virtual BinaryTree<Data>
    , public virtual MutablePreOrderMappableContainer<Data>
    , public virtual MutablePostOrderMappableContainer<Data>
    , public virtual MutableInOrderMappableContainer<Data>
    , public virtual MutableBreadthMappableContainer<Data>
  {
    protected:
      using Container::size;
    
    public:
      MutableBinaryTree() = default;
      MutableBinaryTree(const MutableBinaryTree&) = default;
      MutableBinaryTree(MutableBinaryTree&&) = default;
      virtual ~MutableBinaryTree() = default;

      MutableBinaryTree& operator=(const MutableBinaryTree&) noexcept = delete;
      MutableBinaryTree& operator=(MutableBinaryTree&&) noexcept = delete;

      using BinaryTree<Data>::operator==;
      using BinaryTree<Data>::operator!=;

      using Container::Size;
      using Container::Empty;

      using FoldFunctor = typename FoldableContainer<Data>::FoldFunctor;
      using MapFunctor = typename MappableContainer<Data>::MapFunctor;
      using MutableMapFunctor = typename MutableMappableContainer<Data>::MutableMapFunctor;
      
      virtual void Map(MutableMapFunctor) override;
      virtual void PreOrderMap(MutableMapFunctor) override;
      virtual void PostOrderMap(MutableMapFunctor) override;
      virtual void InOrderMap(MutableMapFunctor) override;
      virtual void BreadthMap(MutableMapFunctor) override;

      virtual inline void Map(MapFunctor) const override;
      virtual inline void PreOrderMap(MapFunctor) const override;
      virtual inline void PostOrderMap(MapFunctor) const override;
      virtual inline void InOrderMap(MapFunctor) const override;
      virtual inline void BreadthMap(MapFunctor) const override;
  
      struct MutableNode : public virtual BinaryTree<Data>::Node {
        MutableNode() = default;
        MutableNode(const MutableNode&) = default;
        MutableNode(MutableNode&&) = default;
        virtual ~MutableNode() = default;

        virtual MutableNode& operator=(const MutableNode&) = delete;
        virtual MutableNode& operator=(MutableNode&&) = delete;

        virtual Data& Element() noexcept = 0;

        using BinaryTree<Data>::Node::IsLeaf;
        using BinaryTree<Data>::Node::HasLeftChild;
        using BinaryTree<Data>::Node::HasRightChild;

        virtual MutableNode& LeftChild() = 0;
        virtual MutableNode& RightChild() = 0;
      };
      virtual MutableNode& Root() = 0;
  };
}

#include "binarytree.cpp"
#include "../iterator/binarytree-const-iterators.hpp"
#include "../iterator/binarytree-mutable-iterators.hpp"