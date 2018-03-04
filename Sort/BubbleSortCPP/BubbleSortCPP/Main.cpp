
#include <iostream>

void Print(int a[], int len);
void Swap(int *a, int *b);
void BubbleSort(int a[], int len, bool(*f)(int, int));
bool CompareAscending(int a, int b);

int main() {

	int a[] = { 50, 20, 40, 30, 60, 80, 90, 15, 5, 35 };
	int len = sizeof(a) / sizeof(int);
	BubbleSort(a, len, CompareAscending);

	Print(a, len);

	return 0;
}

void BubbleSort(int a[], int len, bool(*f)(int, int)) {
	for (int i = 0; i < len; i++) {
		for (int j = len - 1; j > i; j--) {
			if (f(a[j], a[i])) {
				Swap(&a[j], &a[i]);
			}
		}
	}
}

bool CompareAscending(int a, int b) {
	return a < b;
}

void Swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void Print(int a[], int len) {
	for (int i = 0; i < len; i++) {
		std::cout << a[i] << ", ";
	}
	std::cout << "\n";
}
