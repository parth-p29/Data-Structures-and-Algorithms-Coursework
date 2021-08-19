#ifndef SYDE223_A3_AVL_TREE_H
#define SYDE223_A3_AVL_TREE_H
#include "binary-search-tree.h"

using namespace std;
class AVLTree: public BinarySearchTree
{
public:
    // Overriden insert and remove functions
    // Do not modify these definitions

    //The AVL tree should be kept balanced after calling just insert or remove.
    bool insert(DataType val);
    bool remove(DataType val);

    // Define additional functions and attributes below if you need
    void LeftRot(Node *parent);


    void RightRot(Node *parent);


    int NodeDepth(Node* n);


    bool ExistsDiffRoot(Node* root, DataType val);


    void balance(Node* temp);


    Node* FinderNode = nullptr;
};

#endif //SYDE223_A3_AVL_TREE_H
