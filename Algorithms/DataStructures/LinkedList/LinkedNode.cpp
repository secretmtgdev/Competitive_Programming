#include "LinkedNode.h"

LinkedNode::LinkedNode(int data)
{
    _data = data;
    _next = nullptr;
}

int LinkedNode::getData()
{
    return _data;
}

LinkedNode *LinkedNode::getNext()
{
    return _next;
}

void LinkedNode::setData(int data)
{
    _data = data;
}

void LinkedNode::setNext(LinkedNode *next)
{
    _next = next;
}