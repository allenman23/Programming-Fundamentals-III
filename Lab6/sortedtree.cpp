#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include <random>
#include <chrono>
//#include <stdexcept>
//#include <cstddef>
//#include "stdafx.h"
#include "NotFoundException.h"
#include "PrecondViolatedExcep.h"
#include "BinaryNode.h"
#include "BinaryTreeInterface.h"
#include "BinaryNodeTree.h"// ADT binary tree operations
#include "BinarySearchTree.h"

void display(int& anItem)
{
	std::cout << anItem << " ";
}  // end display

int main()
{   /*
	std::shared_ptr<BinaryTreeInterface<int>> tree1;
	tree1 = std::make_shared<BinarySearchTree<int>>();

	int num = 5;
	
		unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
		std::default_random_engine generator(seed);
		std::uniform_int_distribution<int> distribution(1, 100);

		for (int i = 0; i < 21; ++i)
		{
			num = distribution(generator);
			std::cout << "inserting " << num << "\n";
			tree1->add(num);
		}
	
	tree1->add(20);
	tree1->add(10);
	tree1->add(5);
	tree1->add(15);
	tree1->add(30);
	tree1->add(25);
	tree1->add(35);
	std::cout << "Tree(inorder): ";
	tree1->inorderTraverse(display);
	std::cout << "\n";
	std::cout << "removing " << num << "\n";
	tree1->remove(num);
	std::cout << "Tree(inorder): ";
	tree1->inorderTraverse(display);
	std::cout << "\n";

	std::cout << "removing 20\n";
	tree1->remove(20);
	std::cout << "Tree(inorder): ";
	tree1->inorderTraverse(display);
	std::cout << "\n";

	std::cout << "removing 10\n";
	tree1->remove(10);
	std::cout << "Tree(inorder): ";
	tree1->inorderTraverse(display);
	std::cout << "\n";

	std::cout << "removing 15\n";
	tree1->remove(15);
	std::cout << "Tree(inorder): ";
	tree1->inorderTraverse(display);
	std::cout << "\n";

	std::cout << "removing 25\n";
	tree1->remove(25);
	std::cout << "Tree(inorder): ";
	tree1->inorderTraverse(display);
	std::cout << "\n";

	std::cout << "removing 30\n";
	tree1->remove(30);
	std::cout << "Tree(inorder): ";
	tree1->inorderTraverse(display);
	std::cout << "\n";

	std::cout << "removing 35\n";
	tree1->remove(35);
	std::cout << "Tree(inorder): ";
	tree1->inorderTraverse(display);
	std::cout << "\n";
	*/
	return 0;
}