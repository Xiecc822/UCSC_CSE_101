/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA7
* Dictionary.cpp
* Dictionary for Dictionary ADT
****************************************/

#include "Dictionary.h"


// Dictionary() creates new Dictionary in the empty state
Dictionary::Node::Node(keyType k, valType v) { 

	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;

}


Dictionary::Dictionary() { 

	nil = nullptr;
	current = nullptr;
	root = nullptr;
	num_pairs = 0;

}


// Dictionary copy constructor
Dictionary::Dictionary(const Dictionary &D) { 

	nil = new Node(" ", -1);
	current = nil;
	root = nil;
	num_pairs = 0;
	preOrderCopy(D.root, D.nil);

}


Dictionary::~Dictionary() { 

	clear();
	delete nil;

}


// inOrderString()
void Dictionary::inOrderString(std::string &s, Node *R) const { 

	if (R == nil) { 
	
		return;
	
	}
	
	inOrderString(s, R -> left);
	s += R -> key + " : " + std::to_string(R -> val) + '\n';
	inOrderString(s, R -> right);

}


// preOrderString()
void Dictionary::preOrderString(std::string &s, Node *R) const { 

	if (R == nil) { 
	
		return;
	
	}
	
	s += R -> key + '\n';
	preOrderString(s, R -> left);
	preOrderString(s, R -> right);

}


// preOrderCopy()
void Dictionary::preOrderCopy(Node *R, Node *N) { 

	if (R == N) { 
	
		return;
	
	}
	
	setValue(R -> key, R -> val);
	preOrderCopy(R -> left, N);
	preOrderCopy(R -> right, N);

}


// postOrderDelete()
void Dictionary::postOrderDelete(Node *R) { 

	if (R == nil) { 
	
		return;
	
	}
	
	postOrderDelete(R -> left);
	postOrderDelete(R -> right);
	
	delete(R);

}


// search()
Dictionary::Node *Dictionary::search(Node *R, keyType k) const { 

	if (R == nil) { 
	
		return R;
	
	}
	
	if (R -> key > k) { 
	
		return search(R -> left, k);
	
	} else if (R -> key < k) { 
	
		return search(R -> right, k);
	
	}
	
	return R;

}


// findMin()
Dictionary::Node* Dictionary::findMin(Node *R) { 

	if (R == nil) { 
	
		return nil;
	
	}
	
	Node *temp = R;
	
	while (temp -> left != nil) { 
	
		temp = temp -> left;
	
	}
	
	return temp;

}


// findMax()
Dictionary::Node* Dictionary::findMax(Node *R) { 

	if (R == nil) { 
	
		return nil;
	
	}
	
	Node *temp = R;
	
	while (temp -> right != nil) { 
	
		temp = temp -> right;
	
	}
	
	return temp;

}


// findNext()
Dictionary::Node* Dictionary::findNext(Node *N) { 

	if (N -> right != nil) { 
	
		return findMin(N -> right);
	
	}
	
	Node *temp = N -> parent;
	
	while (temp != nil && N == temp -> right) { 
	
		N = temp;
		temp = temp -> parent;
	
	}
	
	return temp;

}


// findPrev()
Dictionary::Node* Dictionary::findPrev(Node *N) { 

	if (N == nil) { 
	
		return nil;
	
	}
	
	if (N -> left != nil) { 
	
		return findMax(N -> left);
	
	}
	
	Node *temp = N -> parent;
	
	while (temp != nil && N == temp -> left) { 
	
		N = temp;
		temp = temp -> parent;
	
	}
	
	return temp;

}


// Access functions --------------------

// size()
int Dictionary::size() const { 

	return num_pairs;

}

// contains()
bool Dictionary::contains(keyType k) const { 

	return this -> search(root, k) != nil;

}

// getValue()
valType& Dictionary::getValue(keyType k) const { 

	Node *temp = this -> search(root, k);
	
	if (temp == nil) { 
	
		throw std::logic_error("Dictionary: getValue(): key \"" + k + "\" does not exist");
	
	}
	
	return temp -> val;

}

// hasCurrent()
bool Dictionary::hasCurrent() const { 

	return current != nil;

}

// currentKey()
keyType Dictionary::currentKey() const { 

	if (current == nil) { 
	
		throw std::logic_error("Dictionary: currentKey(): current undefined");
	
	}
	
	return current -> key;

}

// currentVal()
valType& Dictionary::currentVal() const { 

	if (current == nil) { 
	
		throw std::logic_error("Dictionary: currentVal(): current undefined");
	
	}
	
	return current -> val;

}


// Manipulation procedures --------------------

// clear()
void Dictionary::clear() { 

	postOrderDelete(root);
	root = nil;
	current = nil;
	num_pairs = 0;

}

// setValue()
void Dictionary::setValue(keyType k, valType value) { 

	Node *N = new Node(k, value);
	N -> left = nil;
	N -> right = nil;
	
	Node *parent = this -> nil;
	Node **currentptr = &this -> root;
	
	while (*currentptr != this -> nil) { 
	
		parent = *currentptr;
		
		if (k < (*currentptr) -> key) { 
		
			currentptr = &((*currentptr) -> left);
		
		} else if (k > (*currentptr) -> key) { 
		
			currentptr = &((*currentptr) -> right);
		
		} else { 
		
			(*currentptr) -> val = value;
			delete N;
			return;
		
		}
	
	}
	
	N -> parent = parent;
	*currentptr = N;
	
	num_pairs++;

}


// remove()
void Dictionary::remove(keyType k) { 

	if (!contains(k)) { 
	
		throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
	
	}
	
	
	Node *deltemp = search(root, k);
	
	if (deltemp -> left == nil || deltemp -> right == nil) {
	
		Node *child = deltemp -> left == nil ? deltemp -> right : deltemp -> left;
    
		if (deltemp -> parent == nil) {
		
			root = child;
      
		} else if (deltemp == deltemp -> parent -> left) {
		
			deltemp -> parent -> left = child;
      
		} else {
    
			deltemp -> parent -> right = child;
      
		}
    
		if (child != nil) child -> parent = deltemp -> parent;
    
	} else {
  
		Node *successor = findMin(deltemp -> right);
    
		if (successor -> parent != deltemp) {
    
			if (successor -> right != nil) successor -> right -> parent = successor -> parent;
      
			successor -> parent -> left = successor -> right;
			successor -> right = deltemp -> right;
			successor -> right -> parent = successor;
      
    }
    
		(deltemp == root ? root : deltemp -> parent -> left == deltemp ? deltemp -> parent -> left : deltemp -> parent -> right) = successor;
    
		successor -> parent = deltemp -> parent;
		successor -> left = deltemp -> left;
		successor -> left -> parent = successor;
    
	}

	if (current == deltemp) {
		
		current = nil;
		
	}
	
	delete deltemp;

	this->num_pairs--;

}


// begin()
void Dictionary::begin() { 

	if (num_pairs <= 0) { 
	
		throw std::length_error("Dictionary: begin(): Dictionary is empty");
	
	}
	
	current = findMin(root);

}

// end()
void Dictionary::end() { 

	if (num_pairs <= 0) { 
	
		throw std::length_error("Dictionary: end(): Dictionary is empty");
	
	}
	
	current = findMax(root);

}

// next()
void Dictionary::next() { 

	if (current == nil) { 
	
		throw std::logic_error("Dictionary: next(): current undefined");
	
	}
	
	current = findNext(current);

}

// prev()
void Dictionary::prev() { 

	if (current == nil) { 
	
		throw std::logic_error("Dictionary: prev(): current undefined");
	
	}
	
	current = findPrev(current);

}


// Other Functions --------------------

// to_string()
std::string Dictionary::to_string() const { 

	std::string s = "";
	inOrderString(s, root);
	return s;

}

// pre_string()
std::string Dictionary::pre_string() const { 

	std::string s = "";
	preOrderString(s, root);
	return s;

}

// equals()
bool Dictionary::equals(const Dictionary& D) const { 

	return (num_pairs == D.num_pairs) && (to_string() == D.to_string());

}


// Overloaded Operators --------------------

// operator<<()
std::ostream& operator<<( std::ostream& stream, Dictionary& D ) { 

	return stream << D.to_string();

}

// operator==()
bool operator==( const Dictionary& A, const Dictionary& B ) { 

	return A.equals(B);

}

// operator=()
Dictionary& Dictionary::operator=( const Dictionary& D ) { 

	if (this != &D) { 
	
		Dictionary temp = D;
		std::swap(nil, temp.nil);
		std::swap(root, temp.root);
		std::swap(current, temp.current);
		std::swap(num_pairs, temp.num_pairs);
	
	}
	
	return *this;

}


