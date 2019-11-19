#ifndef ITEM_H
#define ITEM_H

#include <iostream>
#include <cstring>

using namespace std;

class Item {

 public:

  //Constructor
  Item(char*);

  //Overloaded constructor
  Item(char*, int);

  //Get Name
  char* getName();

  //Get Key Val
  int getKeyVal();
  
  //Destructor
  ~Item();

 private:

  int keyVal;
  char* name;

};

#endif
