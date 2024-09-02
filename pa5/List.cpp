/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA5
* List.cpp
* List for List ADT
****************************************/

#include "List.h"


// Node constructor
List::Node::Node(ListElement x) { 

	data = x;
	next = nullptr;
	prev = nullptr;

}


// List() creates new List in the empty state
List::List() { 

	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy -> next = backDummy;
	backDummy -> prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;

}

List::List(const List& L) { 

	frontDummy = new Node(0);
	backDummy = new Node(0);
	frontDummy -> next = backDummy;
	backDummy -> prev = frontDummy;
	beforeCursor = frontDummy;
	afterCursor = backDummy;
	pos_cursor = 0;
	num_elements = 0;
	
	Node *N = L.frontDummy -> next;
	
	while (N != L.backDummy) { 
	
		this -> insertBefore(N -> data);
		N = N -> next;
	
	}

}


// Destructor
List::~List() { 

	this -> clear();
	delete frontDummy;
	delete backDummy;

}


// Access functions
// Returns the length of this List
int List::length() const { 

	return num_elements;

}


// Returns the front element in this List.
// pre: length()>0
ListElement List::front() const { 

	if (length() <= 0) { 
	
		throw std::length_error("List: front(): empty list");
	
	}
	
	return frontDummy -> next -> data;

}


// Returns the back element in this List.
// pre: length() > 0
ListElement List::back() const { 

	if (length() <= 0) { 
	
		throw std::length_error("List: back(): empty list");
	
	}
	
	return backDummy -> prev -> data;

}


// Returns the position of cursor in this List: 0 <= position() <= length()
int List::position() const { 

	return pos_cursor;

}


// Returns the element after the cursor.
// pre: position()<length()
ListElement List::peekNext() const { 
	
	if (position() >= length()) { 
	
		throw std::range_error("List: peekNext(): cursor at back");
	
	}
	
	return afterCursor -> data;

}


// Returns the element before the cursor.
// pre: position() > 0
ListElement List::peekPrev() const { 

	if (position() <= 0) { 
	
		throw std::range_error("List: peekPrev(): cursor at front");
	
	}
	
	return beforeCursor -> data;

}


// Manipulation procedures
// Delete all elements in this List, setting it to the empty
void List::clear() { 

	moveFront();
	
	while (length() > 0) { 
	
		eraseAfter();
	
	}

}


// Moves cursor to positon 0 in this List
void List::moveFront() { 

	beforeCursor = frontDummy;
	afterCursor = frontDummy -> next;
	pos_cursor = 0;

}


// Moves cursor to positon length() in this List
void List::moveBack() { 

	beforeCursor = backDummy -> prev;
	afterCursor = backDummy;
	pos_cursor = length();

}


// Advances cursor to next higher position. Returns the List elements that was passed over
// pre: positon() < length()
ListElement List::moveNext() { 

	if (position() == length()) { 
	
		throw std::range_error("List: moveNext(): cursor at back");
	
	}
	
	if (position() > length()) { 
	
		throw std::range_error("List: moveNext(): cursor at front");
	
	}
	
	beforeCursor = afterCursor;
	afterCursor = afterCursor -> next;
	pos_cursor++;
	return beforeCursor -> data;

}


// Advances cursor to next lower position. Returns the List element that was passed over
// pre: positon() > 0
ListElement List::movePrev() { 

	if (position() == 0) { 
	
		throw std::range_error("List: movePrev(): cursor at front");
	
	}
	
	if (position() < 0) { 
	
		throw std::range_error("List: movePrev(): cursor at back");
	
	}
	
	afterCursor = beforeCursor;
	beforeCursor = beforeCursor -> prev;
	pos_cursor--;
	return afterCursor -> data;

}


void List::insertAfter(ListElement x) { 

	Node *temp = new Node(x);
	temp -> prev = beforeCursor;
	temp -> next = afterCursor;
	beforeCursor -> next = temp;
	afterCursor -> prev = temp;
	
	afterCursor = temp;
	num_elements++;

}


void List::insertBefore(ListElement x) { 

	Node *temp = new Node(x);
	temp -> prev = beforeCursor;
	temp -> next = afterCursor;
	beforeCursor -> next = temp;
	afterCursor -> prev = temp;
	
	beforeCursor = temp;
	pos_cursor++;
	num_elements++;

}


void List::setAfter(ListElement x) { 

	if (position() == length()) { 
	
		throw std::range_error("List: setAfter(): cursor at back");
	
	}
	
	if (position() > length()) { 
	
		throw std::range_error("List: setAfter(): cursor at front");
	
	}
	
	afterCursor -> data = x;

}


void List::setBefore(ListElement x) { 

	if (position() == 0) { 
	
		throw std::range_error("List: setBefore(): cursor at front");
	
	}
	
	if (position() < 0) { 
	
		throw std::range_error("List: setBefore(): cursor at back");
	
	}
	
	beforeCursor -> data = x;

}


// Deletes element after cursor
// pre: position() < length()
void List::eraseAfter() { 

	if (position() == length()) { 
	
		throw std::range_error("List: eraseAfter(): cursor at back");
	
	}
	
	if (position() > length()) { 
	
		throw std::range_error("List: eraseAfter(): cursor at front");
	
	}
	
	Node *N = afterCursor;
	beforeCursor -> next = N -> next;
	afterCursor -> next -> prev = beforeCursor;
	afterCursor = N -> next;
	delete N;
	num_elements--;

}


// Deletes element before cursor
// pre: position() > 0
void List::eraseBefore() { 

	if (position() == 0) { 
	
		throw std::range_error("List: eraseBefore(): cursor at front");
	
	}
	
	if (position() < 0) { 
	
		throw std::range_error("List: eraseBefore(): cursor at back");
	
	}
	
	Node *N = beforeCursor;
	afterCursor -> prev = N -> prev;
	afterCursor -> prev -> next = afterCursor;
	beforeCursor = N -> prev;
	delete N;
	num_elements--;
	pos_cursor--;

}


// Other Functions 
// Starting from the current cursor position, performs a linear search (in da
// the direction front-to-back) for the first occurrence of element x. If x
// is found, places the cursor immediately after the found element, then 
// returns the final cursor position. If x is not found, places the cursor 
// at position length(), and returns -1. 
int List::findNext(ListElement x) { 

	while (position() < length()) { 
	
		if (peekNext() == x) { 
		
			moveNext();
			return position();
		
		}
		
		moveNext();
	
	}
	
	return -1;

}


// Starting from the current cursor position, performs a linear search (in 
// the direction back-to-front) for the first occurrence of element x. If x
// is found, places the cursor immediately before the found element, then
// returns the final cursor position. If x is not found, places the cursor 
// at position 0, and returns -1. 
int List::findPrev(ListElement x) { 

	while (position() > 0) { 
	
		if (peekPrev() == x) { 
		
			movePrev();
			return position();
		
		}
		
		movePrev();
	
	}
	
	return -1;

}


// Removes any repeated elements in this List, leaving only unique elements.
// The order of the remaining elements is obtained by retaining the frontmost 
// occurrance of each element, and removing all other occurances. The cursor 
// is not moved with respect to the retained elements, i.e. it lies between 
// the same two retained elements that it did before cleanup() was called.
void List::cleanup() { 

	int current_pos = 0;
	Node *current_node = frontDummy -> next;
	
	while (current_node != backDummy) { 
	
		int compare_pos = current_pos + 1;
		Node *compare_node = current_node -> next;
		
		while (compare_node != backDummy) { 
		
			Node *prev_node = compare_node -> prev;
			
			if (compare_node -> data == current_node -> data) { 
			
				if (compare_node == beforeCursor) { 
				
					eraseBefore();
					compare_node = prev_node;
				
				} else if (compare_node == afterCursor) { 
				
					eraseAfter();
					compare_node = prev_node;
				
				} else { 
				
					Node *temp = compare_node;
					compare_node = compare_node -> prev;
					temp -> prev -> next = temp -> next;
					temp -> next -> prev = temp -> prev;
					delete temp;
					num_elements--;
					
					if (compare_pos <= position()) { 
					
						pos_cursor--;
					
					}
				
				}
			
			}
			
			compare_node = compare_node -> next;
			compare_pos++;
		
		}
		
		current_node = current_node -> next;
		current_pos++;
	
	}

}


List List::concat(const List& L) const { 

	List M = List();
	
	for (Node *n1 = frontDummy -> next; n1 != backDummy; n1 = n1 -> next) { 
	
		M.insertBefore(n1 -> data);
	
	}
	
	for (Node *n2 = L.frontDummy -> next; n2 != L.backDummy; n2 = n2 -> next) { 
	
		M.insertBefore(n2 -> data);
	
	}
	
	M.moveFront();
	return M;

}


std::string List::to_string() const { 

	std::string s = "(";
	
	for (Node *N = frontDummy -> next; N != backDummy; N = N -> next) { 
	
		s += std::to_string(N -> data) + (N != backDummy -> prev ? ", " : ")");
	
	}
	
	return s;

}


bool List::equals(const List& R) const { 

	if (length() != R.length()) { 
	
		return false;
		
	}
	
	for (Node *N = frontDummy -> next, *M = R.frontDummy -> next; N != backDummy; N = N -> next, M = M -> next) { 
	
		if (N -> data != M -> data) { 
		
			return false;
		
		}
	
	}
	
	return true;

}


// Overriden Operators 
// operator<<()
// Inserts string representation of L into stream.
std::ostream& operator<<( std::ostream& stream, const List& L ) { 

	return stream << L.List::to_string();

}


bool operator==( const List& A, const List& B ) { 

	return A.List::equals(B);

}


List& List::operator=(const List& L) { 

	if (this != &L) { 
	
		List temp = L;
		std::swap(frontDummy, temp.frontDummy);
		std::swap(backDummy, temp.backDummy);
		std::swap(beforeCursor, temp.beforeCursor);
		std::swap(afterCursor, temp.afterCursor);
		std::swap(pos_cursor, temp.pos_cursor);
		std::swap(num_elements, temp.num_elements);
	
	}
	
	return *this;

}



