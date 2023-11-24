//-----------------------------------------------------------------------------
// Connor Hamilton
// coohamil 
// 2023 Fall PA7
// Order.cpp
// Prints key-value pairs as well as a pre-order traversal of a tree from provided keys from an input file to an output file
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"Dictionary.h"


int main(int argc, char * argv[]){
    std::ifstream in;
    std::ofstream out;
    
    // check command line for correct number of arguments
    if (argc != 3 ) {
        std::cerr << "Usage: " << argv[0] << " <input file> <output file>" << std::endl;
        return(EXIT_FAILURE);
    }

    // open files for reading and writing 
    in.open(argv[1]);
    if( !in.is_open() ){
        std::cerr << "Unable to open file " << argv[1] << " for reading" << std::endl;
        return(EXIT_FAILURE);
    }

    out.open(argv[2]);
    if( !out.is_open() ){
        std::cerr << "Unable to open file " << argv[2] << " for writing" << std::endl;
        return(EXIT_FAILURE);
    }




    return(EXIT_SUCCESS);

}

