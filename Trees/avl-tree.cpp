#include "avl-tree.h";
#include "algorithm";

bool AVLTree::insert(DataType val)
{
    bool Inserted = BinarySearchTree::insert(val);  //calls insert function from BST

    if (!Inserted){
        return false;  //returns false if insert doesn't go through
    }

    FinderNode = nullptr;  //sets our finder node to null

    balance(this->getRootNode());  //calls the avl balance with the orginal tree as input param

    if (!FinderNode){  //if the findernode is empty, it will jus end the call and return true
        return true;
    }

    else if (FinderNode->left && FinderNode->left->left && ExistsDiffRoot(FinderNode->left->left, val)){  //goes through the conditions to successfuly rotate tree
        this->RightRot(FinderNode);  //does right rotation if the correct orientation is present
    }

    else if (FinderNode->right && FinderNode->right->right && ExistsDiffRoot(FinderNode->right->right, val)){
        this->LeftRot(FinderNode); //does left rotation if the correct orientation is present
    }

    else if (FinderNode->left && FinderNode->left->right && ExistsDiffRoot(FinderNode->left->right, val)){
        this->LeftRot(FinderNode->left);  //first does left rotation and then right rotation to complete the left-right variant
        this->RightRot(FinderNode);
    }

    else if(FinderNode->right && FinderNode->right->left && ExistsDiffRoot(FinderNode->right->left, val)) {
        this->RightRot(FinderNode->right); //performs right-left rotation by using the previously made right and left rotations
        this->LeftRot(FinderNode);
    }

    return true;
}

bool AVLTree::ExistsDiffRoot(Node* root, DataType val) //checks if a value exisits in each subtree of a specific node
{
    if (root == nullptr){  //if tree is empty, returns false
        return false;
    }

    else if (root->val == val || ExistsDiffRoot(root->right, val) || ExistsDiffRoot(root->left, val)){  //checks the entire tree recursivley to see if node is there
        return true;
    }
}

void AVLTree::RightRot(Node *parent)  //performs right rotation on tree
{
    Node* temp = new Node(parent->val); //creates temp node

    temp->right = parent->right;  //steps for rotation:
    temp->left = parent->left->right;

    parent->val = parent->left->val;
    parent->right = temp;

    parent->left = parent->left->left;
}

void AVLTree::LeftRot(Node *parent)  //performs left rotation on tree
{
    Node* temp = new Node(parent->val); //creates temp node

    //steps for rotation:
    temp->right = parent->right->left;
    temp->left = parent->left;

    parent->left = temp;
    parent->val = parent->right->val;

    parent->right = parent->right->right;
}

bool AVLTree::remove(DataType val)  //similar to insert, this will remove a node and then balance tree
{
    bool removed = BinarySearchTree::remove(val);  //calls remove function from bst

    if (!removed){
        return false;  //returns  false if remove is not complete
    }

    FinderNode = nullptr; //sets finder to null

    balance(this->getRootNode());  //performs balnce on root node

    if(!FinderNode)  //returns true if finder ends up being null
    {
        return true;
    }

    else if(FinderNode->left && (NodeDepth(FinderNode->left->left) == (NodeDepth(FinderNode) - 2)))  //performs the correct rotation after remove is complete
    {
        this->RightRot(FinderNode); //does the right rotation after above conditions
    }

    else if (FinderNode->right && (NodeDepth(FinderNode->right->right) == (NodeDepth(FinderNode) - 2)))
    {
        this->LeftRot(FinderNode);  //does left rotation
    }


    else if(FinderNode->left && (NodeDepth(FinderNode->left->right) == (NodeDepth(FinderNode) - 2)))
    {
        this->LeftRot(FinderNode->left);  //first does left rotation and then right rotation to complete the left-right variant
        this->RightRot(FinderNode);
    }

    else
    {
        this->RightRot(FinderNode->right); //performs right-left rotation by using the previously made right and left rotations
        this->LeftRot(FinderNode);
    }

    return true;
}

int AVLTree::NodeDepth(Node* n)  //gets the depth of a node in the tree
{
    if (!n){
        return -1;  //if tree only has root, returns -1
    }
    else{
        return std::max(NodeDepth(n->right), NodeDepth(n->left)) + 1;
    }
}

void AVLTree::balance(Node *temp)  //finds balance for inputted node
{
    if(!temp){
        return; //if null exits function call
    }

    if(temp->avlBalance < -1 || temp->avlBalance > 1)  //conditions for balance
    {
        FinderNode = temp;
    }

    balance(temp->left);  //performs balance for all node subtrees
    balance(temp->right);
}
