#include "polynomial.h"
#include <iostream>
#include <stack>

using namespace std;
Polynomial::Polynomial(int A[], int size) {

    size_ = size; //sets the size of the list to the size inputted

    for (int i = 0; i < size_; i++){
        coefficients.insert_back(A[i]); //inserts elements into the linked list
    }
}

Polynomial* Polynomial::add(Polynomial* rhs) {

    int max_size;
    int min_size;  //sets a max and min size variables to hold the sizes of the largest and smallest list

    if (rhs->size_ > size_){  //sets which list is bigger and which is smaller
        max_size = rhs->size_;
        min_size = size_;
    }
    else if (rhs->size_ < size_){
        max_size = size_;
        min_size = rhs->size_;
    }
    else{
        min_size = size_;
        max_size = size_;
    }

    int newArr[max_size]; //creates new array with the size of the maximum inputted list

    for (int i=0; i < min_size; i++){  //loops through the smaller inputed list
        newArr[i] = rhs->coefficients.select(i) + coefficients.select((i));  //sets each element in the new array to the added elements of the 2 inputted arrays
    }

    if (rhs->size_ == max_size){ //based on which list is larger, it will add in the additional elements that did not get affected by the add operation
        for (int i = min_size; i < max_size; i++){
            newArr[i] = rhs->coefficients.select(i);
        }
    }

    else if (size_ == max_size){
        for (int i = min_size; i < max_size; i++){
            newArr[i] = coefficients.select(i);
        }
    }

    Polynomial *newPoly = new Polynomial(newArr, max_size);  //creates new polynomial with the new array and its size

    return newPoly; //new polynomial gets returned
}

Polynomial* Polynomial::sub(Polynomial* rhs) { //this methods works by turning subtraction into addition -> (1) - (1) is the same thing as (1) + (-1)


    int newRhs[rhs->size_]; //initilize a new array that will hold the inverted values of the original rhs array

    for(int i = 0; i < rhs->size_; i++){

        newRhs[i] = rhs->coefficients.select(i) * -1;  //multiples each of rhs's coefficents with -1 to get the inverted value and stores that in the newRhs array
    }

    Polynomial *newPolyRhs = new Polynomial(newRhs, rhs->size_); //creates a new rhs polynomial

    Polynomial *newPoly = add(newPolyRhs); //adds the new rhs polynomial with this polynomial

    return newPoly; //returns the new polynomial
}

Polynomial* Polynomial::mul(Polynomial* rhs) {

    int max_size = (size_ + rhs->size_)-1; //when multipling two polynomials, the size will be the sum of the sizes of the 2 polynomials and then subtracting 1

    int newArr[max_size]; //new array created with the size

    for (int i = 0; i < max_size; i++){
        newArr[i] = 0;  //all the elemtns in said array will be initially set to 0
    }

    for (int i = 0; i < size_; i++){  //loops through this polynomail list

        for(int g = 0; g < rhs->size_; g++){  //loops through the rhs polynomial list
            newArr[i + g] += coefficients.select(i) * rhs->coefficients.select(g); //multiplies the elements of the two together
        }
    }

    Polynomial *newPoly = new Polynomial(newArr, max_size); //creates a new polynomial

    return newPoly;

}

void Polynomial::print(){

    int degree = size_ - 1; //variable will represent the degree of each term in the polynomial
    int numOfNonZeros = 0; //variable will be used to represent all the non-zero coefficents in the list

    for (int i = 0; i < size_; i++){
        if (coefficients.select(i) != 0){
            numOfNonZeros++;  //counts the number of non-zero terms
        }
    }

    int numOfAdditionSigns = numOfNonZeros - 1;  //variables holds the number of "+" signs which will be outputted

    for (int i = size_-1; i >= 0; i--){  //loops through the list

        if (coefficients.select(i) > 0){
            cout << coefficients.select(i) << "x^" << degree; //if the coefficent is greater than 0, it will output it with the corresponding configuration (e.g 2x^2)

            degree--;
        }
        else if (coefficients.select(i) < 0){
            cout << "(" << coefficients.select(i) << ")" << "x^" << degree; //prints coefficent out with the corresponding config if it is less than 0 (e.g. (-2)x^2)
            degree--;
        }
        else{
            degree--; //if coefficent is 0, subtract degree by 1
        }

        if (i != 0 && coefficients.select(i) != 0 && numOfAdditionSigns > 0){ //if the current index isn't the last index in the list and the current coefficent isnt 0 and the number of signs is greater than 0:
            cout << " + ";  //it will print a plus sign
            numOfAdditionSigns--;  //decrese the number of signs by 1
        }

        if (degree < 0){ //once degree is less than 0, it will end the line and break out of loop
            cout << endl;
            break;
        }
    }
}
