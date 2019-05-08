//  Created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

// Listing 16-4. Altered

/** Link-based implementation of the ADT binary search tree.
 @file BinarySearchTree.h */
 
#ifndef BINARY_SEARCH_TREE_
#define BINARY_SEARCH_TREE_

#include <memory>
#include "BinaryTreeInterface.h"
#include "BinaryNode.h"
#include "BinaryNodeTree.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"

template<class ItemType>
class BinarySearchTree : public BinaryNodeTree<ItemType>
{
	// use this->rootPtr to access the BinaryNodeTree rootPtr

protected:
	//------------------------------------------------------------
	// Protected Utility Methods Section:
	// Recursive helper methods for the public methods.
	//------------------------------------------------------------
	// Recursively finds where the given node should be placed and
	// inserts it in a leaf at that point.
	std::shared_ptr<BinaryNode<ItemType>> placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		std::shared_ptr<BinaryNode<ItemType>> newNodePtr);

	// Removes the given target value from the tree while maintaining a
	// binary search tree.
	std::shared_ptr<BinaryNode<ItemType>> removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		const ItemType target,
		bool& success) override;

	// Removes a given node from a tree while maintaining a
	// binary search tree.
	std::shared_ptr<BinaryNode<ItemType>> removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr);

	// Removes the leftmost node in the left subtree of the node
	// pointed to by nodePtr.
	// Sets inorderSuccessor to the value in this node.
	// Returns a pointer to the revised subtree.
	std::shared_ptr<BinaryNode<ItemType>> removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
		ItemType& inorderSuccessor);

	// Returns a pointer to the node containing the given value,
	// or nullptr if not found.
	std::shared_ptr<BinaryNode<ItemType>> findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
		const ItemType& target) const;

public:
	//------------------------------------------------------------
	// Constructor and Destructor Section.
	//------------------------------------------------------------
	// inherits from BinaryNodeTree

	//------------------------------------------------------------
	// Public Methods Section.
	//------------------------------------------------------------
	void setRootData(const ItemType& newData) const;
	bool add(const ItemType& newEntry) override;
	bool remove(const ItemType& anEntry) override;
	ItemType getEntry(const ItemType& anEntry) const;
	bool contains(const ItemType& anEntry) const override;

};


#endif
