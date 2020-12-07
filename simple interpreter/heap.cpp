#include "heap.h"
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

void swapVariables(variable** n1, variable ** n2) {
    variable **temp = n1;
    n1 = n2;
    n2 = temp;
}

void heapify(variable arr[], int n, int i)
{
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    // If left child is larger than root
    if (left < n && arr[left].value > arr[largest].value)
        largest = left;

    // If right child is larger than largest so far
    if (right < n && arr[right].value >arr[largest].value)
        largest = right;

    // If largest is not root
    if (largest != i)
    {
        variable temp = arr[largest];
		arr[largest] = arr[i];
		arr[i] = temp;
        heapify(arr, n, largest);
    }
}

void heapSort(variable arr[],int n)
{
    // Build heap (rearrange array)
    for (int i = (n / 2)- 1; i >= 0; i--)
        heapify(arr, n, i);
    // One by one extract an element from heap
    variable temp;
    for (int i=n-1; i>0; i--)
    {
        // Move current root to end
        //swapVariables(&myHeap->arr[0], &myHeap->arr[i]);
        temp = arr[0];
		arr[0] = arr[i];
		arr[i] = temp;
        // call max heapify on the reduced heap
        heapify(arr, i, 0);
    }
}

