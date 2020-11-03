#include "LinkedList.h"

LinkedList::LinkedList()
{
    _head = nullptr;
    _size = 0;
}

LinkedNode *LinkedList::find(int value)
{
    LinkedNode *currPtr = _head;
    while (currPtr)
    {
        if (currPtr->getData() == value)
        {
            return currPtr;
        }
        currPtr = currPtr->getNext();
    }
    return nullptr;
}

void LinkedList::insert(int value)
{
    LinkedNode *newNode = new LinkedNode(value);
    newNode->setNext(_head);
    _head = newNode;
    _size++;
}

void LinkedList::deleteAt(int idx)
{
    if (idx >= _size || idx < 0)
        return;
    if (idx == 0)
    {
        _head = _head->getNext();
    }
    else
    {
        int tmpIdx = 0;
        LinkedNode *currPtr = _head;
        while (tmpIdx < idx - 1)
        {
            currPtr = currPtr->getNext();
            tmpIdx++;
        }
        LinkedNode *next = currPtr->getNext();
        currPtr->setNext(next->getNext());
        delete next;
    }
    _size--;
}

int LinkedList::getSize()
{
    return _size;
}

LinkedList::~LinkedList()
{
    LinkedNode *currPtr = _head;
    while (currPtr)
    {
        LinkedNode *next = currPtr->getNext();
        delete currPtr;
        currPtr = next;
    }
    _head = nullptr;
}