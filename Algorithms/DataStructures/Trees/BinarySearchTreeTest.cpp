#include <iostream>
#include <stdlib.h>
#include <vector>
#include <assert.h>
#include "BinarySearchTree.h"

using namespace std;

// Accessible functions
void testInsert();
void testDelete();
void testGenerateMinimalTree();
void testLCA();
void testSubtreeOf();

// Helper functions
BinarySearchTree *generateRandomTree(int);
void printCommonVisuals(BinarySearchTree *bst);
void cleanTree(BinarySearchTree *bst);

int main()
{
    testInsert();
    testDelete();
    testGenerateMinimalTree();
    testLCA();
    testSubtreeOf();
}

void testInsert()
{
    printf("TESTING INSERTION");
    BinarySearchTree *bst = generateRandomTree(6);

    printCommonVisuals(bst);

    cleanTree(bst);
    printf("\nFINISHED TESTING INSERTION\n");
}

void testDelete()
{
    printf("TESTING DELETION");

    BinarySearchTree *bst = generateRandomTree(6);
    bst->lazyDelete(6);

    printCommonVisuals(bst);
    cleanTree(bst);

    printf("\nFINISHED TESTING DELETION\n");
}

void testGenerateMinimalTree()
{
    printf("\nTESTING GENERATE MINIMAL TREE\n");
    vector<int> increasingOrder = {1, 2, 3, 4, 5, 6};
    BinarySearchTree *bst = new BinarySearchTree();
    bst->setRoot(bst->generateMinimalTree(increasingOrder));
    printCommonVisuals(bst);
    cleanTree(bst);
    printf("\nFINISHED TESTING GENERATE MINIMAL TREE\n");
}

void testLCA()
{
    printf("\nTESTING LCA \n");
    BinarySearchTree *bst = new BinarySearchTree();
    /** Visual that I am working with
     *       7
     *     /   \
     *    3     8
     *   / \    
     *  2   4
     *       \
     *        5
     */
    bst->insert(7);
    bst->insert(3);
    bst->insert(8);
    bst->insert(2);
    bst->insert(4);
    bst->insert(5);

    // Case: Two nodes in the same subtree[root-view], should return 3
    int p = 2, q = 5;
    BinarySearchNode *res = bst->LCA(p, q);
    assert(res->getData() == 3);
    printf("The LCA value of %d and %d is %d\n", p, q, res->getData());

    // Case: Two nodes in different subtrees[root-view], should return 7
    p = 3, q = 8;
    res = bst->LCA(p, q);
    assert(res->getData() == 7);
    printf("The LCA value of %d and %d is %d\n", p, q, res->getData());

    // Case: One node is the ancestor of both, should return 4
    p = 4, q = 5;
    res = bst->LCA(p, q);
    assert(res->getData() == 4);
    printf("The LCA value of %d and %d is %d\n", p, q, res->getData());
    cleanTree(bst);

    printf("\nFINISHED TESTING LCA \n");
}

void testSubtreeOf()
{
    printf("\nTESTING SUBTREE OF \n");
    BinarySearchTree *t1 = new BinarySearchTree();
    t1->insert(10);
    t1->insert(9);
    t1->insert(4);
    t1->insert(5);
    t1->insert(3);
    t1->insert(6);
    /** Visual of t1
     *           10
     *          / 
     *         9
     *        /
     *       4
     *      / \
     *     3   5
     *          \
     *           6
     */
    BinarySearchTree *t2 = new BinarySearchTree();
    /** Visual of t2
     *         5
     *        / \
     *       3   6
     */
    t2->insert(5);
    t2->insert(3);
    t2->insert(6);

    // Case: T2 is not a subtree of T1
    assert(!t1->containsSubtree(t2));
    printf("T2 is not a subtree of T1: %s\n", !t1->containsSubtree(t2) ? "true" : "false");

    delete t1;
    delete t2;

    // Case: T2 is a subtree of T1
    t1 = new BinarySearchTree();
    t1->insert(10);
    t1->insert(9);
    t1->insert(5);
    t1->insert(4);
    t1->insert(6);
    /** Visual of t1
     *           10
     *          / 
     *         9
     *        /
     *       5
     *      / \
     *     4   6
     */
    t2 = new BinarySearchTree();
    /** Visual of t2
     *         5
     *        / \
     *       4   6
     */
    t2->insert(5);
    t2->insert(4);
    t2->insert(6);
    assert(t1->containsSubtree(t2));
    printf("T2 is subtree of T1: %s\n", t1->containsSubtree(t2) ? "true" : "false");

    cleanTree(t1);
    cleanTree(t2);
    printf("\nFINISHED TESTING SUBTREE OF \n");
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

void cleanTree(BinarySearchTree *bst)
{
    delete bst;
    bst = NULL;
}