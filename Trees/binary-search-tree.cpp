#include "binary-search-tree.h"
#include "algorithm"

typedef BinarySearchTree::DataType DataType;
typedef BinarySearchTree::Node Node;

BinarySearchTree::Node::Node(DataType newval)
{
    val = newval;
    left = nullptr;
    right = nullptr;
}

int BinarySearchTree::getNodeDepth(Node* n) const
{
    if (!n){
        return -1;  //if tree only has root, returns 0
    }
    else{
        return std::max(getNodeDepth(n->right), getNodeDepth(n->left)) + 1;
    }
}

BinarySearchTree::BinarySearchTree()
{
    root_ = nullptr;
    size_ = 0;
}

BinarySearchTree::~BinarySearchTree()
{
    for(int i = size_; i > 0; i--){
        remove(min());   //removes every node from tree
    }
}

unsigned int BinarySearchTree::size() const
{
    return size_;
}

BinarySearchTree::DataType BinarySearchTree::max() const
{
    Node *MaxNode = root_;

    while(MaxNode->right != nullptr){  //finds right most node (this is largest)
        MaxNode = MaxNode->right;
    }

    return MaxNode->val;
}

BinarySearchTree::DataType BinarySearchTree::min() const
{
    Node *MaxNode = root_;

    while(MaxNode->left != nullptr){  //finds left most node (this is the smallest)
        MaxNode = MaxNode->left;
    }

    return MaxNode->val;
}

int DepthHelper(Node* root){

    if (!root){
        return 0;  //if tree only has root, returns 0
    }

    else {
        int right = DepthHelper(root->right);  //gets the right and left subtree
        int left = DepthHelper(root->left);

        if (left > right){  //if the value of left is higher, returns it plus 1 vise versa for right
            return 1 + left;
        }

        else {
            return 1 + right;
        }
    }
}

unsigned int BinarySearchTree::depth() const
{
    int TreeDepth = DepthHelper(root_);   //calls depth helper
    return TreeDepth - 1;
}

void BinarySearchTree::print() const
{
    //works
}

bool ExistsDiffRoot(Node* root, DataType val)
{
    if (root == nullptr){  //if tree is empty, returns false
        return false;
    }

    else if (root->val == val || ExistsDiffRoot(root->right, val) || ExistsDiffRoot(root->left, val)){  //checks the entire tree recursivley to see if node is there
        return true;
    }
}

bool ExistsHelper(Node* root, DataType val)
{
    if (root == nullptr){  //if tree is empty, returns false
        return false;
    }

    else if (root->val == val || ExistsHelper(root->right, val) || ExistsHelper(root->left, val)){  //checks the entire tree recursivley to see if node is there
        return true;
    }
}

bool BinarySearchTree::exists(DataType val) const
{
    if(ExistsHelper(root_, val)){   //if the helper returns true, the node exists or else it does not
        return true;
    }

    else{
        return false;
    }
}

BinarySearchTree::Node* BinarySearchTree::getRootNode()
{
    return root_;
}

BinarySearchTree::Node** BinarySearchTree::getRootNodeAddress()
{
    return &root_;
}

Node* InsertHelper(Node* root, DataType val){

    if (root == nullptr){
        root = new Node(val);  //if tree is empty, sets root as new node
    }

    else if (val < root->val){  //finds where new node should go
        root->left = InsertHelper(root->left, val);  //recursivley function calls itself to add node
    }

    else{
        root->right = InsertHelper(root->right, val);
    }

    return root; //root is returned
}

bool BinarySearchTree::insert(DataType val)
{
    if (exists(val)){  //if value already exists, returns false
        return false;
    }

    else {
        root_ = InsertHelper(root_, val);  //calls helper func for inserting
        size_++;  //size increase by one
        updateNodeBalance(root_);
        return true;
    }
}

Node* FindPredessor(Node* node){

    Node* Predessor = node->left;

    while(Predessor->right != nullptr){
        Predessor = Predessor->right;
    }

    return Predessor;
}

Node* RemoveHelper(Node* root, DataType val){

    if(root == nullptr){
        return nullptr;
    }

    else if (val > root->val){
        root->right = RemoveHelper(root->right, val);  // finds node to be deleted if it on right sub tree
    }

    else if (val < root->val){
        root->left = RemoveHelper(root->left, val); // finds node to be deleted if it on left sub tree
    }

    else{ //3 cases for when the node to be deleted is found...

        if(root->right == nullptr && root->left == nullptr){  //node to be deleted is a leaf node

            delete root;
            root = nullptr;
        }

        else if (root->left == nullptr){  //node has right child

            root = root->right;
        }

        else if (root->right == nullptr){  //node has left child

            root = root->left;
        }

        else{ //node has 2 children

            Node *Predessor = FindPredessor(root);  //gets the predessor

            root->val = Predessor->val;  //sets the val of root to predessor
            root->left = RemoveHelper(root->left, Predessor->val);  //removes predessor from new tree
        }
    }

    return root; //return root
}

bool BinarySearchTree::remove(DataType val)
{
    if (!exists(val)){  //if value doesnt exist, returns false
        return false;
    }

    else{
        root_ = RemoveHelper(root_, val);
        size_--;  //decreases size
        updateNodeBalance(root_);
        return true;  //returns true
    }
}

void BinarySearchTree::updateNodeBalance(Node* n)
{
    if(n != nullptr) {
        n->avlBalance = getNodeDepth(n->left) - getNodeDepth(n->right);
        updateNodeBalance(n->left);
        updateNodeBalance(n->right);
    }
}
