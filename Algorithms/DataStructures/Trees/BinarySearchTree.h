#include "BinarySearchNode.h"

class BinarySearchTree
{
private:
    BinarySearchNode *_root;
    void cleanUp(BinarySearchNode *);
    bool containsUtil(BinarySearchNode *, int);
    BinarySearchNode *findMin();
    BinarySearchNode *findMax();
    BinarySearchNode *insertUtil(BinarySearchNode *, int);
    void lazyDeleteUtil(BinarySearchNode *, int);

public:
    BinarySearchTree();
    void insert(int);
    void lazyDelete(int);
    bool contains(int);
    void preorderTraversal(BinarySearchNode *);
    void inorderTraversal(BinarySearchNode *);
    void postorderTraversal(BinarySearchNode *);
    BinarySearchNode *getRoot();
    ~BinarySearchTree();
};