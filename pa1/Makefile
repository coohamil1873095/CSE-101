#------------------------------------------------------------------------------
# Connor Hamilton 
# coohamil 
# 2023 Fall PA1
# Makefile for CSE 101 Programming Assignment 1
#
# make                   makes Lex
# make ListTest          makes ListTest
# make ListClient        makes ListClient
# make clean             removes all binaries
# make checkTest         checks ListTest for memory errors
# make checkClient       checks ListClient for memory errors
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

ListClient: ListClient.o List.o
	gcc -std=c17 -Wall -o ListClient ListClient.o List.o

ListClient.o : ListClient.c List.h
	gcc -std=c17 -Wall -c ListClient.c

List.o : List.c List.h
	gcc -std=c17 -Wall -c List.c

clean :
	rm -f Lex ListTest ListClient Lex.o ListTest.o ListClient.o List.o

checkTest : 
	valgrind --leak-check=full ListTest

checkClient : 
	valgrind --leak-check=full ListClient

checkLex :
	valgrind --leak-check=full Lex in3 blah3

