#include <iostream>
#include <stdlib.h>
#include <vector>
#include "BinarySearchTree.h"

using namespace std;

// Accessible functions
void testInsert();
void testDelete();
void testGenerateMinimalTree();

// Helper functions
BinarySearchTree *generateRandomTree(int);
void printCommonVisuals(BinarySearchTree *bst);

int main()
{
    testInsert();
    testDelete();
    testGenerateMinimalTree();
}

void testInsert()
{
    printf("TESTING INSERTION");
    BinarySearchTree *bst = generateRandomTree(6);

    printCommonVisuals(bst);

    printf("\nFINISHED TESTING INSERTION\n");
}

void testDelete()
{
    printf("TESTING DELETION");

    BinarySearchTree *bst = generateRandomTree(6);
    bst->lazyDelete(6);

    printCommonVisuals(bst);

    printf("\nFINISHED TESTING DELETION\n");
}

void testGenerateMinimalTree()
{
    printf("\nTESTING GENERATE MINIMAL TREE\n");
    vector<int> increasingOrder = {1, 2, 3, 4, 5, 6};
    BinarySearchTree *bst = new BinarySearchTree();
    bst->setRoot(bst->generateMinimalTree(increasingOrder));
    printCommonVisuals(bst);
    printf("\nFINISHED TESTING GENERATE MINIMAL TREE\n");
}

BinarySearchTree *generateRandomTree(int size)
{
    BinarySearchTree *bst = new BinarySearchTree();
    bst->insert(size);
    for (int i = 0; i < size; i++)
    {
        bst->insert(rand() % (2 * size));
    }
    return bst;
}

void printCommonVisuals(BinarySearchTree *bst)
{
    printf("\nPre order: ");
    bst->preorderTraversal(bst->getRoot());
    printf("\nIn order: ");
    bst->inorderTraversal(bst->getRoot());
    printf("\nPost order: ");
    bst->postorderTraversal(bst->getRoot());
    printf("\nLevel order: \n");
    bst->levelorderTraversal(bst->getRoot());
    printf("\nBalanced?: %s", bst->isBalanced(bst->getRoot()) ? "true" : "false");
    printf("\n");
}