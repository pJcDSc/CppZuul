/*
Author: Peter Jin
Date: 10/16/2019
Room Class
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <iterator>
#include <map>
#include "Room.h"
#include "Item.h"

using namespace std;

//Constructor
Room::Room(char* n, char* d) {
  cout << "Room constructor called with name '" << n << "' and description '" << d << "'" << endl;
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
int Room::getLocked(char* c) {
  return (*exitLocked)[c];
}

//Get Exit Description
char* Room::getExitDesc(char* c) {
  return (*exitDescs)[c];
}

//Toggle locked exit
int Room::toggleLock(char* c, int i) {
  int originalState = (*exitLocked)[c];
  (*exitLocked)[c] = i;
  return originalState;
}

//Set Description of Exit
void Room::setExitDesc(char* c, char* d) {
  (*exitDescs)[c] = d;
}

//Destructor 
Room::~Room() {
  cout << "Room Destructor Called" << endl;
  vector<Item*>::iterator vecIt = itemList -> begin();
  while (vecIt != itemList -> end()) {
    delete (*vecIt);
    vecIt = itemList -> erase(vecIt);
  }
  delete itemList;

  map<char*, Room*>::iterator mapIt = exits -> begin();
  while (mapIt != exits -> end()) {
    delete (mapIt->second);
    map<char*, Room*>::iterator toErase = mapIt;
    ++mapIt;
    exits -> erase(toErase);
  }
  delete exits;

  map<char*, char*>::iterator mapIt2 = exitDescs -> begin();
  while (mapIt2 != exitDescs->end()) {
    delete(mapIt2->second);
    map<char*, char*>::iterator toErase = mapIt2;
    ++mapIt2;
    exitDescs -> erase(toErase);
  }
  delete exitDescs;

  delete exitLocked;
  delete desc;
  delete name;
}

