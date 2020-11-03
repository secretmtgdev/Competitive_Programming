#pragma once

class LinkedNode
{
private:
    int _data;
    LinkedNode *_next;

public:
    LinkedNode(int);
    int getData();
    LinkedNode *getNext();
    void setData(int);
    void setNext(LinkedNode *);
};
