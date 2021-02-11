#include <stdio.h>
#include <stdlib.h>
#include "QuickSort.c"
#include "RadixSort.c"

int main() {
	int A[20] = {15,6,16,14,156,54,124,552,24,23,12,3,7,34,75,453,33,4133,51,5};
	QuickSort(A,20);
	int i;
	for (i=0; i<20; i++){
		printf("%d ",A[i]);
	}
	return 0;
} 
