#pragma once
#include "LinkedNode.h"

class LinkedList
{
private:
    LinkedNode *_head;
    int _size;

public:
    LinkedList();
    void insert(int);
    LinkedNode *find(int);
    void deleteAt(int);
    int getSize();
    ~LinkedList();
};
