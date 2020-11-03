#include "BinarySearchTree.h"
#include <stack>

BinarySearchTree::BinarySearchTree()
{
    _root = nullptr;
}

void BinarySearchTree::insert(int value)
{
    _root = insertUtil(_root, value);
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

BinarySearchTree::~BinarySearchTree()
{
    cleanUp(_root);
}

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

BinarySearchNode *BinarySearchTree::insertUtil(BinarySearchNode *root, int value)
{
    if (!root)
    {
        return new BinarySearchNode(value);
    }
    if (root->getData() < value)
    {
        root->setRight(insertUtil(root->getRight(), value));
    }
    else if (root->getData() > value)
    {
        root->setLeft(insertUtil(root->getLeft(), value));
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