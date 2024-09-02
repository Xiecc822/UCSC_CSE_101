/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA7
* DictionaryTest.cpp
* Dictionary Test Client for Dictionary ADT
****************************************/

#include <iostream>
#include <string>
#include <stdexcept>

#include "Dictionary.h"

using namespace std;


int main() { 

	cout << endl;
	
	// Create a new dictionary
	Dictionary D;
	
	// Insert some key-value pairs into the dictionary
	D.setValue("apple", 1);
	D.setValue("banana", 2);
	D.setValue("cherry", 3);
	
	// Test the size() function
	cout << "Dictionary size: " << D.size() << endl;
	
	// Test the contains() function
	cout << "Contains 'apple': " << D.contains("apple") << endl;
	cout << "Contains 'durian': " << D.contains("durian") << endl;
	
	// Test the getValue() function
	cout << "Value for 'banana': " << D.getValue("banana") << endl;
	
	// Test the hasCurrent() function
	cout << "Has current: " << D.hasCurrent() << endl;
	
	// Test the currentKey() and currentVal() functions
	D.begin();
	cout << "Current key: " << D.currentKey() << endl;
	cout << "Current value: " << D.currentVal() << endl;
	
	// Test the setValue() function
	D.setValue("apple", 4);
	cout << "New value for 'apple': " << D.getValue("apple") << endl;
	
	// Test the remove() function
	D.remove("banana");
	cout << "Dictionary size after removal: " << D.size() << endl;
	
	// Test the clear() function
	D.clear();
	cout << "Dictionary size after clear: " << D.size() << endl;
	
	// Test the pre_string() function
	D.setValue("dog", 1);
	D.setValue("cat", 2);
	D.setValue("bird", 3);
	cout << "Pre-order traversal: " << D.pre_string() << endl;
	
	// Test the overloaded operator<<
	cout << "Dictionary contents: " << endl;
	cout << D << endl;
	
	// Test the overloaded operator== and the copy constructor
	Dictionary E = D;
	cout << "D and E are equal: " << (D == E) << endl;
	
	// Test the overloaded operator=
	Dictionary F;
	F = D;
	cout << "D and F are equal: " << (D == F) << endl;
	
	// Test the iterator functions
	D.begin();
	
	while (D.hasCurrent()) { 
	
		cout << D.currentKey() << " -> " << D.currentVal() << endl;
		D.next();
	
	}
	
	
	cout << endl;
	
	
	// Check exceptions
	try { 
	
		D.getValue("foo");
	
	} catch (logic_error &e) { 
	
		cout << e.what() << endl;
		cout << "   continuing without interruption" << endl;
	
	}
	
	try { 
	
		D.remove("foo");
	
	} catch (logic_error &e) { 
	
		cout << e.what() << endl;
		cout << "   continuing without interruption" << endl;
	
	}
	
	try { 
	
		D.currentKey();
	
	} catch (logic_error &e) { 
	
		cout << e.what() << endl;
		cout << "   continuing without interruption" << endl;
	
	}
	
	try { 
	
		D.currentVal();
	
	} catch (logic_error &e) { 
	
		cout << e.what() << endl;
		cout << "   continuing without interruption" << endl;
	
	}
	
	try { 
	
		D.next();
	
	} catch (logic_error &e) { 
	
		cout << e.what() << endl;
		cout << "   continuing without interruption" << endl;
	
	}
	
	try { 
	
		D.prev();
	
	} catch (logic_error &e) { 
	
		cout << e.what() << endl;
		cout << "   continuing without interruption" << endl;
	
	}
	
	
	cout << endl;
	
	return(EXIT_SUCCESS);

}


/****************************************
Output of this Test:

Dictionary size: 3
Contains 'apple': 1
Contains 'durian': 0
Value for 'banana': 2
Has current: 0
Current key: apple
Current value: 1
New value for 'apple': 4
Dictionary size after removal: 2
Dictionary size after clear: 0
Pre-order traversal: dog
cat
bird

Dictionary contents: 
bird : 3
cat : 2
dog : 1

D and E are equal: 1
D and F are equal: 1
bird -> 3
cat -> 2
dog -> 1

Dictionary: getValue(): key "foo" does not exist
   continuing without interruption
Dictionary: remove(): key "foo" does not exist
   continuing without interruption
Dictionary: currentKey(): current undefined
   continuing without interruption
Dictionary: currentVal(): current undefined
   continuing without interruption
Dictionary: next(): current undefined
   continuing without interruption
Dictionary: prev(): current undefined
   continuing without interruption

****************************************/


