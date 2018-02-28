// BSTInsert.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <string>
#include <iostream>

using namespace std;

class Node {
public:
	Node(int key, string data = "Hello") {
		_key = key;
		_data = data;
		pLeft = NULL;
		pRight = NULL;
	};
public:
	int _key;
	string _data;
	Node *pLeft;
	Node *pRight;
};

class BST {
public:
	BST() {
		pRoot = NULL;
	}

	Node &Insert(int key) {
		Node *pNode = new Node(key);
		Insert(*pNode);
		return *pRoot;
	}

	void PrintInOrder(Node *pRoot) {
		// Left -> Root -> Right
		if (pRoot->pLeft) {
			PrintInOrder(pRoot->pLeft);
		}
		cout << pRoot->_key << ",";
		if (pRoot->pRight) {
			PrintInOrder(pRoot->pRight);
		}
	}

	void PrintPreOrder(Node *pRoot) {
		// Root -> Left -> Right
		cout << pRoot->_key << ",";
		if (pRoot->pLeft) {
			PrintPreOrder(pRoot->pLeft);
		}
		if (pRoot->pRight) {
			PrintPreOrder(pRoot->pRight);
		}
	}

	void PrintPostOrder(Node *pRoot) {
		// Left -> Right -> Root
		if (pRoot->pLeft) {
			PrintPreOrder(pRoot->pLeft);
		}
		if (pRoot->pRight) {
			PrintPreOrder(pRoot->pRight);
		}
		cout << pRoot->_key << ",";
	}

	Node *Search(int key) {
		return SearchInternal(key, pRoot);
	}

	Node *FindLCA(int a, int b) {
		// The node which has 'a' on one side and 'b' on the other is the LCA
		Node *pA = Search(a);
		Node *pB = Search(b);

		if ((!pA) || (!pB)) {
			return NULL;
		}

		Node *pCurr = pRoot;
		while (pCurr) {
			if (pCurr->_key == a)
				return pCurr;
			if (pCurr->_key == b)
				return pCurr;

			bool foundA = SearchInternal(a, pCurr->pLeft) != NULL;
			bool foundB = SearchInternal(b, pCurr->pRight) != NULL;

			if ((foundA && foundB) || ((!foundA) && (!foundB))) {
				return pCurr;
			}
			else if (foundA && (!foundB)) {
				// Both are on the left sub-tree
				pCurr = pCurr->pLeft;
			}
			else {
				pCurr = pCurr->pRight;
			}
		}

		return NULL;
	}

	Node *FindKthSmallestElement(int k) {
		elementIndex = -1;
		return FindKthSmallestInternal(k, pRoot);
	}

private:
	Node *pRoot;

	Node &Insert(Node &node) {
		if (pRoot == NULL) {
			pRoot = &node;
			return *pRoot;
		}

		Node *pCurrent = pRoot;

		while (pCurrent) {
			if (pCurrent->_key == node._key) {
				break; // Do not insert duplicates
			}
			if (pCurrent->_key > node._key) {
				if (!pCurrent->pLeft) {
					pCurrent->pLeft = &node;
					break;
				}
				pCurrent = pCurrent->pLeft;
			}
			else {
				if (!pCurrent->pRight) {
					pCurrent->pRight = &node;
					break;
				}
				pCurrent = pCurrent->pRight;
			}
		}

		return (*pRoot);
	}

	Node *SearchInternal(int key, Node *pCurrNode) {
		if (pCurrNode == NULL)
			return NULL;
		if (key == pCurrNode->_key) {
			return pCurrNode;
		}
		if (pCurrNode->_key > key) {
			return SearchInternal(key, pCurrNode->pLeft);
		}
		else {
			return SearchInternal(key, pCurrNode->pRight);
		}
	}

	Node *FindKthSmallestInternal(int k, Node *pCurr) {
		if (!pCurr) {
			return NULL;
		}

		if (pCurr->pLeft) {
			Node *p = FindKthSmallestInternal(k, pCurr->pLeft);
			if (elementIndex == k) {
				return p;
			}
		}
		// Do something with pCurr
		elementIndex++;
		if (elementIndex == k) {
			return pCurr;
		}

		if (pCurr->pRight) {
			Node *p = FindKthSmallestInternal(k, pCurr->pRight);
			if (elementIndex == k) {
				return p;
			}
		}

		return NULL;
	}

	int elementIndex;
};

int main()
{
	// Insert
	BST bst;
	Node &pRoot = 
	bst.Insert(5);
	bst.Insert(25);
	bst.Insert(55);
	bst.Insert(34);
	bst.Insert(24);
	bst.Insert(45);
	bst.Insert(5); // Duplicate ..
	bst.Insert(63);
	bst.Insert(9);
	bst.Insert(3);

	//                    5
	//                3       25
	//                    24      55
	//                 9       34    63
	//                           45

	// Traversal - In-Order, Pre-Order, Post-Order
	bst.PrintInOrder(&pRoot);
	cout << "\n";
	bst.PrintPreOrder(&pRoot);
	cout << "\n";
	bst.PrintPostOrder(&pRoot);

	// Search Tree
	Node *pNode = bst.Search(5);
	cout << ((pNode) ? pNode->_key : -1) << "\n";

	pNode = bst.Search(56);
	cout << ((pNode) ? pNode->_key : -1) << "\n";

	pNode = bst.Search(34);
	cout << ((pNode) ? pNode->_key : -1) << "\n";

	pNode = bst.Search(24);
	cout << ((pNode) ? pNode->_key : -1) << "\n";

	pNode = bst.Search(63);
	cout << ((pNode) ? pNode->_key : -1) << "\n";

	pNode = bst.Search(51);
	cout << ((pNode) ? pNode->_key : -1) << "\n";

	// Find Least Common Ancestor of 2 nodes
	pNode = bst.FindLCA(34, 63);
	pNode = bst.FindLCA(55, 63);
	pNode = bst.FindLCA(34, 45);
	pNode = bst.FindLCA(9, 63);
	pNode = bst.FindLCA(9, 45);
	pNode = bst.FindLCA(9, 34);

	// Find Kth Smallest Element
	pNode = bst.FindKthSmallestElement(0); // Smallest of all
	pNode = bst.FindKthSmallestElement(1); // Smallest of all
	pNode = bst.FindKthSmallestElement(2); // Smallest of all
	pNode = bst.FindKthSmallestElement(3); // Smallest of all
	pNode = bst.FindKthSmallestElement(4); // Smallest of all
	pNode = bst.FindKthSmallestElement(5); // Smallest of all
	pNode = bst.FindKthSmallestElement(8); // Smallest of all
	pNode = bst.FindKthSmallestElement(10); // Smallest of all

	return 0;
}

