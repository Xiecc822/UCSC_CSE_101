#------------------------------------------------------------------------------
# Name: Chucheng Xie
# UCSC UserID: cxie15
# 2023 Fall CSE101 PA1
# Makefile
#------------------------------------------------------------------------------
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListTest          makes ListTest
# make clean             removes all binaries
# make checkClient       checks ListTest for memory errors
# make checkLex          checks Lex for memory errors
#------------------------------------------------------------------------------

Lex : Lex.o List.o
	gcc -std=c17 -Wall -o Lex Lex.o List.o

Lex.o : Lex.c List.h
	gcc -std=c17 -Wall -c Lex.c

ListTest: ListTest.o List.o
	gcc -std=c17 -Wall -o ListTest ListTest.o List.o

ListTest.o : ListTest.c List.h
	gcc -std=c17 -Wall -c ListTest.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

clean :
	rm -f Lex ListTest Lex.o ListTest.o List.o

checkClient : 
	valgrind --leak-check=full ListTest

checkLex :
	valgrind --leak-check=full Lex in3 blah3



