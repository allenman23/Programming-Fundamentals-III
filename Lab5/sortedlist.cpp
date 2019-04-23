// Allen Lim

#include<iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include<random>
#include<chrono>

template<class ItemType>
class Node
{
private:
   ItemType        item;
   std::shared_ptr<Node<ItemType>> next;
   
public:
   Node() {};
   Node(const ItemType& anItem) {  item = anItem; };
   Node(const ItemType& anItem, std::shared_ptr<Node<ItemType>> nextNodePtr)
   { 
   		item = anItem;
   		next = nextNodePtr;
   };
   void setItem(const ItemType& anItem) { item = anItem; };
   void setNext(std::shared_ptr<Node<ItemType>> nextNodePtr) { next = nextNodePtr; };
   ItemType getItem() const { return item; };
   auto getNext() const { return next; };
};

class PrecondViolatedExcep : public std::logic_error
{
public:
   PrecondViolatedExcep(const std::string& message = "")
         : std::logic_error("Precondition Violated Exception: " + message)
	{
	}
};

template<class ItemType>
class SortedListInterface
{
public:
	virtual bool insertSorted(const ItemType& newEntry) = 0;
	virtual bool removeSorted(const ItemType& anEntry) = 0;
	virtual int getPosition(const ItemType& anEntry) const = 0;
	virtual bool isEmpty() const = 0;
	virtual int getLength() const = 0;
	virtual bool remove(int position) = 0;
	virtual void clear() = 0;
	virtual ItemType getEntry(int position) const = 0;
	virtual ~SortedListInterface() { }
};

template<class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>
{
private:
	std::shared_ptr<Node<ItemType>> headPtr;
	int itemCount;
	std::shared_ptr<Node<ItemType>> getNodeBefore(const ItemType& anEntry) const;
	std::shared_ptr<Node<ItemType>> getNodeAt(int position) const;
	std::shared_ptr<Node<ItemType>> copyChain(const std::shared_ptr<Node<ItemType>> origChainPtr);

public:
	LinkedSortedList();
	LinkedSortedList(const LinkedSortedList<ItemType>& aList);
	virtual ~LinkedSortedList();
	bool insertSorted(const ItemType& newEntry);
	bool removeSorted(const ItemType& anEntry);
	int getPosition(const ItemType& newEntry) const;
	bool isEmpty() const;
	int getLength() const;
	bool remove(int position);
	void clear();
	ItemType getEntry(int position) const;
};

template<class ItemType>
std::shared_ptr<Node<ItemType>> LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const
{
	std::shared_ptr<Node<ItemType>> curPtr = std::make_shared<Node<ItemType>>();
	curPtr = headPtr;
	std::shared_ptr<Node<ItemType>> prevPtr = std::make_shared<Node<ItemType>>();
	prevPtr = nullptr;
	while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) ) 
	{
		prevPtr = curPtr;
		curPtr = curPtr->getNext();
	}
	return prevPtr;
}

template<class ItemType>
std::shared_ptr<Node<ItemType>> LinkedSortedList<ItemType>::getNodeAt(int position) const
{
	std::shared_ptr<Node<ItemType>> curPtr = std::make_shared<Node<ItemType>>();
	curPtr = headPtr;
	for (int i = 1; i < position; i++)
		curPtr = curPtr->getNext();
	return curPtr;
}

template<class ItemType>
std::shared_ptr<Node<ItemType>> LinkedSortedList<ItemType>::copyChain(const std::shared_ptr<Node<ItemType>> origChainPtr)
{
	std::shared_ptr<Node<ItemType>> copiedChainPtr = std::make_shared<Node<ItemType>>();
	if (origChainPtr == nullptr)
	{
	copiedChainPtr = nullptr;
	itemCount = 0; 
	}
	else
	{
		copiedChainPtr = origChainPtr->getItem();
		copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
		itemCount++; 
	}
	return copiedChainPtr;
}

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList()
{
	headPtr = std::make_shared<Node<ItemType>>();
	headPtr = nullptr;
	itemCount = 0;
}

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList(const LinkedSortedList<ItemType>& aList) 
{
	headPtr = copyChain(aList.headPtr); 
}

template<class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList()
{
   clear();
}

template<class ItemType>
bool LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
	std::shared_ptr<Node<ItemType>> newNodePtr = std::make_shared<Node<ItemType>>();
	newNodePtr->setItem(newEntry);
	std::shared_ptr<Node<ItemType>> prevPtr = std::make_shared<Node<ItemType>>();
	prevPtr = getNodeBefore(newEntry);
	if (isEmpty() || (prevPtr == nullptr)) // Add at beginning 
	{
   		newNodePtr->setNext(headPtr);
		headPtr = newNodePtr;
	}
	else // Add after node before
	{
		std::shared_ptr<Node<ItemType>> aftPtr = std::make_shared<Node<ItemType>>();
		aftPtr = prevPtr->getNext();
		newNodePtr->setNext(aftPtr);
		prevPtr->setNext(newNodePtr);
	}
	itemCount++;
	return true;
}

template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType & anEntry)
{
	if (getPosition(anEntry) == 1) // remove from front
	{
		headPtr = headPtr->getNext();
		itemCount--;
	}
	else if (getPosition(anEntry) > 1) //remove anywhere after front
	{
		std::shared_ptr<Node<ItemType>> prevPtr = std::make_shared<Node<ItemType>>();
		prevPtr = getNodeBefore(anEntry);
		std::shared_ptr<Node<ItemType>> curPtr = std::make_shared<Node<ItemType>>();
		curPtr = prevPtr->getNext();
		curPtr = curPtr->getNext();
		prevPtr->setNext(curPtr);
		itemCount--;
		return true;
	}
	else
		return false;
}

template<class ItemType>
int LinkedSortedList<ItemType>::getPosition(const ItemType & newEntry) const
{
	std::shared_ptr<Node<ItemType>> curPtr = std::make_shared<Node<ItemType>>();
	curPtr = headPtr;
	int position = 1;
	while (curPtr != nullptr && curPtr->getItem() != newEntry)
	{
		curPtr = curPtr->getNext();
		position++;
	}
	if (curPtr == nullptr)
		return -1;
	else
		return position;
}

template<class ItemType>
bool LinkedSortedList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}

template<class ItemType>
int LinkedSortedList<ItemType>::getLength() const
{
   return itemCount;
}

template<class ItemType>
bool LinkedSortedList<ItemType>::remove(int position)
{
   bool ableToRemove = (position >= 1) && (position <= itemCount);
   if (ableToRemove)
   {
      if (position == 1)
      {
         headPtr = headPtr->getNext();
      }
      else
      {
         auto prevPtr = getNodeAt(position - 1);
         auto curPtr = prevPtr->getNext();
         prevPtr->setNext(curPtr->getNext());
      }  
      itemCount--;
   }
   return ableToRemove;
}

template<class ItemType>
void LinkedSortedList<ItemType>::clear()
{
   headPtr = nullptr;
   itemCount = 0;
}

template<class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) const
{
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
   {
      auto nodePtr = getNodeAt(position);
      return nodePtr->getItem();
   }
   else
   {
      std::string message = "getEntry() called with an empty list or ";
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message)); 
   }
}

template<class ItemType>
void displayLinkedSortedList(std::shared_ptr<SortedListInterface<ItemType>> sli)
{
	std::cout << "list: ";
	for (int i = 1; i <= sli->getLength(); i++)
	{
		std::cout << sli->getEntry(i) << " ";
	}
	std::cout << "\n";
}

int main()
{
	
	std::shared_ptr<SortedListInterface<int>> numbers;
	numbers = std::make_shared<LinkedSortedList<int>>();

	numbers->insertSorted(4);
	displayLinkedSortedList(numbers);
	numbers->insertSorted(6);
	displayLinkedSortedList(numbers);
	numbers->insertSorted(2);
	displayLinkedSortedList(numbers);
	numbers->insertSorted(3);
	displayLinkedSortedList(numbers);
	numbers->insertSorted(5);
	displayLinkedSortedList(numbers);
	numbers->insertSorted(9);
	displayLinkedSortedList(numbers);
	numbers->removeSorted(4);
	displayLinkedSortedList(numbers);
	numbers->removeSorted(5);
	displayLinkedSortedList(numbers);
	numbers->removeSorted(2);
	displayLinkedSortedList(numbers);
	numbers->removeSorted(9);
	displayLinkedSortedList(numbers);


/*
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);

	std::uniform_int_distribution<int> distribution(1, 100);
	int num;
	for (int i = 0; i < 21; ++i)
	{
		//		std::cout << distribution(generator) << " ";
		num = distribution(generator);
		std::cout << "inserting " << num << "\n";
		numbers->insertSorted(num);
		displayLinkedSortedList(numbers);
		std::cout << "\n";
	}
	std::cout << "removing " << num << "\n";
	numbers->removeSorted(num);
	displayLinkedSortedList(numbers);
*/
	return 0;
}
