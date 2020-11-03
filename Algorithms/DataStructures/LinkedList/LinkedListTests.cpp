#include <iostream>
#include "LinkedList.h"

using namespace std;

void testInsert();
void testDelete();
void testFind();

int main()
{
    testInsert();
    testDelete();
    testFind();
}

void testInsert()
{
    printf("TESTING INSERTION\n");
    LinkedList *newList = new LinkedList();
    for (int i = 0; i < 5; i++)
    {
        newList->insert(i + 1);
    }

    printf("Size of list: %d\n", newList->getSize());
}

void testDelete()
{
    printf("TESTING DELETION\n");
    LinkedList *newList = new LinkedList();
    for (int i = 0; i < 5; i++)
    {
        newList->insert(i + 1);
    }

    printf("Size of list before deletion: %d\n", newList->getSize());
    newList->deleteAt(0);
    printf("Size of list after deletion at front: %d\n", newList->getSize());
    newList->deleteAt(2);
    printf("Size of list after deletion at valid idx: %d\n", newList->getSize());
    newList->deleteAt(-1);
    printf("Size of list after deletion at invalid idx: %d\n", newList->getSize());
}

void testFind()
{
    printf("TESTING FIND\n");
    LinkedList *newList = new LinkedList();
    for (int i = 0; i < 5; i++)
    {
        newList->insert(i + 1);
    }

    int idx = 3;
    printf("Finding node at valid index %d: %d\n", idx, newList->find(idx)->getData());
    idx = -1;
    printf("Finding node at invalid index %d: %d\n", idx, newList->find(idx) ? newList->find(idx)->getData() : INT16_MIN);
}