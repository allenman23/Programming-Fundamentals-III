cmake_minimum_required (VERSION 3.8)
project(lab6_library)

add_library("BinaryNode.cpp" "BinaryNode.h" "BinaryNodeTree.cpp" "BinaryNodeTree.h" 
			"BinaryTreeInterface.h" "NotFoundException.h" "PrecondViolatedExcep.h"
			"BinarySearchTree.cpp" "BinarySearchTree.h"
			"sortedtree.cpp")

add_executable(sortedtree_exe  "BinaryNode.cpp" "BinaryNodeTree.cpp" "BinarySearchTree.cpp" "sortedtree.cpp")