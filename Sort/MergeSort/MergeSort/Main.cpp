
#include <iostream>


void Swap(int &a, int &b) {
	int temp = a;
	a = b;
	b = temp;
}

void Merge(int a[], int lenA, int b[], int lenB) {
	int *res = new int[lenA + lenB];
	int indexA = 0, indexB = 0;
	for (int i = 0; i < lenA + lenB; i++) {
		if (indexA == lenA && indexB < lenB) {
			// All of A already copied
			res[i] = b[indexB];
			indexB++;
		}
		else if (indexB == lenB && indexA < lenA) {
			// All of B already copied
			res[i] = a[indexA];
			indexA++;
		}
		else {

			if (a[indexA] < b[indexB]) {
				res[i] = a[indexA];
				indexA++;
			}
			else {
				res[i] = b[indexB];
				indexB++;
			}
		}
	}
	for (int i = 0; i < lenA + lenB; i++) {
		if (i < lenA) {
			a[i] = res[i];
		}
		else {
			b[i - lenA] = res[i];
		}
	}
}

void MergeSort(int a[], int len) {
	if (len < 2)
		return;
	if (len == 2) {
		if (a[0] > a[1]) {
			Swap(a[0], a[1]);
		}
		return;
	}

	MergeSort(a, len / 2);
	MergeSort(a + (len / 2), len - len / 2);

	Merge(a, len / 2, a + len / 2, len - (len / 2));
}



int main()
{
	int a[] = { 50, 20, 40, 30, 10, 67, 89, 45, 3, 25 };

	MergeSort(a, sizeof(a) / sizeof(int));

	return 0;
}
