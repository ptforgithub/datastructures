
#include <iostream>

class Node {
public :
	Node(int k) : data(k), pNext(NULL) { }
public:
	int data;
	Node *pNext;
};

class LinkedList {
public :
	LinkedList(): pHead(NULL) {}

	void Insert(int a[], int len) {
		for (int i = 0; i < len; i++) {
			InsertSorted(a[i]);
		}
	}

	void InsertSorted(int k) {
		if (!pHead) {
			pHead = new Node(k);
			return;
		}
		if (pHead->data > k) {
			// Need to replace Head
			Node *p = new Node(k);
			p->pNext = pHead;
			pHead = p;
			return;
		}
		Node *p = pHead;
		while (p->pNext) {
			if (k < p->pNext->data) {
				// Insert K between p and pnext
				Node *temp = p->pNext;
				p->pNext = new Node(k);
				p->pNext->pNext = temp;
				return;
			}
			p = p->pNext;
		}
		p->pNext = new Node(k);
	}

	void Insert(int k) {
		if (!pHead) {
			pHead = new Node(k);
			return;
		}
		Node *p = pHead;
		while (p->pNext) {
			p = p->pNext;
		}
		p->pNext = new Node(k);
	}

	void Print() {
		Node *p = pHead;
		while (p) {
			std::cout << p->data << ", ";
			p = p->pNext;
		}
	}

private :
	Node *pHead;
};

int main()
{
	LinkedList l;
	int a[] = { 5, 100, 30, 40, 56, 76 };
	l.Insert(a, sizeof(a) / sizeof(int));
	l.Print();

	return 0;
}

