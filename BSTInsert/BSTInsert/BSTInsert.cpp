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
};

int main()
{
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

	bst.PrintInOrder(&pRoot);
	cout << "\n";
	bst.PrintPreOrder(&pRoot);
	cout << "\n";
	bst.PrintPostOrder(&pRoot);

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

	return 0;
}

