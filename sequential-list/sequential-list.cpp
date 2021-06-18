#include "sequential-list.h"
#include <iostream>

SequentialList::SequentialList(unsigned int cap)
{
    capacity_ = cap;
    size_ = 0;
    DataType *list = new DataType[capacity_]; //dynamically creates new array of type datatype (int) with the size of capacity
    data_ = list; //data_ will now point to the list in memory
}

SequentialList::~SequentialList()
{
    delete []data_; //deletes the array
    data_ = nullptr; //sets to null
}

unsigned int SequentialList::size() const
{
    return size_;
}

unsigned int SequentialList::capacity() const
{
    return capacity_;
}

bool SequentialList::empty() const
{
    if (size_ == 0){ //if size equals 0, list is empty
        return true;
    }
    else{
        return false;
    }
}

bool SequentialList::full() const
{
    if (size_ == capacity_){ //if size equals the cap, it is full
        return true;
    }
    else{
        return false;
    }
}

SequentialList::DataType SequentialList::select(unsigned int index) const
{
    if (index > size_ || index < 0){  //if index is larger than size or below 0 it will return last elem
        return data_[size_];
    }
    else{
        return data_[index];
    }
}

unsigned int SequentialList::search(DataType val) const
{
    for(int index = 0; index < size_; index++){
        if (data_[index] == val){
            return index;
        }
    }

    return size_;
}

void SequentialList::print() const
{

    for (int index = 0; index < size_; index++) {
        std::cout << data_[index] << std::endl;
    }
}

bool SequentialList::insert(DataType val, unsigned int index)
{
    if (index > size_ || full() || index < 0){

        return false;
    }

    else if (index == size_){

        data_[index] = val;
        size_++;
        return true;
    }

    else{

        //goes through loop from last index and iterates until idx is larger than index. it then changes the next current element to the previous
        for (int idx = size_; idx > index; idx--){

            data_[idx] = data_[idx - 1];  //shift all elements to the right
        }

        data_[index] = val;
        size_++;
        return true;
    }
}

bool SequentialList::insert_front(DataType val)
{
    bool status = insert(val, 0); //calls insert with 0 index param
    return status;
}

bool SequentialList::insert_back(DataType val)
{

    bool status = insert(val, size_); //calls insert with last elem index
    return status;
}

bool SequentialList::remove(unsigned int index)
{
    if (index >= size_ || index < 0){

        return false;
    }

    else{ //shifts all the elements to the left by making the current element equal to the next element
        for(int idx = index; idx <= size_; idx++){
            data_[idx] = data_[idx+1];
        }

        size_--;
        return true;
    }
}

bool SequentialList::remove_front()
{
    bool status = remove(0); //calls remove method with index 0
    return status;
}

bool SequentialList::remove_back()
{
    bool status = remove(size_-1); //calls remove method with index of last element
    return true;
}

bool SequentialList::replace(unsigned int index, DataType val)
{
    if (index > size_ || index < 0 ){

        return false;
    }
    else{

        data_[index] = val;   //re assigns new index to value
        return true;
    }

}

