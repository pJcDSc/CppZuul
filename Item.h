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

  //Destructor
  ~Item();

 private:

  int keyVal;
  char* name;

};

#endif
