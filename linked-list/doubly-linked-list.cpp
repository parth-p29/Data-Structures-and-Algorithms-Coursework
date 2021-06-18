#include "doubly-linked-list.h"
#include <iostream>
using namespace std;
DoublyLinkedList::Node::Node(DataType data)
{
    value = data;
    prev = NULL;
    next = NULL;
}

DoublyLinkedList::DoublyLinkedList()
{
    size_ = 0;
    head_ = NULL;
    tail_ = NULL;
}

DoublyLinkedList::~DoublyLinkedList()
{
    while (head_ != NULL){  //loops as head is not null
        Node *temp = head_;
        head_ = head_ -> next;
        delete temp;
    }
}

unsigned int DoublyLinkedList::size() const
{
    return size_;
}

unsigned int DoublyLinkedList::capacity() const
{
    return CAPACITY;
}

bool DoublyLinkedList::empty() const
{
    if (size_ == 0){
        return true;
    }
    else {
        return false;
    }
}

bool DoublyLinkedList::full() const
{
    if (size_ == CAPACITY){
        return true;
    }
    else{
        return false;
    }
}

DoublyLinkedList::DataType DoublyLinkedList::select(unsigned int index) const
{
    if (index < 0 || index >= size_){

        return tail_->value;
    }

    else{

        Node *elem = getNode(index); //gets the node of this index
        return elem -> value; //returns its value
    }
}

unsigned int DoublyLinkedList::search(DataType value) const
{

    for(int i = 0; i < size_; i++){

        Node *CurrNode = getNode(i);  //gets the node of each index

        if (CurrNode -> value == value){   //if the value of the node equals to the inputted value, it returns the value
            return i;
        }
    }

    return size_;

}

void DoublyLinkedList::print() const
{
    if (empty()){
        cout << "Sorry, no values in this list.";
    }

    else{

        for(int i = 0; i < size_; i++){

            Node *CurrNode = getNode(i);

            cout << CurrNode -> value << endl;
        }

    }
}

DoublyLinkedList::Node* DoublyLinkedList::getNode(unsigned int index) const
{
    Node *tempnode = head_;  //creates a temp node that points to head

    int i = 0;

    while (i < index){  //loops until the iterator is equal to index
        tempnode = tempnode -> next;  //sets the temp to the next next node
        i++;
    }

    return tempnode;  //returns the node
}

bool DoublyLinkedList::insert(DataType value, unsigned int index)
{
    if (index < 0 || index > size_ || full()){
        return false;
    }

    else if (index == 0){  //insert node at head, calls the insert_front method
        return insert_front(value);
    }

    else if (index == size_){  //insert node at tail, calls insert_back method
        return insert_back(value);
    }

    else{

        Node *NewNode = new Node(value);  //creates a new node

        Node *PrevNode = getNode(index - 1);  //gets the previous node in the list
        Node *AfterNode = PrevNode->next; //gets the next node in the list

        if (AfterNode != NULL){
            AfterNode -> prev = NewNode;  //if the next node isnt null, it sets the prev node to the new node
        }

        PrevNode -> next = NewNode; //sets the next node for the prev node to the new node

        NewNode -> prev = PrevNode;
        NewNode -> next = AfterNode;  //sets the before and after node for the new node

        size_++; //increase list size
        return true;
    }
}

bool DoublyLinkedList::insert_front(DataType value)
{
    Node *NewNode = new Node(value);

    if (size_ == 0){

        head_ = NewNode; //if list is empty, sets both tail and head to null
        tail_ = NewNode;

    }

    else{

        NewNode -> next = head_;  //sets the next node after the new one to head
        head_ -> prev = NewNode; //sets the prev node of head's to the new node
        head_ = NewNode; //sets head to new node

    }

    size_++;
    return true;
}

bool DoublyLinkedList::insert_back(DataType value)
{
    Node *NewNode = new Node(value);

    if (size_ == 0) {

        head_ = NewNode;
        tail_ = NewNode;  //sets head and tail to null if list is empty
    }

    else{
        NewNode -> prev = tail_;  //sets the node before the new node to tail
        tail_ -> next = NewNode; //sets the node after the tail to the new node
        tail_ = NewNode; //makes tail point to new node
    }

    size_++;
    return true;
}

bool DoublyLinkedList::remove(unsigned int index)
{
    if (index < 0 || empty() || index >= size_) {  //added a slight change - if the index is greater than or equal to the size that is not an acceptable index -> returns false
        return false;
    }

    else if (index == 0){  //if want to remove first index, calls remove_front method
        return remove_front();
    }

    else if (index == size_-1){
        return remove_back();  //if want to remove last element, calls remove back method
    }

    else{

        Node *PrevNode = getNode(index-1);  //gets the previous node to that of the index
        Node *AfterNode = PrevNode->next; //gets the node that is after the previous node

        PrevNode->next = AfterNode->next; //sets the node after the previous to the after nodes after
        AfterNode->next->prev = PrevNode; //sets the node after the after node's previous value to the previous node

        delete AfterNode;
        AfterNode = NULL;  //deallocates the after node and set to null

        size_--; //decreses size of list by 1

        return true; //another small change (added a return true statement here)
    }
}

bool DoublyLinkedList::remove_front()
{
    if (empty()){
        return false;
    }
    else{

        Node *temp = head_;  //sets a temp pointer to the head node
        head_ = temp->next; //sets the head node to equal to the next value of the temp pointer

        if (size_ - 1 == 0){
            tail_ = NULL; //if the list only has one element before deleting, it will set the tail to null
        }

        delete temp;  //deallocates temp and sets it to null
        temp = NULL;

        size_--;

        return true;
    }
}

bool DoublyLinkedList::remove_back()   //same process as remove front
{
    if (size_ == 0){
        return false;
    }
    else{
        Node *temp = tail_;
        tail_ = temp -> prev;

        temp -> next = NULL;   // (New addition) sets the next value of the new tail to NULL

        if (tail_) //if tail is not null, it will set its next value to NULL
        {
            tail_->next = NULL;
        }else{
            head_ = NULL; //if tail is null, then head should be null too
        }

        delete temp;
        temp = NULL;
        size_--;

        return true;
    }
}

bool DoublyLinkedList::replace(unsigned int index, DataType value)
{
    if (index > size_ || index < 0 ){

        return false;
    }

    else {

        Node *NewNode = new Node(value);  //creates the new node
        Node *CurrNode = getNode(index);  //gets the node at the current index

        if (CurrNode == head_){  //if the node the user wants to replace is a head node, it will do the following:
            CurrNode -> next -> prev = NewNode;  //set the next value's previous node to the new node
            NewNode -> prev = NULL;  //sets the new nodes previous node to null (head nodes previous node is going to be null)
            NewNode -> next = CurrNode -> next; //sets the node after the new node to the current nodes next value
            head_ = NewNode; //sets the head to the new node
        }

        else if (CurrNode == tail_){
            CurrNode -> prev -> next = NewNode;   //does the same process but for the tail node
            NewNode -> next = NULL;
            NewNode -> prev = CurrNode -> prev;
            tail_ = NewNode;
        }

        else{
            CurrNode -> prev -> next = NewNode;  //if node is not a head or tail node. I will do the following:
            CurrNode -> next -> prev = NewNode;

            NewNode -> next = CurrNode -> next;
            NewNode -> prev = CurrNode -> prev;
        }

        delete CurrNode;
        CurrNode = NULL;  //deallocate and set pointer to null

        return true;
    }
}
