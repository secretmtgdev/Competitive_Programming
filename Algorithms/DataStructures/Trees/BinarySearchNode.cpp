#include "BinarySearchNode.h"

BinarySearchNode::BinarySearchNode(int data)
{
    _data = data;
    _height = -1;
    _left = nullptr;
    _right = nullptr;
    _frequency = 1;
}

int BinarySearchNode::getData()
{
    return _data;
}

BinarySearchNode *BinarySearchNode::getLeft()
{
    return _left;
}

BinarySearchNode *BinarySearchNode::getRight()
{
    return _right;
}

void BinarySearchNode::setData(int data)
{
    _data = data;
}

void BinarySearchNode::setLeft(BinarySearchNode *left)
{
    _left = left;
}

void BinarySearchNode::setRight(BinarySearchNode *right)
{
    _right = right;
}

int BinarySearchNode::getFrequency()
{
    return _frequency;
}

void BinarySearchNode::decrementFrequency()
{
    _frequency--;
}

void BinarySearchNode::incrementFrequency()
{
    _frequency++;
}

int BinarySearchNode::getHeight()
{
    return _height;
}

void BinarySearchNode::setHeight(int height)
{
    _height = height;
}