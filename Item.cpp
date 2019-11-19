#include <iostream>
#include <cstring>
#include "Item.h"

using namespace std;

Item::Item(char* c) {
  cout << "Item constructor called with name " << c << endl;
  name = c;
  keyVal = 0;
}

Item::Item(char* c, int i) {
  cout << "Overloaded Item Constructor called with name " << c << " and keyval " << i << endl;
  keyVal = i;
  name = c;
}

Item::~Item() {
  cout << "Item Destructor called" << endl;
  delete name;
}
