#ifndef SYDE223_A3_BINARY_SEARCH_TREE_H
#define SYDE223_A3_BINARY_SEARCH_TREE_H

class BinarySearchTree {
public:
    // Can be seen externally as BinarySearchTree::DataType
    typedef int DataType;

    struct Node {
        // Sets the left and right children to NULL, and initializes val.
        Node(DataType newval);

        DataType val;  // Value of the node.
        Node* left;    // Pointer to the left node.
        Node* right;   // Pointer to the right node.
        int avlBalance;   // you may or may not use it for AVL trees (optional)
    };

private:
    friend class BinarySearchTreeTest;
    friend class AVLTreeTest;

    // Optional function that recursively gets the maximum depth for a given node.
    int getNodeDepth(Node* n) const;

    // Pointer to the root node of the tree.
    Node* root_;
    // Number of nodes in the tree.
    unsigned int size_;

    // Sets copy constructor and assignment operator to private.
    BinarySearchTree(const BinarySearchTree& other) {}
    BinarySearchTree& operator=(const BinarySearchTree& other) {}

public:
    // Default constructor to initialize the root.
    BinarySearchTree();
    // Destructor of the class BinarySearchTree. It deallocates the memory
    // space allocated for the binary search tree.
    ~BinarySearchTree();

    // Returns the number of nodes in the tree.
    unsigned int size() const;
    // Returns the maximum value of a node in the tree. You can assume that
    // this function will never be called on an empty tree.
    DataType max() const;
    // Returns the minimum value of a node in the tree. You can assume that
    // this function will never be called on an empty tree.
    DataType min() const;
    // Returns the maximum depth of the tree. A tree with only the root node has a
    // depth of 0. You can assume that this function will never be called on an
    // empty tree.
    unsigned int depth() const;
    // You can print the tree in whatever order you prefer. However, methods such
    // as in-order or level-order traversal could be the most useful for debugging.
    void print() const;
    // Returns true if a node with the value val exists in the tree; otherwise,
    // it returns false.
    bool exists(DataType val) const;
    // Returns a pointer to the root node
    Node* getRootNode();
    // Returns the root node pointer address
    Node** getRootNodeAddress();

    // Inserts the value val into the tree. Returns false if val already exists in
    // the tree, and true otherwise.
    bool insert(DataType val);
    // Removes the node with the value val from the tree. Returns true if successful,
    // and false otherwise.
    bool remove(DataType val);
    // Update the avlBalance starting at node n (optional)
    void updateNodeBalance(Node* n);
};

#endif //SYDE223_A3_BINARY_SEARCH_TREE_H
