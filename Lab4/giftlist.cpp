// Allen Lim

#include<iostream>
#include<string>
#include<memory>

class GiftNode
{
private:
	std::string item;
	std::shared_ptr<GiftNode> next;

public:
	GiftNode() {};
	GiftNode(const std::string& anItem) { item = anItem; };
	GiftNode(const std::string& anItem, std::shared_ptr<GiftNode> nextGiftNodePtr) {
		item = anItem;
		next = nextGiftNodePtr;
	};
	void setItem(const std::string& anItem) { item = anItem; };
	void setNext(std::shared_ptr<GiftNode> nextGiftNodePtr) { next = nextGiftNodePtr; };
	std::string getItem() const { return item; };
	auto getNext() const { return next; };
};


template<class ItemType>
class LinkedList
{
private:
	std::shared_ptr<ItemType> headPtr;
	int itemCount;

public:
	LinkedList();
	LinkedList(const LinkedList<ItemType>& aList);
	virtual ~LinkedList();

	bool isEmpty() const;
	int getLength() const;
	bool insert(int newPosition, const std::string& newEntry);
	bool remove(int position);
	void clear();
	auto getNodeAt(int position) const;

	std::string getEntry(int position);

	void replace(int position, const std::string& newEntry);
};

template<class ItemType>
LinkedList<ItemType>::LinkedList() : headPtr(nullptr), itemCount(0)
{
}

template<class ItemType>
LinkedList<ItemType>::LinkedList(const LinkedList<ItemType>& aList) : itemCount(aList.itemCount)
{
	auto origChainPtr = aList.headPtr;  // Points to nodes in original chain

	if (origChainPtr == nullptr)
		headPtr.reset();  // Original list is empty
	else
	{
		// Copy first node
		headPtr = std::make_shared<ItemType>();
		headPtr->setItem(origChainPtr->getItem());

		// Copy remaining nodes
		auto newChainPtr = headPtr;      // Points to last node in new chain
		origChainPtr = origChainPtr->getNext();     // Advance original-chain pointer
		while (origChainPtr != nullptr)
		{
			// Get next item from original chain
			ItemType nextItem = origChainPtr->getItem();

			// Create a new node containing the next item 
			auto newNodePtr = std::make_shared<ItemType>(nextItem);

			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			// Advance pointer to new last node      
			newChainPtr = newChainPtr->getNext();

			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNext();
		}

		newChainPtr->setNext(nullptr);              // Flag end of chain
	}
}

template<class ItemType>
LinkedList<ItemType>::~LinkedList()
{
	clear();
}

template<class ItemType>
bool LinkedList<ItemType>::isEmpty() const
{
	return itemCount == 0;
}

template<class ItemType>
int LinkedList<ItemType>::getLength() const
{
	return itemCount;
}

template<class ItemType>
bool LinkedList<ItemType>::insert(int newPosition, const std::string& newEntry)
{
	bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
	if (ableToInsert)
	{
		// Create a new node containing the new entry 
		auto newNodePtr = std::make_shared<ItemType>(newEntry);

		// Attach new node to chain
		if (newPosition == 1)
		{
			// Insert new node at beginning of chain
			newNodePtr->setNext(headPtr);
			headPtr = newNodePtr;
		}
		else
		{
			// Find node that will be before new node
			auto prevPtr = getNodeAt(newPosition - 1);

			// Insert new node after node to which prevPtr points
			newNodePtr->setNext(prevPtr->getNext());
			prevPtr->setNext(newNodePtr);
		}

		itemCount++;  // Increase count of entries
	}

	return ableToInsert;
}

template<class ItemType>
bool LinkedList<ItemType>::remove(int position)
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
	}

	return ableToRemove;
}

template<class ItemType>
void LinkedList<ItemType>::clear()
{
	headPtr.reset();
	itemCount = 0;
}

template<class ItemType>
std::string LinkedList<ItemType>::getEntry(int position)
{
	// Enforce precondition
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		auto nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	}
}

template<class ItemType>
void LinkedList<ItemType>::replace(int position, const std::string& newEntry)
{
	// Enforce precondition
	bool ableToSet = (position >= 1) && (position <= itemCount);
	if (ableToSet)
	{
		auto nodePtr = getNodeAt(position);
		nodePtr->setItem(newEntry);
	}
}

template<class ItemType>
auto LinkedList<ItemType>::getNodeAt(int position) const
{
	auto curPtr = headPtr;
	for (int skip = 1; skip < position; skip++)
		curPtr = curPtr->getNext();

	return curPtr;
}

class KidNode
{
private:
	LinkedList<GiftNode> kidgifts;
	std::string item;
	std::shared_ptr<KidNode> next;

public:
	KidNode() {};
	KidNode(const std::string& anItem) { item = anItem; };
	KidNode(const std::string& anItem, std::shared_ptr<KidNode> nextKidNodePtr) {
		item = anItem;
		next = nextKidNodePtr;
	};
	void setItem(const std::string& anItem) { item = anItem; };
	void setNext(std::shared_ptr<KidNode> nextKidNodePtr) { next = nextKidNodePtr; };
	std::string getItem() const { return item; };
	auto getNext() const { return next; };
	void appendGift(std::string gift);
	auto getGifts() const { return kidgifts; };
};

void KidNode::appendGift(std::string gift)
{
	kidgifts.insert(kidgifts.getLength() + 1, gift);
}

void displayKids(LinkedList<KidNode>& list)
{
	std::cout << "The list contains\n";
	for (int pos = 1; pos <= list.getLength(); pos++)
	{
		std::cout << list.getEntry(pos) << ": ";
		for (int i = 1; i <= list.getNodeAt(pos)->getGifts().getLength(); i++)
			std::cout << list.getNodeAt(pos)->getGifts().getEntry(i) << " ";
		std::cout << "\n";
	}
}

int main()
{
	LinkedList<KidNode> kids;
	std::string giftName;
	std::string kidName;
	do
	{
		std::cout << "name for nice list: ";
		std::getline(std::cin, kidName);
		if (kidName != "")
		{
			kids.insert(kids.getLength() + 1, kidName);
			std::cout << "add gifts for " << kidName << "\n";
			do
			{
				std::cout << "gift: ";
				std::getline(std::cin, giftName);
				if (giftName != "")
					kids.getNodeAt(kids.getLength())->appendGift(giftName);
			} while (giftName != "");
			std::cout << "\n";
		}
	} while (kidName != "");
	std::cout << "\n";
	displayKids(kids);
	return 0;
}
