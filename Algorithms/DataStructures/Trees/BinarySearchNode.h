#pragma once

class BinarySearchNode
{
private:
    int _data;
    int _frequency;
    int _height;
    BinarySearchNode *_left, *_right;

public:
    BinarySearchNode(int);
    int getData();
    BinarySearchNode *getLeft();
    BinarySearchNode *getRight();
    void setData(int);
    void setLeft(BinarySearchNode *left);
    void setRight(BinarySearchNode *right);
    int getFrequency();
    void decrementFrequency();
    void incrementFrequency();
    int getHeight();
    void setHeight(int);
};