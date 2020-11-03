#include <iostream>
#include <stdlib.h>
#include "BinarySearchTree.h"

void testInsert();
void testDelete();
BinarySearchTree *generateRandomTree(int);

int main()
{
    testInsert();
    testDelete();
}

void testInsert()
{
    printf("TESTING INSERTION");
    BinarySearchTree *bst = generateRandomTree(6);

    printf("\nPre order: ");
    bst->preorderTraversal(bst->getRoot());
    printf("\nIn order: ");
    bst->inorderTraversal(bst->getRoot());
    printf("\nPost order: ");
    bst->postorderTraversal(bst->getRoot());

    printf("\nFINISHED TESTING INSERTION\n");
}

void testDelete()
{
    printf("TESTING DELETION");

    BinarySearchTree *bst = generateRandomTree(6);
    bst->lazyDelete(6);

    printf("\nPre order: ");
    bst->preorderTraversal(bst->getRoot());
    printf("\nIn order: ");
    bst->inorderTraversal(bst->getRoot());
    printf("\nPost order: ");
    bst->postorderTraversal(bst->getRoot());

    printf("\nFINISHED TESTING DELETION\n");
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