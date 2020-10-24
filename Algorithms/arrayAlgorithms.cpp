#include <iostream>

// Include needed objects
#include <vector>
#include <queue>
#include "DataStructures/Point.h"
#include "DataStructures/SkylinePoint.h"

using namespace std;

//////////////////////////
// FUNCTION DECLARATION //
//////////////////////////
void nQueens(int);
int kadane(vector<int>);
vector<Point *> getSkylines(vector<tuple<int, int, int>>);
int magicIndex(vector<int>);

/////////////////////////////////
// HELPER FUNCTION DECLARATION //
/////////////////////////////////
bool underAttack(int, vector<Point *>, int, int);
bool nQueensUtil(int, int, vector<Point *>);
void printQueensBoard(int, vector<Point *>);
vector<SkylinePoint *> convertToSkylinePoints(vector<tuple<int, int, int>>);
priority_queue<int> removeFromQueue(int, priority_queue<int>);
bool sortSkylines(SkylinePoint *, SkylinePoint *);

int main()
{
    // print queens to 16x16 board
    // for (int i = 1; i <= 16; i++)
    // {
    //     nQueens(i);
    // }
    // vector<int> sequence = {1, 2, 3, -2, -3, 4, 5, -3, 2};
    // cout << "Largest sum in the given sequence: " << kadane(sequence) << endl;
    vector<tuple<int, int, int>> buildings = {
        make_tuple(1, 3, 3),
        make_tuple(2, 4, 4),
        make_tuple(5, 8, 2),
        make_tuple(6, 7, 4),
        make_tuple(8, 9, 4)};

    vector<Point *> skylines = getSkylines(buildings);
    printf("Printing %lu skylines:\n[ ", skylines.size());
    for (int i = 0; i < skylines.size(); i++)
    {
        Point *skylinePoint = skylines[i];
        printf("(%d, %d) ", skylinePoint->getRow(), skylinePoint->getCol());
    }
    printf("]\n");
}

/////////////////////////////
// FUNCTION IMPLEMENTATION //
/////////////////////////////
int magicIndex(vector<int> A)
{
    int lo = 0;
    int hi = A.size() - 1;
    while (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        if (mid == A[mid])
        {
            return mid;
        }
        else if (mid < A[mid])
        {
            // go left, values to the right are too high
            hi = mid - 1;
        }
        else
        {
            lo = mid + 1;
        }
    }

    // failed to find a magic number
    return -1;
}

vector<Point *> getSkylines(vector<tuple<int, int, int>> skylines)
{
    vector<SkylinePoint *> skylinePoints = convertToSkylinePoints(skylines);
    vector<Point *> result;
    sort(skylinePoints.begin(), skylinePoints.end(), sortSkylines);

    priority_queue<int> maxHeights;
    maxHeights.push(0);
    int currMaxHeight = 0;
    for (int i = 0; i < skylinePoints.size(); i++)
    {
        SkylinePoint *skyline = skylinePoints[i];
        int skylineHeight = skyline->getHeight();
        if (skyline->isStart())
        {
            maxHeights.push(skylineHeight);
        }
        else
        {
            maxHeights = removeFromQueue(skylineHeight, maxHeights);
        }
        int currMaxInQueue = maxHeights.top();
        if (currMaxInQueue != currMaxHeight)
        {
            currMaxHeight = currMaxInQueue;
            result.push_back(new Point(skyline->getX(), currMaxHeight));
        }
    }
    return result;
};

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
    // Using vector<Point *> positions(n, new Point(0, 0))
    // sets all of the indices to point to the same pont
    vector<Point *> positions;
    for (int i = 0; i < n; i++)
    {
        positions.push_back(new Point(-1, -1));
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
bool sortSkylines(SkylinePoint *A, SkylinePoint *B)
{
    bool samePoint = A->getX() == B->getX();

    bool sameStart = A->isStart() && B->isStart() && samePoint;
    bool sameEnd = !A->isStart() && !B->isStart() && samePoint;

    if (sameStart)
    {
        return A->getHeight() > B->getHeight();
    }
    else if (sameEnd)
    {
        return B->getHeight() < A->getHeight();
    }
    else if (samePoint && (A->isStart() != B->isStart()))
    {
        return A->isStart() ? A->getHeight() < B->getHeight() : B->getHeight() < A->getHeight();
    }
    else
    {
        return A->getX() < B->getX();
    }
}

// RT: O(n), SC: O(n)
priority_queue<int> removeFromQueue(int height, priority_queue<int> maxHeights)
{
    // temp queue
    priority_queue<int> tmpQueue;
    for (int i = 0; i < maxHeights.size(); i++)
    {
        // remove the top element but store it first
        int val = maxHeights.top();
        maxHeights.pop();
        if (val == height)
        {
            break;
        }
        tmpQueue.push(val);
    }

    while (!tmpQueue.empty())
    {
        maxHeights.push(tmpQueue.top());
        tmpQueue.pop();
    }
    return maxHeights;
}

vector<SkylinePoint *> convertToSkylinePoints(vector<tuple<int, int, int>> skylines)
{
    vector<SkylinePoint *> skylinePoints;
    for (int i = 0; i < skylines.size(); i++)
    {
        tuple<int, int, int> skyline = skylines[i];
        int start = get<0>(skyline);
        int end = get<1>(skyline);
        int height = get<2>(skyline);
        skylinePoints.push_back(new SkylinePoint(start, height, true));
        skylinePoints.push_back(new SkylinePoint(end, height, false));
    }
    return skylinePoints;
}

void printQueensBoard(int size, vector<Point *> positions)
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

bool underAttack(int queenIdx, vector<Point *> positions, int row, int col)
{
    // get the current queen
    Point currQueen = *positions[queenIdx];
    int qRow = currQueen.getRow();
    int qCol = currQueen.getCol();

    // the queens will never be in the same row, ignore
    return qRow - qCol == row - col || qRow + qCol == row + col || qCol == col;
}

bool nQueensUtil(int n, int row, vector<Point *> positions)
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
            Point *currPos = positions[row];
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