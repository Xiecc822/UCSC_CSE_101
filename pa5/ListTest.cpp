/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA5
* ListTest.cpp
* List Test Client for List ADT
****************************************/

#include <string>
#include <iostream>
#include <stdexcept>

#include "List.h"

using namespace std;


int main() { 

	// Create a new List
	List myList;
	
	// Test the length function, return 0
	cout << "Length of myList: " << myList.length() << endl;
	
	// Test the insertAfter function
	myList.insertAfter(1);
	myList.insertAfter(2);
	myList.insertAfter(3);
	
	// Test the front and back function
	cout << "Front element: " << myList.front() << endl;
	cout << "Back element: " << myList.back() << endl;
	
	// Test the moveFront function
	myList.moveFront();
	cout << "Current element: " << myList.peekNext() << endl;
	
	// Test the moveNext function
	cout << "Next element: " << myList.moveNext() << endl;
	
	// Test the moveBack function
	myList.moveBack();
	cout << "Current element: " << myList.peekPrev() << endl;
	
	// Test the movePrev function
	cout << "Previous element: " << myList.movePrev() << endl;
	
	// Test the insertBefore function
	myList.insertBefore(0);
	
	// Test the setAfter and setBefore functions
	myList.setAfter(5);
	myList.setBefore(4);
	
	// Test the findNext and findPrev functions
	cout << "Index of 5: " << myList.findNext(5) << endl;
	cout << "Index of 4: " << myList.findPrev(4) << endl;
	
	// Test the eraseAfter and eraseBefore functions
	myList.eraseAfter();
	myList.eraseBefore();
	
	// Test the to_string function
	cout << "List: " << myList.to_string() << endl;
	
	// Test the equals function with an identical list
	List identicalList;
	identicalList.insertAfter(1);
	identicalList.insertAfter(2);
	identicalList.insertAfter(3);
	cout << "Lists equal? " << myList.equals(identicalList) << endl;
	
	// Test the equals function with a different list
	List differentList;
	differentList.insertAfter(3);
	differentList.insertAfter(2);
	differentList.insertAfter(1);
	cout << "Lists equal? " << myList.equals(differentList) << endl;
	
	// Test the assignment operator
	List copyList = myList;
	cout << "Copy of List: " << copyList.to_string() << endl;
	
	// Test the coucat function
	List concatList = myList.concat(identicalList);
	cout << "Concatenated List: " << concatList.to_string() << endl;
	
	// Test the clear function
	myList.clear();
	cout << "The length of the List after clearing: " << myList.length() << endl;
	
	
	return 0;

}


/****************************************
Output of this Test:
Length of myList: 0
Front element: 3
Back element: 1
Current element: 3
Next element: 3
Current element: 1
Previous element: 1
Index of 5: 4
Index of 4: 2
List: (3, 5)
Lists equal? 0
Lists equal? 0
Copy of List: (3, 5)
Concatenated List: (3, 5, 3, 2, 1)
The length of the List after clearing: 0
****************************************/

