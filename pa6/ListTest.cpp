//-----------------------------------------------------------------------------
//  Connor Hamilton
//  coohamil 
//  2023 Fall PA6
//  ListTest.cpp
//  A test client for List ADT
//-----------------------------------------------------------------------------
#include<iostream>
#include<string>
#include<stdexcept>
#include"List.h"

using namespace std;

int main(){

   int i, n=10;
   List A, B, C, D;

   cout << "created lists" << endl;

   for(i=1; i<=n; i++){
      A.insertAfter(i);
      B.insertAfter(11-i);
      C.insertBefore(i);
      D.insertBefore(11-i);
   }

   cout << "inserted" << endl;

   cout << endl;
   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;
   cout << endl;

   A.moveBack();
   B.moveBack();
   C.moveFront();
   D.moveFront();

   cout << "moved" << endl;

   cout << "A = " << A << endl;
   cout << "A.position() = " << A.position() << endl;
   cout << "B = " << B << endl;
   cout << "B.position() = " << B.position() << endl;
   cout << "C = " << C << endl;
   cout << "C.position() = " << C.position() << endl;
   cout << "D = " << D << endl;
   cout << "D.position() = " << D.position() << endl;

   cout << endl << "B: ";
   for(i=1; i<=7; i++){
      cout << B.movePrev() << " ";
   }
   cout << endl << "B.position() = " << B.position() << endl;
   
   cout << endl << "C: ";
   for(i=1; i<=7; i++){
      cout << C.moveNext() << " ";
   }
   cout << endl << "C.position() = " << C.position() << endl;

   cout << endl;
   cout << "A==B is " << (A==B?"true":"false") << endl;
   cout << "B==C is " << (B==C?"true":"false") << endl;
   cout << "C==D is " << (C==D?"true":"false") << endl;
   cout << "D==A is " << (D==A?"true":"false") << endl;
   cout << endl;

   cout << B.findNext(5) << endl;
   cout << B << endl;
   B.eraseBefore();
   cout << B << endl;
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl;
   cout << B.findPrev(2) << endl;
   B.eraseBefore();
   B.eraseAfter();
   cout << B << endl;
   cout << B.position() << endl; 
   cout << B.findNext(20) << endl; 
   cout << B.position() << endl;
   cout << B.findPrev(20) << endl;
   cout << B.position() << endl;
   cout << endl;

   for( i=10; i>=1; i--){
      A.insertAfter(i);
      A.movePrev();
   }
   cout << "A = " << A << endl;
   for( i=1; i<=15; i++){
      A.moveNext();
   }
   cout << A.position() << endl;
   A.cleanup();
   cout << "A = " << A << endl;
   cout << A.position() << endl;
   cout << endl;

   List E = A;
   cout << "E==A is " << (E==A?"true":"false") << endl;

   cout << endl;

   cout << "testing concat" << endl;

   C.clear(); A.clear(); B.clear();
    A.insertAfter(1);
    A.insertAfter(2);
    A.insertAfter(3);
    B.insertAfter(4);
    B.insertAfter(5);
    B.insertAfter(6);

    cout << "hi" << endl;

    C = A.concat(B);
    cout << C.length() << endl;
    cout << "printing: " << endl;
    cout << C << endl;
    cout << "hi" << endl;
    if (C.length() != 6)
      return 1;
    return 0;

    cout << "finished concat" << endl;


   List F = A.concat(B);
   cout << "F = " << F << endl;
   cout << "length: " << F.length() << endl;
   cout << "front: " << F.front() << endl;
   cout << "back: " << F.back() << endl;
   cout << "position: " << F.position() << endl;
   for( i=1; i<=7; i++){
      cout << "peekNext: " << F.peekNext() << endl;
      F.insertBefore(-i);
      cout << F.moveNext() << endl; 
   }
   cout << "F = " << F << endl;

   cout << endl;

   cout << "test exceptions: " << endl;
   cout << "A = " << A << endl;
   A.moveFront();
   try{
      A.peekPrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.movePrev();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setBefore(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseBefore();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.moveBack();
   try{
      A.peekNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.moveNext();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.setAfter(5);
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.eraseAfter();
   }catch( std::range_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   A.clear();
   try{
      A.front();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }
   try{
      A.back();
   }catch( std::length_error& e ){
      cout << e.what() << endl;
      cout << "   continuing without interruption" << endl;
   }

   cout << endl;

   return( EXIT_SUCCESS );
}