// Allen Lim

#include<iostream>
#include <memory>
#include <stdexcept>
#include <string>
//#include<random>
//#include<ctime>

template<class ItemType>
class Node
{
private:
   ItemType        item; // A data item
   std::shared_ptr<Node<ItemType>> next; // Pointer to next node
   
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
	/** Inserts an entry into this sorted list in its proper order
		so that the list remains sorted.
	 @pre  None.
	 @post  newEntry is in the list, and the list is sorted.
	 @param newEntry  The entry to insert into the sorted list. */
	virtual void insertSorted(const ItemType& newEntry) = 0;

	/** Removes the first or only occurrence of the given entry from this
		sorted list.
	 @pre  None.
	 @post  If the removal is successful, the first occurrence of the
		given entry is no longer in the sorted list, and the returned
		value is true. Otherwise, the sorted list is unchanged and the
		returned value is false.
	 @param anEntry  The entry to remove.
	 @return  True if removal is successful, or false if not. */
	virtual bool removeSorted(const ItemType& anEntry) = 0;

	/** Gets the position of the first or only occurrence of the given
		entry in this sorted list. In case the entry is not in the list,
		determines where it should be if it were added to the list.
	 @pre  None.
	 @post  The position where the given entry is or belongs is returned.
		The sorted list is unchanged.
	 @param anEntry  The entry to locate.
	 @return  Either the position of the given entry, if it occurs in the
		sorted list, or the position where the entry would occur, but as a
		negative integer. */
	virtual int getPosition(const ItemType& anEntry) const = 0;

	// The following methods are the same as those given in ListInterface
	// in Listing 8-1 of Chapter 8 and are completely specified there.

	/** Sees whether this list is empty. */
	virtual bool isEmpty() const = 0;

	/** Gets the current number of entries in this list. */
	virtual int getLength() const = 0;

	/** Removes the entry at a given position from this list. */
	virtual bool remove(int position) = 0;

	/** Removes all entries from this list. */
	virtual void clear() = 0;

	/** Gets the entry at the given position in this list. */
	virtual ItemType getEntry(int position) const = 0;

	/** Destroys object and frees memory allocated by object. */
	virtual ~SortedListInterface() { }
};

template<class ItemType>
class LinkedSortedList : public SortedListInterface<ItemType>
{
private:
	Node<ItemType>* headPtr; // Pointer to first node in the chain
	int itemCount; // Current count of list items
// Locates the node that is before the node that should or does
// contain the given entry.
// @param anEntry The entry to find.
// @return Either a pointer to the node before the node that contains
// or should contain the given entry, or nullptr if no prior node exists. 
	Node<ItemType>* getNodeBefore(const ItemType& anEntry) const;
// Locates the node at a given position within the chain.
	Node<ItemType>* getNodeAt(int position) const;
// Returns a pointer to a copy of the chain to which origChainPtr points.
	Node<ItemType>* copyChain(const Node<ItemType>* origChainPtr);

public:
	LinkedSortedList();
	LinkedSortedList(const LinkedSortedList<ItemType>& aList);
	virtual ~LinkedSortedList();
	void insertSorted(const ItemType& newEntry);
	bool removeSorted(const ItemType& anEntry);
	int getPosition(const ItemType& newEntry) const;
// The following methods are the same as given in ListInterface:
	bool isEmpty() const;
	int getLength() const;
	bool remove(int position);
	void clear();
	ItemType getEntry(int position)/* const throw(PrecondViolatedExcep)*/;
};

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeBefore(const ItemType& anEntry) const
{
	Node<ItemType>* curPtr = headPtr;
	Node<ItemType>* prevPtr = nullptr;
	while ( (curPtr != nullptr) && (anEntry > curPtr->getItem()) ) 
	{
		prevPtr = curPtr;
		curPtr = curPtr->getNext();
	} // end while
	return prevPtr;
} // end getNodeBefore

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::getNodeAt(int position) const
{
	Node<ItemType>* curPtr = headPtr;
	for (int i = 1; i < position; i++)
		curPtr = curPtr->getNext();
	return curPtr;
}

template<class ItemType>
Node<ItemType>* LinkedSortedList<ItemType>::copyChain(const Node<ItemType>* origChainPtr)
{
	Node<ItemType>* copiedChainPtr;
	if (origChainPtr == nullptr)
	{
	copiedChainPtr = nullptr;
	itemCount = 0; 
	}
	else
	{
		Node<ItemType>* copiedChainPtr = new Node<ItemType>(origChainPtr->getItem());
		copiedChainPtr->setNext(copyChain(origChainPtr->getNext()));
		itemCount++; 
	} // end if
	return copiedChainPtr;
} // end copyChain

template<class ItemType>
LinkedSortedList<ItemType>::LinkedSortedList() : headPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
LinkedSortedList<ItemType>::
LinkedSortedList(const LinkedSortedList<ItemType>& aList) 
{
	headPtr = copyChain(aList.headPtr); 
}

template<class ItemType>
LinkedSortedList<ItemType>::~LinkedSortedList()
{
   clear();
}

template<class ItemType>
void LinkedSortedList<ItemType>::insertSorted(const ItemType& newEntry)
{
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);
	Node<ItemType>* prevPtr = getNodeBefore(newEntry);
	if (isEmpty() || (prevPtr == nullptr)) // Add at beginning 
	{
   		newNodePtr->setNext(headPtr);
		headPtr = newNodePtr;
	}
	else // Add after node before
	{
		Node<ItemType>* aftPtr = prevPtr->getNext();
		newNodePtr->setNext(aftPtr);
		prevPtr->setNext(newNodePtr);
	} // end if
	itemCount++;
} // end insertSorted

template<class ItemType>
bool LinkedSortedList<ItemType>::removeSorted(const ItemType & anEntry)
{
	if (getPosition >= 1)
	{
		Node<ItemType>* prevPtr = getNodeBefore(anEntry);
		Node<ItemType>* curPtr = prevPtr->getNext();
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
	Node<ItemType>* curPtr = headPtr;
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
}  // end isEmpty

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
         // Remove the first node in the chain
         headPtr = headPtr->getNext();
      }
      else
      {
         // Find node that is before the one to delete
         auto prevPtr = getNodeAt(position - 1);
         
         // Point to node to delete
         auto curPtr = prevPtr->getNext();
         
         // Disconnect indicated node from chain by connecting the
         // prior node with the one after
         prevPtr->setNext(curPtr->getNext());
      }  // end if
      
      itemCount--;  // Decrease count of entries
   }  // end if
   
   return ableToRemove;
}

template<class ItemType>
void LinkedSortedList<ItemType>::clear()
{
//   headPtr.reset();
   headPtr = nullptr; // is OK also
   itemCount = 0;
}

template<class ItemType>
ItemType LinkedSortedList<ItemType>::getEntry(int position) // const throw(PrecondViolatedExcep)
{
   // Enforce precondition
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
   }  // end if
}

template<class ItemType>
void displaySortedList(SortedListInterface<ItemType>& sli)
{
	std::cout << "list: ";
	for (int i = 1; i <= sli.getLength(); i++)
	{
		std::cout << sli.getEntry(i) << " ";
	}
}

int main()
{
	LinkedSortedList<int> nums;
	nums.insertSorted(9);
	nums.insertSorted(7);
	nums.insertSorted(1);
	nums.insertSorted(10);
	nums.insertSorted(5);
	displaySortedList(nums);
	return 0;
}
