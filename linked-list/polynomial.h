#ifndef SYDE223_A1_POLYNOMIAL_H
#define SYDE223_A1_POLYNOMIAL_H

#include "doubly-linked-list.h"
#include <iostream>

using namespace std;

class Polynomial {

private:
    int size_;
    DoublyLinkedList coefficients;

public:
    void print();
    Polynomial(int A[], int size);
    Polynomial* add(Polynomial* rhs);
    Polynomial* sub(Polynomial* rhs);
    Polynomial* mul(Polynomial* rhs);
};

#endif
