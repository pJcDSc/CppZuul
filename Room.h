/*
Author: Peter Jin
Date: 10/16/2019
Room Class Header
*/

#include <iostream>
#include <cstring>
#include <vector>
#include "Item.h"

using namespace std;

class Room {

 public:

  //Constructor
  Room(char*, char*);

  //Get Items
  vector<Item*>* getItems();

  //Remove Items
  Item* removeItem(Item*);

  //Add Item
  void addItem(Item*);

  //Set Exit
  Room* setExit(char*, Room*);

  //Get Name
  char* getName();

  //Get Description
  char* getDescription();

  //Toggle locked exit
  bool toggleLock(char*);

  //Get Exits
  map<char*, Room*>* getExits();

  //Get Exit locked
  bool getLocked(char*);

  //Get Exit Description
  char* getExitDesc(char*);
  
 private:

  vector<Item*> v; //Vector for itemList
  vector<Item*>* itemList;
  map<char*, Room*>* exits;
  map<char*, char*>* exitDescs;
  map<char*, bool>* exitLocked;
  char* desc;
  char* name;

};
