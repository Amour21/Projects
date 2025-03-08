#include <stdio.h>
#include <stdlib.h>
#include "sort.h"
#include <time.h>


double* make_random_arr(int n) {
	double* arr = (double*)malloc(n * sizeof(double));
	for (int i = 0; i < n; i++) {
		arr[i] = rand() * (21.0 / 100.0);
	}
	return arr;
}
int* make_random_arr_int(int n) {
	int* arr = (int*)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++) {
		arr[i] = rand();
	}
	return arr;
}
double* make_random_arr_sort(int n) {
	double* arr = (double*)malloc(n * sizeof(double));
	double first = rand() * (21.0 / 100.0);
	for (int i = 0; i < n; i++) {
		arr[i] = first + 2*i;
	}
	return arr;
}
int* make_random_arr_sort_int(int n) {
	int* arr = (int*)malloc(n * sizeof(double));
	int first = rand() ;
	for (int i = 0; i < n; i++) {
		arr[i] = first + 2 * i;
	}
	return arr;
}
double* make_random_arr_unsort(int n) {
	double* arr = (double*)malloc(n * sizeof(double));
	double first =RAND_MAX - rand() * (21.0 / 100.0);
	for (int i = 0; i < n; i++) {
		arr[i] = first - 2 * i;
	}
	return arr;
}
int* make_random_arr_unsort_int(int n) {
	int* arr = (int*)malloc(n * sizeof(double));
	int first = RAND_MAX - rand();
	for (int i = 0; i < n; i++) {
		arr[i] = first - 2 * i;
	}
	return arr;
}
void delete_random_arr(double* arr) {
	free(arr);
}
void delete_random_arr_int(int* arr) {
	free(arr);
}
int swap(double* a, double* b) {
	double temp = *a;
	*a = *b;
	*b = temp;
	return *a, * b;
}
void bubbleSort(double* arr, int end) {
		for (int i = 0; i < end - 1; i++) {
			int flag = 0;
			for (int j = 0; j < end - i - 1; j++) {
				if (arr[j] > arr[j + 1]) {
					swap(&arr[j], &arr[j + 1]);
					flag = 1;
				}
			}
			if (flag != 1) break;
		}
}
void selectSort(double* arr, int end) {
	int index;
		for (int i = 0; i < end - 1; i++) {
			index = i;
			for (int j = i + 1; j < end; j++) {
				if (arr[index] > arr[j]) index = j;
			}
			if (index != i) swap(&arr[i], &arr[index]);

		}
}
void insertSort(double* arr, int end) {
	for (int i = 1; i < end; i++) {
		double key = arr[i];  
		int j = i - 1;

		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = arr[j];  
			j--;
		}
		arr[j + 1] = key;
	}
}
void merge(double* array, int left, int mid, int right) {
	int n1 = mid - left + 1;
	int n2 = right - mid;
	double* L = (double*)malloc(n1 * sizeof(double));
	double* R = (double*)malloc(n2 * sizeof(double));
	for (int i = 0; i < n1; i++) {
		L[i] = array[left + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = array[mid + 1 + j];
	}
	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			array[k] = L[i];
			i++;
		}
		else {
			array[k] = R[j];
			j++;
		}
		k++;
	}
	while (i < n1) {
		array[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		array[k] = R[j];
		j++;
		k++;
	}

	free(L);
	free(R);
}
void mergeSort(double* array, int left, int right) {
	if (left < right) {
		int mid = left + (right - left) / 2;
		mergeSort(array, left, mid);
		mergeSort(array, mid + 1, right);
		merge(array, left, mid, right);
	}
}
int medianOfThree(double* array, int low, int high) {
	int mid = low + (high - low) / 2;
	if (array[low] > array[mid]) swap(&array[low], &array[mid]);
	if (array[low] > array[high]) swap(&array[low], &array[high]);
	if (array[mid] > array[high]) swap(&array[mid], &array[high]);
	return mid; 
}
int partition(double* array, int low, int high) {
	
	int pivotIndex = medianOfThree(array, low, high);
	double pivot = array[pivotIndex];
	swap(&array[pivotIndex], &array[high]);  

	int i = low - 1;
	for (int j = low; j < high; j++) {
		if (array[j] <= pivot) {
			i++;
			swap(&array[i], &array[j]);
		}
	}
	swap(&array[i + 1], &array[high]);
	return i + 1;
}
void quickSort(double* array, int low, int high) {
	if (low < high) {
		int pivotIndex = partition(array, low, high);
		quickSort(array, low, pivotIndex - 1);  
		quickSort(array, pivotIndex + 1, high); 
	}
}
void hybridQuickSort(double* array, int low, int high) {
	
	int threshold = 128;
	if (high - low + 1 <= threshold) {
		insertSort(array + low, high - low + 1);
	}
	else {
		quickSort(array, low, high);  
	}
}
int getMax(int arr[], int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) {
			max = arr[i];
		}
	}
	return max;
}
void countSort(int arr[], int n, int exp) {
	int* output = (int*)malloc(n * sizeof(int));  
	int* count = (int*)malloc(10 * sizeof(int));  
	for (int i = 0; i < 10; i++) {
		count[i] = 0;
	}
	for (int i = 0; i < n; i++) {
		count[(arr[i] / exp) % 10]++;
	}
	for (int i = 1; i < 10; i++) {
		count[i] += count[i - 1];
	}
	for (int i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}
	for (int i = 0; i < n; i++) {
		arr[i] = output[i];
	}
	free(output);
	free(count);
}
void radixSort(int arr[], int n) {
	int max = getMax(arr, n);
	for (int exp = 1; max / exp > 0; exp *= 10) {
		countSort(arr, n, exp);
	}
}
int checkSorted(double* arr, int n) {
	for (int i = 1; i < n; i++) {
		if (arr[i - 1] > arr[i]) {
			printf("Not correct\n");
			return -1;
		}
	}
	return 1;
}
int checkSorted_int(int* arr_int, int n) {
	for (int i = 1; i < n; i++) {
		if (arr_int[i - 1] > arr_int[i]) {
			return -1;
		}
	}
	return 1;
}
