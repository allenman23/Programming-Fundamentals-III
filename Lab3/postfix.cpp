// Allen Lim

#include<iostream>
#include<string>

class Node
{
private:
	int item;
	Node* next;

public:
	Node();
	Node(const int& anItem);
	Node(const int& anItem, Node* nextNodePtr);
	void setItem(const int& anItem);
	void setNext(Node* nextNodePtr);
	int getItem() const;
	Node* getNext() const;
};


Node::Node() : next(nullptr)
{
}

Node::Node(const int& anItem) : item(anItem), next(nullptr)
{
}

Node::Node(const int& anItem, Node* nextNodePtr) :
	item(anItem), next(nextNodePtr)
{
}

void Node::setItem(const int& anItem)
{
	item = anItem;
}

void Node::setNext(Node* nextNodePtr)
{
	next = nextNodePtr;
}

int Node::getItem() const
{
	return item;
}

Node* Node::getNext() const
{
	return next;
}


class LinkedStack
{

private:
	Node* topPtr;
public:
	LinkedStack();
	LinkedStack(const LinkedStack& aStack);
	virtual ~LinkedStack();

	bool isEmpty() const;
	bool push(const int& newItem);
	bool pop();
	int peek();
	void display();
};


LinkedStack::LinkedStack() : topPtr(nullptr)
{
}

LinkedStack::LinkedStack(const LinkedStack& aStack)
{
	// Point to nodes in original chain
	Node* origChainPtr = aStack.topPtr;

	if (origChainPtr == nullptr)
		topPtr = nullptr;  // Original stack is empty
	else
	{
		// Copy first node
		topPtr = new Node();
		topPtr->setItem(origChainPtr->getItem());

		// Point to last node in new chain
		Node* newChainPtr = topPtr;

		// Advance original-chain pointer
		origChainPtr = origChainPtr->getNext();

		// Copy remaining nodes
		while (origChainPtr != nullptr)
		{
			// Get next item from original chain
			int nextItem = origChainPtr->getItem();

			// Create a new node containing the next item
			Node* newNodePtr = new Node(nextItem);

			// Link new node to end of new chain
			newChainPtr->setNext(newNodePtr);

			// Advance pointer to new last node
			newChainPtr = newChainPtr->getNext();

			// Advance original-chain pointer
			origChainPtr = origChainPtr->getNext();
		}  // end while

		newChainPtr->setNext(nullptr);               // Flag end of chain
	}  // end if
}  // end copy constructor

LinkedStack::~LinkedStack()
{
	while (!isEmpty())
		pop();
}

bool LinkedStack::isEmpty() const
{
	return (topPtr == nullptr);
}

bool LinkedStack::push(const int& newEntry)
{
	Node* newNodePtr = new Node(newEntry, topPtr);
	topPtr = newNodePtr;
	newNodePtr = nullptr;
	return true;
}

bool LinkedStack::pop()
{
	bool result = false;
	if (!isEmpty())
	{
		// Stack is not empty; delete top
		Node* nodeToDeletePtr = topPtr;
		topPtr = topPtr->getNext();

		// Return deleted node to system
		nodeToDeletePtr->setNext(nullptr);
		delete nodeToDeletePtr;
		nodeToDeletePtr = nullptr;

		result = true;
	}
	return result;
}

int LinkedStack::peek()
{
	return topPtr->getItem();
}

void LinkedStack::display()
{
	Node * curr = topPtr;
	std::cout << "LinkedStack: '";
	while (curr != nullptr) {
		std::cout << curr->getItem();
		curr = curr->getNext();
	}
	std::cout << "'\n";
}

int evalPostfix(std::string postfixstring)
{
	LinkedStack stackInt;
	int convertToInt;
	for (int i = 0; i < postfixstring.length(); i++)
	{
		convertToInt = postfixstring[i] - '0';
		if (convertToInt >= 0 && convertToInt <= 9)
			stackInt.push(convertToInt);
		else
		{
			int operand2 = stackInt.peek();
			stackInt.pop();
			int operand1 = stackInt.peek();
			stackInt.pop();
			int result;
			switch (postfixstring[i])
			{
			case '+':
				result = operand1 + operand2;
				break;
			case '-':
				result = operand1 - operand2;
				break;
			case '*':
				result = operand1 * operand2;
				break;
			case '/':
				result = operand1 / operand2;
				break;
			}
			stackInt.push(result);
		}
	}
	return stackInt.peek();
}

int main()
{
	LinkedStack ls;
	std::string string1("234+*");
	int convertToInt;
	std::cout << string1 << " = " << evalPostfix(string1) << "\n\n";
	string1 = "123*+4+";
	std::cout << string1 << " = " << evalPostfix(string1) << "\n\n";
	string1 = "12+34+*";
	std::cout << string1 << " = " << evalPostfix(string1) << "\n\n";
	string1 = "12*34*+";
	std::cout << string1 << " = " << evalPostfix(string1) << "\n\n";
	std::cin >> string1;
	return 0;
}