/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA8
* Dictionary.cpp
* Dictionary for Dictionary ADT
****************************************/

#include "Dictionary.h"

#define BLACK 0
#define RED 1


// Dictionary() creates new Dictionary in the empty state
Dictionary::Node::Node(keyType k, valType v) { 

	key = k;
	val = v;
	parent = nullptr;
	left = nullptr;
	right = nullptr;
	color = BLACK;

}


Dictionary::Dictionary() { 

	nil = new Node(" ", -1);
	current = nil;
	root = nil;
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
	
	s += R -> key + (R -> color == RED ? " (RED)" : "") + '\n';
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
void Dictionary::setValue(keyType k, valType v) { 

	Node *N = new Node(k, v);
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
		
			(*currentptr) -> val = v;
			delete N;
			return;
		
		}
	
	}
	
	N -> parent = parent;
	N -> color = RED;
	*currentptr = N;
	
	RB_InsertFixUp(N);
	num_pairs++;

}


// remove()
void Dictionary::remove(keyType k) { 

	if (!contains(k)) { 
	
		throw std::logic_error("Dictionary: remove(): key \"" + k + "\" does not exist");
	
	}
	
	if (current -> key == k) { 
	
		current = nil;
	
	}
	
	RB_Delete(search(root, k));
	
	num_pairs--;

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


// RBT Helper Functions --------------------

// LeftRotate()
void Dictionary::LeftRotate(Node *N) { 

	Node *rightChild = N -> right;
	Node *leftGrandchild = rightChild -> left;
	rightChild -> left = N;
	N -> right = leftGrandchild;
	rightChild -> parent = N -> parent;
	
	if (N -> parent == nil) { 
	
		root = rightChild;
	
	} else if (N == N -> parent -> left) { 
	
		N -> parent -> left = rightChild;
	
	} else { 
	
		N -> parent -> right = rightChild;
	
	}
	
	N -> parent = rightChild;
	
	if (leftGrandchild != nil) { 
	
		leftGrandchild -> parent = N;
	
	}

}


// RightRotate()
void Dictionary::RightRotate(Node *N) { 

	Node *leftChild = N -> left;
	Node *rightGrandchild = leftChild -> right;
	leftChild -> right = N;
	N -> left = rightGrandchild;
	leftChild -> parent = N -> parent;
	
	if (N -> parent == nil) { 
	
		root = leftChild;
	
	} else if (N == N -> parent -> right) { 
	
		N -> parent -> right = leftChild;
	
	} else { 
	
		N -> parent -> left = leftChild;
	
	}
	
	N -> parent = leftChild;
	
	if (rightGrandchild != nil) { 
	
		rightGrandchild -> parent = N;
	
	}

}


// RB_InsertFixUp()
void Dictionary::RB_InsertFixUp(Node *N) { 

	while (N -> parent -> color == RED) { 
	  
	  	Node *grandparent = N -> parent -> parent;
	  
		if (N -> parent == grandparent -> left) { 
	
			Node *uncle = grandparent -> right;
		
			if (uncle -> color == RED) { 
		
				N -> parent -> color = uncle -> color = BLACK;
				grandparent -> color = RED;
				N = grandparent;
		
			} else if (N == N -> parent -> right) { 
		
				N = N -> parent;
				LeftRotate(N);
		
			} else { 
		
				N -> parent -> color = BLACK;
				grandparent -> color = RED;
				RightRotate(grandparent);
		
			}
	
		} else { 
	
			Node *uncle = grandparent -> left;
		
			if (uncle -> color == RED) { 
		
				N -> parent -> color = uncle -> color = BLACK;
				grandparent -> color = RED;
				N = grandparent;
		
			} else if (N == N -> parent -> left) { 
		
				N = N -> parent;
				RightRotate(N);
		
			} else { 
		
				N -> parent -> color = BLACK;
				grandparent -> color = RED;
				LeftRotate(grandparent);
		
			}
	
		}
		
	}
	
	root -> color = BLACK;

}


// RB_Transplant()
void Dictionary::RB_Transplant(Node *u, Node *v) { 

	if (u -> parent == nil) { 
	
		root = v;
	
	} else { 
	
		if (u == u -> parent -> left) { 
		
			u -> parent -> left = v;
		
		} else { 
		
			u -> parent -> right = v;
		
		}
	
	}
	
	v -> parent = u -> parent;

}


// RB_DeleteFixUp()
void Dictionary::RB_DeleteFixUp(Node *N) { 

	while (N != root && N -> color == BLACK) { 
	
		Node *sibling = (N == N -> parent -> left) ? N -> parent -> right : N -> parent -> left;
		
		if (sibling -> color == RED) { 
		
			sibling -> color = BLACK;
			N -> parent -> color = RED;
			
			if (N == N -> parent -> left) { 
			
				LeftRotate(N -> parent);
				sibling = N -> parent -> right;
			
			} else { 
			
				RightRotate(N -> parent);
				sibling = N -> parent -> left;
			
			}
		
		}
		
		if (sibling -> left -> color == BLACK && sibling -> right -> color == BLACK) { 
		
			sibling -> color = RED;
			N = N -> parent;
		
		} else { 
		
			if (N == N -> parent -> left && sibling -> right -> color == BLACK) { 
			
				sibling -> left -> color = BLACK;
				sibling -> color = RED;
				RightRotate(sibling);
				sibling = N -> parent -> right;
			
			} else if (N == N -> parent -> right && sibling -> left -> color == BLACK) { 
			
				sibling -> right -> color = BLACK;
				sibling -> color = RED;
				LeftRotate(sibling);
				sibling = N -> parent -> left;
			
			}
			
			sibling -> color = N -> parent -> color;
			N -> parent -> color = BLACK;
			
			if (N == N -> parent -> left) { 
			
				sibling -> right -> color = BLACK;
				LeftRotate(N -> parent);
			
			} else { 
			
				sibling -> left -> color = BLACK;
				RightRotate(N -> parent);
			
			}
			
			N = root;
		
		}
	
	}
	
	N -> color = BLACK;

}


// RB_Delete()
void Dictionary::RB_Delete(Node *N) { 

	Node *node = N;
	Node *temp;
	int node_color = node -> color;
	
	if (node -> left == nil) { 
	
		temp = node -> right;
		RB_Transplant(node, node -> right);
	
	} else if (node -> right == nil) { 
	
		temp = node -> left;
		RB_Transplant(node, node -> left);
	
	} else { 
	
		node = findMin(node->right);
		node_color = node -> color;
		temp = node -> right;
		RB_Transplant(node, node -> right);
		node -> right = N -> right;
		node -> right -> parent = node;
		RB_Transplant(N, node);
		node -> left = N -> left;
		node -> left -> parent = node;
		node -> color = N -> color;
	
	}
	
	if (node_color == BLACK) { 
	
		RB_DeleteFixUp(temp);
	
	}
	
	delete N;

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


