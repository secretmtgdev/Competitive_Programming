#include "BinarySearchTree.h"
#include <vector>
#include <queue>
#include <stdlib.h>

BinarySearchTree::BinarySearchTree()
{
    _root = nullptr;
}

void BinarySearchTree::insert(int value)
{
    _root = insertUtil(_root, value, 1);
}

void BinarySearchTree::lazyDelete(int value)
{
    lazyDeleteUtil(_root, value);
}

bool BinarySearchTree::contains(int value)
{
    return containsUtil(_root, value);
}

void BinarySearchTree::preorderTraversal(BinarySearchNode *root)
{
    if (root)
    {
        if (root->getFrequency() == 0)
            printf(" x ");
        else
            printf(" %d ", root->getData());
        preorderTraversal(root->getLeft());
        preorderTraversal(root->getRight());
    }
}

void BinarySearchTree::inorderTraversal(BinarySearchNode *root)
{
    if (root)
    {
        inorderTraversal(root->getLeft());
        if (root->getFrequency() == 0)
            printf(" x ");
        else
            printf(" %d ", root->getData());
        inorderTraversal(root->getRight());
    }
}

void BinarySearchTree::postorderTraversal(BinarySearchNode *root)
{
    if (root)
    {
        postorderTraversal(root->getLeft());
        postorderTraversal(root->getRight());
        if (root->getFrequency() == 0)
            printf(" x ");
        else
            printf(" %d ", root->getData());
    }
}

void BinarySearchTree::levelorderTraversal(BinarySearchNode *root)
{
    std::queue<BinarySearchNode *> q;
    q.push(root);

    // push the reference indicating that the level has ended
    q.push(nullptr);
    int depth = 0;

    printf("depth %d: ", depth);
    while (!q.empty())
    {
        BinarySearchNode *top = q.front();

        // perform the action of extracting from the queue, avoids infinite loops
        q.pop();
        if (top)
        {
            printf("%d --> ", top->getData());
            if (top->getLeft())
                q.push(top->getLeft());
            if (top->getRight())
                q.push(top->getRight());
            // the level has ended
            if (!q.front())
            {
                printf("\ndepth %d: ", ++depth);
                q.push(nullptr);
            }
        }
    }
}

BinarySearchNode *BinarySearchTree::generateMinimalTree(std::vector<int> a)
{
    // sentinel node
    BinarySearchNode *root = new BinarySearchNode(-1);
    return generateMinimalTreeUtil(root, a, 0, a.size() - 1);
}

bool BinarySearchTree::isBalanced(BinarySearchNode *root)
{
    return isBalancedUtil(root) != INT16_MIN;
}

BinarySearchTree::~BinarySearchTree()
{
    cleanUp(_root);
}

// PRIVATE FUNCTIONS
void BinarySearchTree::cleanUp(BinarySearchNode *root)
{
    if (root)
    {
        // go left
        cleanUp(root->getLeft());

        // go right
        cleanUp(root->getRight());

        // delete
        delete root;
    }
}

bool BinarySearchTree::containsUtil(BinarySearchNode *root, int value)
{
    if (!root)
        return false;
    if (root->getData() == value)
        return true;
    else if (root->getData() < value)
        return containsUtil(root->getLeft(), value);
    else
        return containsUtil(root->getRight(), value);
}

BinarySearchNode *BinarySearchTree::findMin()
{
    BinarySearchNode *curr = _root;
    while (curr && curr->getLeft())
    {
        curr = curr->getLeft();
    }
    return curr;
}

BinarySearchNode *BinarySearchTree::findMax()
{
    BinarySearchNode *curr = _root;
    while (curr && curr->getRight())
    {
        curr = curr->getRight();
    }
    return curr;
}

BinarySearchNode *BinarySearchTree::insertUtil(BinarySearchNode *root, int value, int height)
{
    if (!root)
    {
        BinarySearchNode *newRoot = new BinarySearchNode(value);
        newRoot->setHeight(height);
        return newRoot;
    }
    if (root->getData() < value)
    {
        root->setRight(insertUtil(root->getRight(), value, height + 1));
    }
    else if (root->getData() > value)
    {
        root->setLeft(insertUtil(root->getLeft(), value, height + 1));
    }
    else
    {
        printf("incrementing frequency of the root due to duplicate\n");
        root->incrementFrequency();
        printf("finished incrementing frequency of the root due to duplicate\n");
    }
    return root;
}

void BinarySearchTree::lazyDeleteUtil(BinarySearchNode *root, int value)
{
    if (!root)
        return;
    if (root->getData() == value)
    {
        if (root->getFrequency() != 0)
        {
            root->decrementFrequency();
        }
        else
        {
            throw __EXCEPTIONS;
        }
    }
    if (root->getData() < value)
    {
        lazyDeleteUtil(root->getRight(), value);
    }
    else
    {
        lazyDeleteUtil(root->getLeft(), value);
    }
}

BinarySearchNode *BinarySearchTree::getRoot()
{
    return _root;
}

void BinarySearchTree::setRoot(BinarySearchNode *newRoot)
{
    cleanUp(_root);
    _root = newRoot;
}

BinarySearchNode *BinarySearchTree::generateMinimalTreeUtil(BinarySearchNode *root, std::vector<int> a, int lo, int hi)
{
    if (lo <= hi)
    {
        int mid = lo + (hi - lo) / 2;
        root = new BinarySearchNode(a[mid]);

        // left subtree
        root->setLeft(generateMinimalTreeUtil(root->getLeft(), a, lo, mid - 1));

        // right subtree
        root->setRight(generateMinimalTreeUtil(root->getRight(), a, mid + 1, hi));
    }
    return root;
}

int BinarySearchTree::isBalancedUtil(BinarySearchNode *root)
{
    if (!root)
        return -1;
    int leftHeight = isBalancedUtil(root->getLeft());
    if (leftHeight == INT16_MIN)
        return INT16_MIN;
    int rightHeight = isBalancedUtil(root->getRight());
    if (rightHeight == INT16_MIN)
        return INT16_MIN;

    int diff = abs(rightHeight - leftHeight);
    if (diff > 1)
        return INT16_MIN;
    else
        return std::max(leftHeight, rightHeight) + 1;
}