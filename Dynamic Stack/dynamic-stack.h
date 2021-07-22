#ifndef SYDE223_A2_DYNAMIC_STACK_H
#define SYDE223_A2_DYNAMIC_STACK_H

class DynamicStack {
public:
    // Defines the kind of data that the stack will contain
    typedef int StackItem;
    // Defines a constant that will be used to indicate an empty stack
    static const StackItem EMPTY_STACK;

private:
    // Befriend so tests have access to variables.
    friend class DynamicStackTest;

    // MEMBER VARIABLES
    // An array of stack items.
    StackItem* items_;
    // Maximum number of elements allowed in the stack.
    int capacity_;
    // Current number of elements in the stack.
    int size_;
    // Initial capacity of the array (i.e., the capacity set in the constructor).
    // This is used by pop() to determine if we should decrease the capacity.
    int init_capacity_;

    // Copy constructor. Declared private so we don't use it incorrectly.
    DynamicStack(const DynamicStack& other) {}

    // Assignment operator. Declared private so we don't use it incorrectly.
    DynamicStack operator=(const DynamicStack& other) {}


public:
    // CONSTRUCTORS/DESTRUCTOR
    // Default constructor of the class DynamicStack. It uses 16 as the initial
    // capacity of the array, and allocates the required memory space for the
    // stack. The function appropriately initializes the fields of the created
    // empty stack.
    DynamicStack();

    // Parametric constructor of the class DynamicStack. It allocates the required
    // memory space for the stack of the given capacity. The function
    // appropriately initializes the fields of the created empty stack.
    DynamicStack(unsigned int capacity);

    // Destructor of the class DynamicStack. It deallocates the memory space
    // allocated for the stack.
    ~DynamicStack();

    // ACCESSORS
    // Returns the number of items in the stack.
    int size() const;

    // Returns true if the stack is empty and false otherwise.
    bool empty() const;

    // Prints the stack items sequentially and in order, from the top to the
    // bottom of the stack.
    void print() const;

    // Returns the value at the top of the stack without removing it. If the
    // stack is empty, it returns the EMPTY_STACK constant instead.
    StackItem peek() const;

    // MUTATORS
    // Takes as an argument a StackItem value. If the stack is not full, the value
    // is pushed onto the stack. Otherwise, the capacity of the stack is doubled,
    // and the item is then pushed onto the resized stack.
    void push(StackItem value);

    // Removes and returns the top item from the stack as long as the stack is
    // not empty. If the number of items remaining in the stack after popping
    // is less than or equal to one quarter of the capacity of the array, then
    // the array is halved. However, if the new halved capacity is less than
    // the initial capacity, then no resizing takes place. Finally, If the stack
    // is empty before the pop, the EMPTY STACK constant is returned.
    StackItem pop();
};

#endif //SYDE223_A2_DYNAMIC_STACK_H
