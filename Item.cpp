/*
Author: Peter Jin
Date: 11/26/19
Item.Cpp Class stores basic functions, constructor, and destructor for items in Zuul
*/
#include <iostream>
#include <cstring>
#include "Item.h"

using namespace std;

//Constructor
Item::Item(char* c) {
  name = c;
  keyVal = 0;
}

//Overloaded Constructor
Item::Item(char* c, int i) {
  keyVal = i;
  name = c;
}

//Get Item Name
char* Item::getName() {
  return name;
}

//Get Key Value of Item
int Item::getKeyVal() {
  return keyVal;
}

//Destructor
Item::~Item() {
  delete name;
}
