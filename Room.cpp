/*
Author: Peter Jin
Date: 10/16/2019
Room Class
*/

#include <iostream>
#include <cstring>
#include <vector>
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
bool Room::toggleLock(char* c) {
  bool originalState = exitLocked[c];
  exitLocked[c] = !originalState;
  return originalState;
}

//Set Description of Exit
void Room::setExitDesc(char* c, char* d) {
  exitDescs[c] = d;
}



