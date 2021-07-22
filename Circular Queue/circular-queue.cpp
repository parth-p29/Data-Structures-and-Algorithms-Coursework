#include "circular-queue.h"
#include <iostream>
using namespace std;


typedef CircularQueue::QueueItem QueueItem;
const QueueItem CircularQueue::EMPTY_QUEUE = -999;  //empty queue value

CircularQueue::CircularQueue() {

    size_ = 0;
    capacity_ = 16;
    items_ = new QueueItem[capacity_];   //construcuter initilizes all the values for the queue with default cap
    tail_ = 0;
    head_ = 0;
}

CircularQueue::CircularQueue(unsigned int capacity) {

    size_ = 0;
    capacity_ = capacity;  //takes user inputted cap for the queue
    items_ = new QueueItem[capacity_];
    tail_ = 0;
    head_ = 0;
}

CircularQueue::~CircularQueue() {

    delete []items_;  //destructor
    items_ = nullptr;

}

bool CircularQueue::empty() const {

    if (size_ == 0){  //returns true if size is 0
        return true;
    }

    return false;
}

bool CircularQueue::full() const {

    if (capacity_ == size_ && tail_ == head_){  //if the size of queue equals the cap and both head and tail equal each other, it is full
        return true;
    }

    return false;
}

int CircularQueue::size() const {
    return size_;  //returns size variable
}

bool CircularQueue::enqueue(QueueItem value) {

    if (full()){
        return false;  //if the queue is full, it will return false
    }

    else{
        items_[tail_] = value;  //adds user inputted value to the end of the items_ array (to where the tail is)

        tail_++; //tail increases by one because it points to the value after the last item in the queue

        if (tail_ >=  capacity_){ //if the tail is or exceeds the cap it will be reinitilized to 0
            tail_ = 0;
        }

        size_++;  //increases size
        return true;
    }
}

CircularQueue::QueueItem CircularQueue::dequeue() {

    if (empty()){
        return EMPTY_QUEUE; //returns the empty const if the queue is empty
    }

    else{
        QueueItem DequeuedItem = this->peek();  //gets the item which will be dequeued

        head_++; //increases head by 1 to point to the new head

        if (head_ >= capacity_){
            head_ = 0;  //if head exceeds cap, it will be reset to 0
        }

        size_--; //decreases size by 1
        return DequeuedItem; //returns the dequeued item
    }

}

CircularQueue::QueueItem CircularQueue::peek() const {

    if (empty()){
        return EMPTY_QUEUE;  //returns empty stack if empty
    }

    return items_[head_]; //if not empty, it will return the item where the head is pointing
}

void CircularQueue::print() const {  //prints all elements in queue

    if (!empty()) {

        if (head_ < tail_) {  //if tail is larger than head, it will print all elements starting from head to tail

            for (int i = head_; i < tail_; i++) {
                cout << items_[i] << " ";
            }

            cout << endl;

        } else {

            for (int i = head_; i < capacity_ ; i++) {  //it will print all elements from head to end of list
                cout << items_[i] << " ";
            }

            for (int i = 0; i < tail_; i++) {
                cout << items_[i] << " "; //and then print the elements from 0 to tail (because it is circle)
            }

            cout << endl;
        }
    }

}
