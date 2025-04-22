# SingleLinkedList
Singly linked version of std::list made for test and educational purposes.

# Features
Uses in-built `Node` struct for nodes with purpose-built iterators

## Supported fuctionality
- Three different constructors:
	- Default
	- Based on `std::initializer_list`
	- Accepting another `SingleLinkedList`
- Destructor which deletes all nodes
- `swap()` for swapping contents of two lists
- `PushFront()` for adding new node in the beginning
- `PopFront()` for deleting first node
- `InsertAfter()` for inserting new node after another node
- `EraseAfter()` for deleting node after another node
- `Clear()` for deleting all nodes
- `GetSize()` and `IsEmpty()` for checking size and emptiness of list
- Iterator support
- Private function `Transfer()` for transfering contents from one list to other

# Usage
- Min. C++ version: C++17
- Clone repository and use similarly to std::list. `main.cpp` containts examples of usage and tests
