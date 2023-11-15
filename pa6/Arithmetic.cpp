//-----------------------------------------------------------------------------
//  Connor Hamilton
//  coohamil 
//  2023 Fall PA6
//  Arithmetic.cpp
//  Performs arithmetic operations given two Big Integers from an input file into an output file
//-----------------------------------------------------------------------------
#include<iostream>
#include<fstream>
#include<string>
#include<stdexcept>
#include"List.h"


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