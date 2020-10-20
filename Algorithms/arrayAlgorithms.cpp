#include <iostream>
#include <vector>
#include "data_structures/point.h"

using namespace std;

//////////////////////////
// FUNCTION DECLARATION //
//////////////////////////
void nQueens(int);
int kadane(vector<int>);

/////////////////////////////////
// HELPER FUNCTION DECLARATION //
/////////////////////////////////
bool underAttack(int, vector<point *>, int, int);
bool nQueensUtil(int, int, vector<point *>);
void printQueensBoard(int, vector<point *>);

int main()
{
    // print queens to 16x16 board
    // for (int i = 1; i <= 16; i++)
    // {
    //     nQueens(i);
    // }
    vector<int> sequence = {1, 2, 3, -2, -3, 4, 5, -3, 2};
    cout << "Largest sum in the given sequence: " << kadane(sequence) << endl;
}

/////////////////////////////
// FUNCTION IMPLEMENTATION //
/////////////////////////////
// RT: O(n)
// Assumption is that the array contains at least one value
int kadane(vector<int> arr)
{
    if (arr.size() < 1)
        return INT16_MIN;
    int max_so_far = arr[0];
    int max_global = arr[0];
    for (int i = 1; i < arr.size(); i++)
    {
        int currVal = arr[i];
        max_so_far = max(max_so_far + currVal, currVal);
        max_global = max(max_so_far, max_global);
    }
    return max_global;
}

// RT: O(2^n), SC: O(n)
void nQueens(int n)
{
    // initialize n vector positions
    // Using vector<point *> positions(n, new point(0, 0))
    // sets all of the indices to point to the same pont
    vector<point *> positions;
    for (int i = 0; i < n; i++)
    {
        positions.push_back(new point(-1, -1));
    }
    bool hasSolution = nQueensUtil(n, 0, positions);
    if (hasSolution)
    {
        printf("Solution found for queens problem of size %d\n", n);
        printQueensBoard(n, positions);
    }
    else
    {
        printf("No solution found for queens problem of size %d\n", n);
    }
    printf("\n");
}

////////////////////////////////////
// HELPER FUNCTION IMPLEMENTATION //
////////////////////////////////////
void printQueensBoard(int size, vector<point *> positions)
{
    char queenBoard[size][size];

    // blank the board
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            queenBoard[i][j] = '-';
        }
    }

    for (int i = 0; i < positions.size(); i++)
    {
        int row = positions[i]->getRow();
        int col = positions[i]->getCol();
        queenBoard[row][col] = 'Q';
    }

    // print the board
    for (int i = 0; i < size; i++)
    {
        cout << "[ ";
        for (int j = 0; j < size; j++)
        {
            cout << queenBoard[i][j] << " ";
        }
        cout << "]" << endl;
    }
}

bool underAttack(int queenIdx, vector<point *> positions, int row, int col)
{
    // get the current queen
    point currQueen = *positions[queenIdx];
    int qRow = currQueen.getRow();
    int qCol = currQueen.getCol();

    // the queens will never be in the same row, ignore
    return qRow - qCol == row - col || qRow + qCol == row + col || qCol == col;
}

bool nQueensUtil(int n, int row, vector<point *> positions)
{
    // found the solution
    if (row == n)
    {
        return true;
    }

    for (int col = 0; col < n; col++)
    {
        // assume that the current position is safe
        bool safe = true;

        // check to see if this row and column is under attack
        for (int i = 0; i < row; i++)
        {
            if (underAttack(i, positions, row, col))
            {
                safe = false;

                // stop the search
                break;
            }
        }

        if (safe)
        {
            // mark the current position as a safe placement
            point *currPos = positions[row];
            currPos->setRow(row);
            currPos->setCol(col);
            // check all other positions in the recursion tree
            if (nQueensUtil(n, row + 1, positions))
            {
                return true;
            }
        }
    }
    return false;
}