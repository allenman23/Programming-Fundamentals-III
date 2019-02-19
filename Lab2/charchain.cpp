// Allen Lim

#include <iostream>
#include <string>

class Node {
private:
	char item;
	Node * next;
public:
	Node(char aitem) :item(aitem), next(nullptr) {}
	char getItem();
	void setItem(char aitem);
	Node* getNext();
	void setNext(Node* anode);
};

char Node::getItem()
{
	return item;
}

void Node::setItem(char aitem)
{
	item = aitem;
}

Node * Node::getNext()
{
	return next;
}

void Node::setNext(Node* anode)
{
	next = anode;
}

class LinkedChar
{
private:
	Node * head;
	int itemCount;
public:
	LinkedChar();
	LinkedChar(std::string s);
	void display();
	void add(const char item);
	int length() const;
	void append(const LinkedChar& lc);
	bool submatch(const LinkedChar& lc) const;
	int index(char ch) const;
	~LinkedChar();
};

LinkedChar::LinkedChar()
{
	head = nullptr;
	itemCount = 0;
}

LinkedChar::LinkedChar(std::string s)
{
	for (int i = 0; i < s.length(); i++) 
		add(s[i]);
}

void LinkedChar::display() 
{
	Node * curr = head;
	std::cout << "LinkedChar: '";
	while (curr != nullptr) {
		std::cout << curr->getItem();
		curr = curr->getNext();
	}
	std::cout << "'";
}

void LinkedChar::add(const char item) 
{
	Node * newNode = new Node(item);
	//newNode->setNext(head);
	//head = newNode;
	if (head == nullptr)
		head = newNode;
	else 
	{
		Node* curr = head;
		while (curr->getNext() != nullptr)
			curr = curr->getNext();
		curr->setNext(newNode);
	}
	itemCount++;
}

int LinkedChar::length() const 
{
	return itemCount;
}

void LinkedChar::append(const LinkedChar & lc) 
{
	Node* curr = lc.head;
	while (curr != nullptr) 
	{
		add(curr->getItem());
		curr = curr->getNext();
	}
}

bool LinkedChar::submatch(const LinkedChar & lc) const 
{
	Node* lcPtr = head;
	Node* subPtr = lc.head;
	while (lcPtr != nullptr)
	{
		if (lcPtr->getItem() == subPtr->getItem() && subPtr->getNext() == nullptr) // match and end of sub (submatch is true)
			return true;
		else if (lcPtr->getItem() == subPtr->getItem()) // match but not end of sub (move both pointers)
		{
			lcPtr = lcPtr->getNext();
			subPtr = subPtr->getNext();
		}
		else if (lc.head->getItem() == lcPtr->getItem()) // no match but sub.head matches lcPtr->getItem (don't move lcPtr and reset subPtr)
			subPtr = lc.head;
		else // no match and sub.head doesn't match lcPtr->getItem (move lcPtr)
			lcPtr = lcPtr->getNext();
	}
	return false;
}

int LinkedChar::index(char ch) const 
{
		int lcindex = 1;
		Node * curr = head;
		while (curr != nullptr  && curr->getItem() != ch) 
		{
			++lcindex;
			curr = curr->getNext();
		}
		if (curr == nullptr)
			return -1;
		else
			return lcindex;
}

LinkedChar::~LinkedChar() 
{
	while (head != nullptr) 
	{
		Node *oldPtr = head;
		head = head->getNext();
		delete oldPtr;
	}
}

void menuDisplay()
{
	std::cout << "LinkedChar Menu\n\n";
//	std::cout << "[0] Enter a string and convert to LinkedChar\n";
	std::cout << "[1] Get length of current LinkedChar\n";
	std::cout << "[2] Find index of char in LinkedChar\n";
	std::cout << "[3] Append AppendLinkedChar to LinkedChar\n";
	std::cout << "[4] Test if SubLinkedChar is a submatch of LinkedChar\n";
	std::cout << "[5] Exit\n\n";
}

int main() 
{
	std::string newstring;
	std::cout << "Enter a string and convert to LinkedChar: ";
	std::getline(std::cin, newstring);
	std::cout << "\n";
	LinkedChar currentlc(newstring);
	int choice = 0;
	while (choice != 5)
	{
		menuDisplay();
		currentlc.display();
		std::cout << "\n\nEnter selection [1-5]: ";
		std::cin >> choice;
		std::cout << "\n";
		/*		if (choice == 0)
				{
					std::cout << "Enter a string and convert to LinkedChar: ";
					std::cin.ignore();
					std::getline(std::cin, newstring);
					std::cout << "\n";
					LinkedChar currentlc(newstring);
					currentlc.display();
					std::cout << "\n\n";
				}
				else
		*/
		if (choice == 1)
			std::cout << "Length of LinkedChar: " << currentlc.length() << "\n\n";
		else if (choice == 2)
		{
			char charsearch;
			std::cout << "Enter char to search for: ";
			std::cin >> charsearch;
			std::cout << "\nIndex of char in LinkedChar (starting from 1): " << currentlc.index(charsearch) << "\n\n";
		}
		else if (choice == 3)
		{
			std::string appendstring;
			std::cout << "Enter AppendLinkedChar and append to LinkedChar: ";
			std::cin.ignore();
			std::getline(std::cin, appendstring);
			LinkedChar appendlc(appendstring);
			currentlc.append(appendlc);
			std::cout << "\n";
			currentlc.display();
			std::cout << "\n\n";
		}
		else if (choice == 4)
		{
			std::string substring;
			std::cout << "Enter SubLinkedChar and search for match in LinkedChar: ";
			std::cin.ignore();
			std::getline(std::cin, substring);
			LinkedChar sublc(substring);
			std::cout << "\nSubLinkedChar found in LinkedChar: ";
			if (currentlc.submatch(sublc))
				std::cout << "TRUE\n\n";
			else
				std::cout << "FALSE\n\n";
		}
	}
	return 0;
}


