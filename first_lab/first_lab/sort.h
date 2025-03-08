#pragma once
#ifndef SORT_H
#define SORT_H

double* make_random_arr(int n);
int* make_random_arr_int(int n);
double* make_random_arr_sort(int n);
void delete_random_arr(double* arr);
void delete_random_arr_int(int* arr);
int swap(double* a, double* b);
void bubbleSort(double* arr, int elements);
void selectSort(double* arr, int end);
void insertSort(double* arr, int end);
void merge(double* array, int left, int mid, int right);
void mergeSort(double* array, int left, int right);
int partition(double* array, int low, int high);
void quickSort(double* array, int low, int high);
void hybridQuickSort(double* array, int low, int high);
int getMax(int arr[], int n);
void countSort(int arr[], int n, int exp);
void radixSort(int arr[], int n);
int checkSorted(double* arr, int n);
int checkSorted_int(int* arr, int n);

#endif