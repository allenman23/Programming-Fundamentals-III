#include <memory>
#include <iostream>
#include "PrecondViolatedExcep.h"
#include "NotFoundException.h"
#include "BinaryNodeTree.h" 
#include "BinaryNode.h" 
#include "BinarySearchTree.h"

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::placeNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
	std::shared_ptr<BinaryNode<ItemType>> newNodePtr)
{
	if (subTreePtr == nullptr)
		return newNodePtr;
	else if (subTreePtr->getItem() > newNodePtr->getItem())
	{
		auto tempPtr = placeNode(subTreePtr->getLeftChildPtr(), newNodePtr);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else
	{
		auto tempPtr = placeNode(subTreePtr->getRightChildPtr(), newNodePtr);
		subTreePtr->setRightChildPtr(tempPtr);

	}
	return subTreePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeValue(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
	const ItemType target, bool & success)
{
	if (subTreePtr == nullptr)
	{
		success = false;
	}
	else if (subTreePtr->getItem() == target)
	{
		subTreePtr = removeNode(subTreePtr);
		success = true;
	}
	else if (subTreePtr->getItem() > target)
	{
		auto tempPtr = removeValue(subTreePtr->getLeftChildPtr(), target, success);
		subTreePtr->setLeftChildPtr(tempPtr);
	}
	else
	{
		auto tempPtr = removeValue(subTreePtr->getRightChildPtr(), target, success);
		subTreePtr->setRightChildPtr(tempPtr);
	}
	return subTreePtr;
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeNode(std::shared_ptr<BinaryNode<ItemType>> nodePtr)
{
	auto nodeToConnectPtr = std::make_shared<BinaryNode<ItemType>>();
	auto tempPtr = std::make_shared<BinaryNode<ItemType>>();
	bool leftNull, rightNull, leftOnly, rightOnly;
	leftNull = nodePtr->getLeftChildPtr() == nullptr;
	rightNull = nodePtr->getRightChildPtr() == nullptr;
	leftOnly = !leftNull && rightNull;
	rightOnly = leftNull && !rightNull;
	ItemType newNodeValue;
	if (leftNull && rightNull)
	{
		std::cout << "removed leaf\n";
		return nullptr;
	}
	else if (leftOnly || rightOnly)
	{
		if (leftOnly)
			nodeToConnectPtr = nodePtr->getLeftChildPtr();
		else
			nodeToConnectPtr = nodePtr->getRightChildPtr();
		std::cout << "removed with 1 child\n";

		return nodeToConnectPtr;
	}
	else
	{
		tempPtr = removeLeftmostNode(nodePtr->getRightChildPtr(), newNodeValue);
		nodePtr->setRightChildPtr(tempPtr);
		nodePtr->setItem(newNodeValue);
		std::cout << "removed with 2 kids\n";
		return nodePtr;
	}
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::removeLeftmostNode(std::shared_ptr<BinaryNode<ItemType>> subTreePtr,
	ItemType & inorderSuccessor)
{
	auto tempPtr = std::make_shared<BinaryNode<ItemType>>();
	if (subTreePtr->getLeftChildPtr() == nullptr)
	{
		inorderSuccessor = subTreePtr->getItem();
		return removeNode(subTreePtr);
	}
	else
	{
		tempPtr = removeLeftmostNode(subTreePtr->getLeftChildPtr(), inorderSuccessor);
		subTreePtr->setLeftChildPtr(tempPtr);
		return subTreePtr;
	}
}

template<class ItemType>
std::shared_ptr<BinaryNode<ItemType>> BinarySearchTree<ItemType>::findNode(std::shared_ptr<BinaryNode<ItemType>> treePtr,
	const ItemType & target) const
{
	if (treePtr == nullptr)
		return nullptr;
	else if (treePtr->getItem() == target)
		return treePtr;
	else if (treePtr->getItem() > target)
		return findNode(treePtr->getLeftChildPtr(), target);
	else
		return findNode(treePtr->getRightChildPtr(), target);
}

template<class ItemType>
void BinarySearchTree<ItemType>::setRootData(const ItemType & newData) const
{
	if (this->isEmpty())
		rootPtr = std::make_shared<BinaryNode<ItemType>>(newData, nullptr, nullptr);
	else
		this->rootPtr->setItem(newData);
}

template<class ItemType>
bool BinarySearchTree<ItemType>::add(const ItemType & newEntry)
{
	auto newNodePtr = std::make_shared<BinaryNode<ItemType>>(newEntry);
	this->rootPtr = placeNode(this->rootPtr, newNodePtr);
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(const ItemType & anEntry)
{
	bool removeSuccess;
	removeValue(this->rootPtr, anEntry, removeSuccess);
	return removeSuccess;
}

template<class ItemType>
ItemType BinarySearchTree<ItemType>::getEntry(const ItemType & anEntry) const
{
	bool isSuccessful = false;
	auto binaryNodePtr = findNode(this->rootPtr, anEntry);

	if (isSuccessful)
		return binaryNodePtr->getItem();
	else
		throw NotFoundException("Entry not found in tree!");
}

template<class ItemType>
bool BinarySearchTree<ItemType>::contains(const ItemType & anEntry) const
{
	if (findNode(this->rootPtr, anEntry) == nullptr)
		return false;
	else
		return true;
}
