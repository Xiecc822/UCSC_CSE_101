/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA8
* Order.cpp
* Main functions for Dictionary ADT
****************************************/

#include <iostream>
#include <string>
#include <fstream>

#include "Dictionary.h"

using namespace std;


int main(int argc, char **argv) { 

	// check command line
	ifstream in;
	ofstream out;
	
	if (argc != 3) { 
	
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return(EXIT_FAILURE);
	
	}
	
	// open files for reading and writing
	in.open(argv[1]);
	
	if (!in.is_open()) { 
	
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return(EXIT_FAILURE);
	
	}
	
	out.open(argv[2]);
	
	if (!out.is_open()) { 
	
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return(EXIT_FAILURE);
	
	}
	
	
	// read each line of input file, count and print tokens
	Dictionary D;
	string s;
	
	for (int i = 1; getline(in, s); i++) { 
	
		D.setValue(s, i);
	
	}
	
	out << D << '\n' << D.pre_string() << '\n';
	
	// clear the Dictionary
	D.clear();
	
	// close the input and output files
	in.close();
	out.close();
	
	
	return(EXIT_SUCCESS);

}


