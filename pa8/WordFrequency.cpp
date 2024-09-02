/****************************************
* Name: Chucheng Xie
* UCSC UserID: cxie15
* 2023 Fall CSE101 PA8
* WordFrequency.cpp
* Main functions for Dictionary ADT
****************************************/


#include <iostream>
#include <string>
#include <fstream>

#include "Dictionary.h"

using namespace std;

#define MAX_LEN 300


int main(int argc, char **argv) { 

	int token_count, line_count;
	size_t begin, end, len;
	ifstream in;
	ofstream out;
	
	string line;
	string tokenBuffer;
	string token;
	
	string delim = " \t\\\"\',<.>/?;:[{]}|`~!@#$%^&*()-_=+0123456789";
	
	// check command line
	if (argc != 3) { 
	
		cerr << "Usage: " << argv[0] << " <input file> <output file>" << endl;
		return EXIT_FAILURE;
	
	}
	
	// open files for reading and writing
	in.open(argv[1]);
	
	if (!in.is_open()) { 
	
		cerr << "Unable to open file " << argv[1] << " for reading" << endl;
		return EXIT_FAILURE;
	
	}
	
	out.open(argv[2]);
	
	if (!out.is_open()) { 
	
		cerr << "Unable to open file " << argv[2] << " for writing" << endl;
		return EXIT_FAILURE;
	
	}
	
	
	// read each line of input file, and count tokens
	Dictionary D;
	
	line_count = 0;
	
	while (getline(in, line)) { 
	
		line_count++;
		len = line.length();
	
	
		// get tokens in this line
		token_count = 0;
		tokenBuffer = "";
	
	
		// get first token
		begin = min(line.find_first_not_of(delim, 0), len);
		end = min(line.find_first_of(delim, begin), len);
		token = line.substr(begin, end-begin);
	
		while (token!="") { 
	
			token_count++;
		
			for (int i = 0; i < (int)token.length(); i++) { 
		
				token[i] = tolower(token[i]);
		
			}
		
			D.contains(token) ? D.setValue(token, D.getValue(token)+1) : D.setValue(token, 1);
		
		
			// get next token
			begin = min(line.find_first_not_of(delim, end+1), len);
			end = min(line.find_first_of(delim, begin), len);
			token = line.substr(begin, end-begin);
	
		}
	
	}
	
	// moved outside
	out << D << "\n";
	
	
	// close all files
	in.close();
	out.close();
	
	
	return EXIT_SUCCESS;

}


