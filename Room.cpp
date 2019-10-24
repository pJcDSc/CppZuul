/*
Author: Peter Jin
Date: 10/16/2019
Room Class
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include "Room.h"
#include "Item.h"

using namespace std;

//Constructor
Room::Room(char* n, char* d) {
  this -> name = n;
  this -> desc = d;
}

//Get Items
vector<Item*>* Room::getItems() {
  return itemList;
}

//Get Exits
map<char*, Room*>* Room::getExits() {
  return exits;
}

//Get Exit locked
bool Room::getLocked(char* c) {
  return exitLocked[c];
}

//Get Exit Description
char* Room::getExitDesc(char* c) {
  return exitDescs[c];
}

//Toggle locked exit
bool Room::toggleLock(char* c, int i) {
  int originalState = exitLocked[c];
  exitLocked[c] = i;
  return originalState;
}

//Set Description of Exit
void Room::setExitDesc(char* c, char* d) {
  exitDescs[c] = d;
}

//Destructor 
Room::~Room() {
  //FINISH DESTRUCTOR
  vector<Item*>::iterator vecIt = itemList -> begin();
  while (vecIt != itemList -> end()) {
    delete (*vecIt);
    vecIt = itemList -> erase(vecIt);
  }
  delete itemList;

  map<char*, Room*>*::iterator mapIt = exits -> begin();
  while (mapIt != exits -> end()) {
    delete (*mapIt);
    mapIt = exits -> erase(vecIt);
  }
  delete exits;
  delete exitDescs;
} 

