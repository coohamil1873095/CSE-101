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
#include "BigInteger.h"


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
    
    std::string line1;
    std::getline(in, line1);

    std::string dummy;
    std::getline(in, dummy);

    std::string line2;
    std::getline(in, line2);

    BigInteger A(line1);
    BigInteger B(line2);

    out << A << std::endl;
    out << std::endl;
    out << B << std::endl;
    out << std::endl;
    out << A + B << std::endl;
    out << std::endl;
    out << A - B << std::endl;
    out << std::endl;
    out << A - A << std::endl;
    out << std::endl;
    out << 3*A - 2*B << std::endl;
    out << std::endl;
    out << A*B << std::endl;
    out << std::endl;
    out << A*A << std::endl;
    out << std::endl;
    out << B*B << std::endl;
    out << std::endl;
    out << 9*(A*A*A*A) + 16*(B*B*B*B*B) << std::endl;
    out << std::endl;

    

    // close files 
    in.close();
    out.close();

    return(EXIT_SUCCESS);

}
