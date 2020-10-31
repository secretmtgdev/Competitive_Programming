#include <iostream>
#include <vector>
#include <array>
#include <string>
#include <bitset>

using namespace std;

const int DEFAULT_SIZE = 5;
const int CHARACTER_SIZE = 8;

///////////////////////////
// FUNCTION DECLARATIONS //
///////////////////////////
void findSubsets(string);
void mergeSort(int *);

//////////////////////////////////
// HELPER FUNCTION DECLARATIONS //
//////////////////////////////////
void findSubsetsTests();
void printSubset(string, int);
void mergeSortTests();
void mergeSortUtil(int *, int, int);
void merge(int *, int, int, int);
void printArray(int *);

int main()
{
    //mergeSortTests();
    findSubsetsTests();
}

//////////////////////////////
// FUNCTION IMPLEMENTATIONS //
//////////////////////////////
void mergeSort(int *A)
{
    mergeSortUtil(A, 0, DEFAULT_SIZE - 1);
}

void findSubsets(string str)
{
    int totalSetCount = 1 << str.length();
    for (int i = 0; i < totalSetCount; i++)
    {
        printSubset(str, i);
    }
}

/////////////////////////////////////
// HELPER FUNCTION IMPLEMENTATIONS //
/////////////////////////////////////
void printSubset(string str, int bitNum)
{
    int len = str.length();
    if (len < 1)
        return;

    printf("[|%c|", (bitNum >> 0) & 1 ? str[0] : ' ');
    for (int i = 1; i < len; i++)
    {
        //printf("bit: %c", bits[i]);
        if ((bitNum >> i) & 1)
        {
            printf("|%c|", str[i]);
        }
        else
        {
            printf("| |");
        }
    }
    printf("]\n");
}

void findSubsetsTests()
{
    string str = "abc";
    findSubsets(str);
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

void mergeSortTests()
{
    int A[] = {5, 4, 3, 2, 1};
    printf("Original array:\n");
    printArray(A);
    mergeSort(A);
    printf("Sorted array:\n");
    printArray(A);
}