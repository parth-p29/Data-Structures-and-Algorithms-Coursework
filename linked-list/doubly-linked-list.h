#ifndef SYDE223_A1_DOUBLY_LINKED_LIST_H
#define SYDE223_A1_DOUBLY_LINKED_LIST_H

class DoublyLinkedList {
public:
    // Can be seen outside as DoublyLinkedList::DataType
    typedef int DataType;

private:
    // Befriend so tests have access to variables.
	friend class DoublyLinkedListTest;
 
    // This type of list can basically grow as large as we want it to,
    // so we'll just pick an arbitrary large value as the capacity for
    // all lists of this type.
    static const unsigned int CAPACITY = 65536;

    // The node structure used for the DoublyLinkedList.
    struct Node {
        Node(DataType value);
        DataType value;
        Node* next;
        Node* prev;
    };

    // Private method to get the node at an index. This is optional, but you
    // will probably find it useful.
    Node* getNode(unsigned int index) const;

	// MEMBER VARIABLES
    // A pointer to the head node of the list.
    Node* head_;
    // A pointer to the tail node of the list.
    Node* tail_;
    // The number of elements in the list.
    unsigned int size_;

    // Copy constructor. Declared private so we don't misuse it.
    DoublyLinkedList(const DoublyLinkedList& rhs) {}
    // Assignment operator. Declared private so we don't misuse it.
    DoublyLinkedList& operator=(const DoublyLinkedList& rhs) {}

public:
	// CONSTRUCTOR/DESTRUCTOR
    // Create a new empty DoublyLinkedList.
    DoublyLinkedList();
    // Destroy this DoublyLinkedList, freeing all dynamically allocated memory.
    ~DoublyLinkedList();

	// ACCESSORS
    // Returns the number of elements in the list.
    unsigned int size() const;
    // Returns the maximum number of elements the list can hold.
    unsigned int capacity() const;
    // Returns true if the list is empty, false otherwise.
    bool empty() const;
    // Returns true if the list is at capacity, false otherwise.
    bool full() const;
    // Returns the value at the given index in the list. If index is invalid, 
    // return the value of the last element.
    DataType select(unsigned int index) const;
    // Searches for the given value, and returns the index of this value if found.
    // returns the size of the list otherwise.
    unsigned int search(DataType val) const;
    // Prints all elements in the list to the standard output.
    void print() const;

	// MUTATORS
    // NOTE: all mutators for this class are boolean functions, returning
    // true if the call succeeds, and false if it fails
    // Inserts a value into the list at a given index.
    bool insert(DataType val, unsigned int index);
    // Inserts a value at the beginning of the list.
    bool insert_front(DataType val);
    // Inserts a value at the end of the list.
    bool insert_back(DataType val);
    // Deletes a value from the list at the given index.
    bool remove(unsigned int index);
    // Deletes a value from the beginning of the list.
    bool remove_front();
    // Deletes a value at the end of the list.
    bool remove_back();
    // Replaces the value at the given index with the given value.
    bool replace(unsigned int index, DataType val);
};
#endif 
