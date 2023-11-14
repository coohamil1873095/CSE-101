//-----------------------------------------------------------------------------
//  Connor Hamilton
//  coohamil 
//  2023 Fall PA5
//  Shuffle.cpp
//  Given a deck with n number of cards, prints a table of the number of shuffles to return the deck to its original state
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"List.h"

void shuffle(List& D) {
    int mid = D.length() / 2;
    int i;
    List E;
    D.moveBack();

    // insert latter half of list first
    for (i = D.length() - 1; i >= mid; i--) {
        E.insertAfter(D.movePrev());
    }

    // prepare for merge
    E.moveFront();
    D.moveFront();
    if (mid <= 1) {
        E.moveNext();
        E.insertBefore(D.moveNext());
    }
    else {
        for (i = 0; i < mid; i++)  {
            E.moveNext();
            E.insertBefore(D.moveNext());
        }
    }
    
    D = E;
}

int main(int argc, char * argv[]){
    // check command line for correct number of arguments
    if (argc != 2 ) {
        std::cerr << "Usage: " << argv[0] << " <num cards>" << std::endl;
        return(EXIT_FAILURE);
    }

    int numCards = 0;

    try {
        numCards = std::stoi(argv[1]);
    }
    catch (std::invalid_argument& e) {
        std::cerr << "Usage: " << argv[0] << " <num cards>" << std::endl;
        return(EXIT_FAILURE);
    }

    std::cout << "deck size\tshuffle count" << std::endl;
    std::cout << "------------------------------" << std::endl;

    int i;
    List L, C;

    // perform shuffles 
    for (i = 1; i <= numCards; i++) {
        L.moveBack();
        L.insertBefore(i - 1);
        int shuffleCount = 1;
        C = L;

        // loop until deck is shuffled back to original state
        if (L.length() > 1) {
            shuffle(L);
            while (!(L == C)) {
                shuffle(L);
                shuffleCount += 1;
            }            
        }
        std::cout << " " << i << "\t\t" << shuffleCount << std::endl;
    }

    return(EXIT_SUCCESS);

}