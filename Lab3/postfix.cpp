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
	Node* origChainPtr = aStack.topPtr;

	if (origChainPtr == nullptr)
		topPtr = nullptr;
	else
	{
		topPtr = new Node();
		topPtr->setItem(origChainPtr->getItem());

		Node* newChainPtr = topPtr;

		origChainPtr = origChainPtr->getNext();

		while (origChainPtr != nullptr)
		{
			int nextItem = origChainPtr->getItem();
			Node* newNodePtr = new Node(nextItem);
			newChainPtr->setNext(newNodePtr);
			newChainPtr = newChainPtr->getNext();
			origChainPtr = origChainPtr->getNext();
		}
		newChainPtr->setNext(nullptr);
	}
}

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
		Node* nodeToDeletePtr = topPtr;
		topPtr = topPtr->getNext();
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
	return 0;
}