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

	// Not straight forward
	Node *FindInOrderSuccessor(int k) {
		return FindInOrderSuccessorInternal(k, pRoot);
	}

	Node *FindInOrderSuccessorInternal(int k, Node *pCurr) {
		if (!pCurr)
			return NULL;
		
		if (k < pCurr->_key) {
			// K is on the left subtree
			if (!pCurr->pLeft)
				return pCurr; // Or we could return NULL based on our definition
			if (k > pCurr->pLeft->_key) {
				return pCurr; // Again, depending on our def
			}
			if (k < pCurr->pLeft->_key) {
				Node *p = FindInOrderSuccessorInternal(k, pCurr->pLeft);
				return p;
			}
			if (k == pCurr->pLeft->_key) {
				// K is the left child of pCurr
				Node *p = pCurr->pLeft->pRight;
				if (!p)
					return pCurr; // Left child of pCurr has no right child
				p = FindMin(pCurr->pLeft->pRight);
				return p;
			}
		}
		else if (k == pCurr->_key) {
			// K is pCurr
			Node *p = FindMin(pCurr->pRight);
			return p;
		}
		else if (k > pCurr->_key) {
			// K is on the right of pCurr
			Node *p = FindInOrderSuccessorInternal(k, pCurr->pRight);
			return p;
		}
		// This should not reach ..
		return NULL;
	}

	// This is tricky !!
	Node *Delete(int k) {
		// https://www.youtube.com/watch?v=gcULXE7ViZw
		// https://www.geeksforgeeks.org/binary-search-tree-set-2-delete/
		pRoot = DeleteInternalAndReturnNewRoot(k, pRoot);
		return pRoot;
	}

	~BST() {
		pRoot = Free(pRoot);
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

	// This is tricky !!
	Node *DeleteInternalAndReturnNewRoot(int k, Node *pCurr) {
		// Delete the node with key == k
		// And return the new root of the tree

		//                    5
		//                3       25
		//                    24      55
		//                 9       34    63
		//                           45

		// Suppose we have to delete 5, look at the lowest in right tree and replace 5 by this value, so that 9 becomes the root. return 9

		// Case 0: pCurr == NULL
		if (!pCurr) {
			return NULL;
		}

		// Case 1: Delete 3
		if (pCurr->_key > k) {
			pCurr->pLeft = DeleteInternalAndReturnNewRoot(k, pCurr->pLeft);
			return pCurr;
		}
		// Case 2: Delete 24
		if (pCurr->_key < k) {
			pCurr->pRight = DeleteInternalAndReturnNewRoot(k, pCurr->pRight);
			return pCurr;
		}
		// Case 3: Delete 5
		if (pCurr->_key == k) {
			// Find the min in Right sub tree == 9
			// Replace 5's value with 9's value
			// Delete 9 from the right subtree; the new root should be assigned as 5's right
			if (!pCurr->pRight) {
				Node *pLeft = pCurr->pLeft;
				delete pCurr;
				return pLeft;
			}
			if (!pCurr->pLeft) {
				Node *pRight = pCurr->pRight;
				delete pCurr;
				return pRight;
			}

			Node *pMin = FindMin(pCurr->pRight);
			pCurr->_key = pMin->_key;
			pCurr->pRight = DeleteInternalAndReturnNewRoot(pMin->_key, pCurr->pRight);
			return pCurr;
		}

	}

	Node *FindMin(Node *p) {
		if (!p) return NULL;
		while (p->pLeft) {
			p = p->pLeft;
		}
		return p;
	}

	Node *FindMax(Node *p) {
		if (!p) return NULL;
		while (p->pRight) {
			p = p->pRight;
		}
		return p;
	}

	Node *Free(Node *pCurr) {
		if (!pCurr)
			return NULL;
		Free(pCurr->pLeft);
		Node *pRight = pCurr->pRight;
		delete pCurr;
		Free(pRight);
		return NULL;
	}
};

BST *GetNewBST() {
	//                    5
	//                3       25
	//                    24      55
	//                 9       34    63
	//                           45

	BST *pBST = new BST();
	Node &pRoot =
		pBST->Insert(5);
	pBST->Insert(25);
	pBST->Insert(55);
	pBST->Insert(34);
	pBST->Insert(24);
	pBST->Insert(45);
	pBST->Insert(5); // Duplicate ..
	pBST->Insert(63);
	pBST->Insert(9);
	pBST->Insert(3);

	return pBST;
}

void Delete(int k) {
	BST *pBST = GetNewBST();
	pBST->Delete(k);
	delete pBST;
}

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
	pNode = bst.FindKthSmallestElement(1);
	pNode = bst.FindKthSmallestElement(2);
	pNode = bst.FindKthSmallestElement(3);
	pNode = bst.FindKthSmallestElement(4);
	pNode = bst.FindKthSmallestElement(5);
	pNode = bst.FindKthSmallestElement(8);
	pNode = bst.FindKthSmallestElement(10); // Out of range - should return NULL

	// Delete
	Delete(5);
	Delete(3);
	Delete(25);
	Delete(55);
	Delete(34);
	Delete(24);
	Delete(45);
	Delete(63);
	Delete(9);
	Delete(3);
	Delete(11);

	//                    5
	//                3       25
	//                    24      55
	//                 9       34    63
	//                           45

	// Inorder Successor
	pNode = bst.FindInOrderSuccessor(5);
	pNode = bst.FindInOrderSuccessor(3);
	pNode = bst.FindInOrderSuccessor(25);
	pNode = bst.FindInOrderSuccessor(24);
	pNode = bst.FindInOrderSuccessor(55);
	pNode = bst.FindInOrderSuccessor(9);
	pNode = bst.FindInOrderSuccessor(34);
	pNode = bst.FindInOrderSuccessor(63);
	pNode = bst.FindInOrderSuccessor(45);
	pNode = bst.FindInOrderSuccessor(11);
	return 0;
}

