#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sort.h"


int main() {
	srand(1382);
	double time_taken = 0.0;
	int choose1, choose2,choose3;
	clock_t start = 0;
	clock_t finish = 0;
	printf("Choose sort: \n 1. Bubble sort \n 2.Selection sort \n 3. Insert  sort \n ");
	printf("4. Merge sort \n 5. Quick sort \n 6. Smart quick sort \n 7. Radix sort \n");
	scanf_s("%d", &choose1);
	printf("How many random elements you want sort? ");
	scanf_s("%d", &choose2);
	int* arr_int = NULL;
	double* arr = NULL;
	//printf("Do you want test accuracy of sorting? 1 - yes no - else ");
	//scanf_s("%d", &choose3);
	if (choose1 !=7) arr = make_random_arr(choose2);
	else arr_int = make_random_arr_int(choose2);
	switch (choose1)
	{
	case 1:
		
		arr = make_random_arr(choose2);
		start = clock();
		bubbleSort(arr, choose2);
		finish = clock();
		time_taken = (finish - start) / CLOCKS_PER_SEC;
		break;
	case 2:
		start = clock();
		selectSort(arr, choose2);
		finish = clock();
		break;
	case 3:
		insertSort(arr, choose2);
		finish = clock();
		break;
	case 4:
		start = clock();
		mergeSort(arr,0, choose2-1);
		finish = clock();
		break;
	case 5:
		start = clock();
		quickSort(arr, 0, choose2 - 1);
		finish = clock();
		break;
	case 6:
		start = clock();
		hybridQuickSort(arr, 0, choose2 - 1);
		finish = clock();
		break;
	case 7:
		start = clock();
		radixSort(arr_int, choose2);
		finish = clock();
		break;
	default:
		return -1;
	}
	time_taken =((double) (finish - start)) / CLOCKS_PER_SEC;
	printf("Time taken %lf\n", time_taken);
	/* if (choose3 == 1) {
		if (choose1 != 7) {
			if (checkSorted(arr, choose2) == 1) printf("Correct");
			else printf("Not correct");
		}
		else {
			if (checkSorted_int(arr_int, choose2) == 1) printf("Correct");
			else printf("Not correct");
		}
	}*/
	if (choose1 != 7) delete_random_arr(arr);
	else delete_random_arr_int(arr_int);
}