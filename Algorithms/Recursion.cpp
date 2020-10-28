#include <iostream>
#include <vector>
#include <array>

using namespace std;

const int DEFAULT_SIZE = 5;

///////////////////////////
// FUNCTION DECLARATIONS //
///////////////////////////
void mergeSort(int *);
void mergeSortUtil(int *, int, int);
void merge(int *, int, int, int);
void printArray(int *);

int main()
{
    int A[] = {5, 4, 3, 2, 1};
    printf("Original array:\n");
    printArray(A);
    mergeSort(A);
    printf("Sorted array:\n");
    printArray(A);
}

//////////////////////////////
// FUNCTION IMPLEMENTATIONS //
//////////////////////////////
void mergeSort(int *A)
{
    mergeSortUtil(A, 0, DEFAULT_SIZE - 1);
}

void mergeSortUtil(int *A, int lo, int hi)
{
    if (lo < hi)
    {
        int mid = lo + (hi - lo) / 2;
        mergeSortUtil(A, lo, mid);
        mergeSortUtil(A, mid + 1, hi);
        merge(A, lo, mid, hi);
    }
}

void merge(int *A, int lo, int mid, int hi)
{
    const int leftBound = mid - lo + 1;
    const int rightBound = hi - mid;
    int B[leftBound];
    int C[rightBound];
    for (int i = 0; i < leftBound; i++)
    {
        B[i] = A[lo + i];
    }

    for (int i = 0; i < rightBound; i++)
    {
        C[i] = A[mid + i + 1];
    }

    int i = 0, j = 0, k = lo;
    while (i < leftBound && j < rightBound)
    {
        A[k++] = B[i] <= C[j] ? B[i++] : C[j++];
    }

    while (i < leftBound)
    {
        A[k++] = B[i++];
    }

    while (j < rightBound)
    {
        A[k++] = C[j++];
    }
}

void printArray(int *A)
{
    printf("[%d", A[0]);

    for (int i = 1; i < DEFAULT_SIZE; i++)
    {
        printf(", %d", A[i]);
    }
    printf("]\n");
}