#include "BinarySearchNode.h"
#include <vector>

class BinarySearchTree
{
private:
    BinarySearchNode *_root;
    void cleanUp(BinarySearchNode *);
    bool containsUtil(BinarySearchNode *, int);
    BinarySearchNode *findMin();
    BinarySearchNode *findMax();
    BinarySearchNode *insertUtil(BinarySearchNode *, int, int);
    void lazyDeleteUtil(BinarySearchNode *, int);
    BinarySearchNode *generateMinimalTreeUtil(BinarySearchNode *, std::vector<int>, int, int);
    int isBalancedUtil(BinarySearchNode *);
    BinarySearchNode *LCAUtil(BinarySearchNode *, int, int);
    bool sameTreeUtil(BinarySearchNode *, BinarySearchNode *);
    bool containsSubtreeUtil(BinarySearchNode *, BinarySearchNode *);

public:
    BinarySearchTree();
    void insert(int);
    void lazyDelete(int);
    bool contains(int);
    void preorderTraversal(BinarySearchNode *);
    void inorderTraversal(BinarySearchNode *);
    void postorderTraversal(BinarySearchNode *);
    void levelorderTraversal(BinarySearchNode *);
    bool isBalanced(BinarySearchNode *);
    BinarySearchNode *generateMinimalTree(std::vector<int>);
    BinarySearchNode *getRoot();
    void setRoot(BinarySearchNode *);
    BinarySearchNode *LCA(int, int);
    bool containsSubtree(BinarySearchTree *);
    ~BinarySearchTree();
};