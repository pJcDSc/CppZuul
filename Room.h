/*
Author: Peter Jin
Date: 10/16/2019
Room Class Header
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "Item.h"

using namespace std;

struct cmp_str {
    bool operator()(char const *a, char const *b) const
    {
      return strcmp(a,b) < 0;
    }
  };

class Room {
  
 public:

  //Constructor
  Room(char*, char*);

  //Get Items
  vector<Item*>* getItems();
  
  //Remove Items
  void removeItem(Item*);

  //Add Item
  Item* addItem(Item*);

  //Set Exit
  void setExit(char*, Room*);

  //Get Name
  char* getName();

  //Get Description
  char* getDescription();

  //Toggle locked exit
  int toggleLock(char*, int);

  //Get Exits
  map<char*, Room*>* getExits();

  //Get Exit locked
  int getLocked(char*);

  //Get Exit Description
  char* getExitDesc(char*);

  //Set Exit Description
  void setExitDesc(char*, char*);

  //Destructor
  ~Room();
  
 private:

  vector<Item*> v; //Vector for itemList
  vector<Item*>* itemList;
  map<char*, Room*, str_cmp>* exits;
  map<char*, char*>* exitDescs;
  map<char*, int>* exitLocked;
  char* desc;
  char* name;

};
