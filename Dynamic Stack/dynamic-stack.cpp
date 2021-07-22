#include "dynamic-stack.h"
#include <iostream>
using namespace std;

const DynamicStack::StackItem DynamicStack::EMPTY_STACK = -9999;

DynamicStack::DynamicStack() {

    size_ = 0;
    init_capacity_ = 16;
    capacity_ = init_capacity_;
    items_ = new StackItem[capacity_];
}

DynamicStack::DynamicStack(unsigned int capacity){

    init_capacity_ = capacity;
    capacity_ = init_capacity_;
    size_ = 0;
    items_ = new StackItem[capacity_];
}

DynamicStack::~DynamicStack() {

    delete [] items_;
    items_ = nullptr;
}

bool DynamicStack::empty() const {

    if (size_ == 0){
        return true;
    }

    else{
        return false;
    }

}

int DynamicStack::size() const {

    return size_;

}

void DynamicStack::push(StackItem value) {


    if (size_ < capacity_){

        items_[size_] = value;

    }

    else{

        StackItem *DoubledStack =  new StackItem [capacity_ * 2]; //creates new doubled stack

        for (int i = 0; i < size_; i++){
            DoubledStack[i] = items_[i];    //copies elements from current stack into this one
        }

        DoubledStack[size_] = value; //pushes the new value into the doubled stack

        delete []items_; //deallocates the current item stack

        capacity_ *= 2; //cap is now doubled

        items_ = new StackItem[capacity_];  //creates new stack that is assigned to our main items with doubled cap

        for (int i = 0; i <= size_; i++){

            items_[i] = DoubledStack[i]; //assigns all values from the doubled stack to the items stack

        }

        delete []DoubledStack; //deallocates the temporary stack
        DoubledStack = nullptr;

    }

    size_++; //increments size by 1
}

DynamicStack::StackItem DynamicStack::pop() {

    if (empty()){
        return EMPTY_STACK;  //returns empty stack const if the stack is empty
    }

    else{

        StackItem *PoppedStack = new StackItem [capacity_];  //creates new stack with same cap as our orig stack
        StackItem PoppedItem = items_[size_-1]; //gets the last element from the stack (this item will be popped and returned)
        size_--; //decreases size by 1

        for (int i = 0; i < size_; i++){
            PoppedStack[i] = items_[i];  //pops last element out
        }

        if (size_ <= (capacity_ * 0.25) && !(capacity_ * 0.5 < init_capacity_ )){  //performs the specifications from the pop method requirements

            capacity_ *= 0.5;

            delete []items_;

            items_ = new StackItem [capacity_];

            for (int i = 0; i < size_; i++){

                items_[i] = PoppedStack[i];  //adds all elems from poppedstack to the orig items stack

            }

            delete []PoppedStack;
            PoppedStack = nullptr;  //de-allocates poppedstack

        }

        return PoppedItem; //returns the popped item
    }


}

DynamicStack::StackItem DynamicStack::peek() const {

    if (empty()){
        return EMPTY_STACK; //returns empty stack if stack is empty
    }
    else{
        return items_[size_-1]; //returns last elem
    }
}

void DynamicStack::print() const {

    for (int i = 0; i < size_; i++){

        cout << items_[i] << endl; //prints item from stack
    }

}
