/*
Author: Peter Jin
Date: 10/16/2019
Room Class Header
*/

#include <iostream>
#include <cstring>
#include "Item.h"

using namespace std;

class Room {

 public:

  //Constructor
  Room(char*, char*);

  //Get Items
  vector<Item*>* getItems();

  //Get Exit
  Room getExit(char*);

  //Remove Items
  Item removeItem(Item);

  //Add Item
  void addItem(Item);

  //Set Exit
  Room setExit(char*, Room);

  //Get Name
  char* getName();

  //Get Description
  char* getDescription();
  
 private:

  vector<Item*> v;
  vector<Item*>* itemList;
  map<char*, Room> exits;
  char* description;
  char* name;

};
