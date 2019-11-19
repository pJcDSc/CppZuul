
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "Room.h"
#include "Item.h"
using namespace std;

void addRoom(map<char*, Room*>*, char*, char*); 
vector<char*>* split(char*, char);
bool parse(char*, Room**, vector<Item*>*);
void printHelp();
void goExit(vector<char*>*, Room**, vector<Item*>*);

int main() {  
  map<char*, Room*>* m = new map<char*, Room*>;
  addRoom(m, "Chest Room", "A chest sits in the center of the room.");
  addRoom(m, "Waterfall", "Music box triggers memories within you.");
  addRoom(m, "Red Stairs Up", "Stairs, but red. Probably not blood.");
  addRoom(m, "Locksmith", "Many keys hang on the walls. This guy is good at making keys.");
  addRoom(m, "Lonely Room", "Only one door lies in the east.");
  addRoom(m, "Water Fountain", "It appears to be broken. Maybe you can fix it with a wrench?");
  addRoom(m, "Western Corridor", "A loooong corridor. Feels like the west one (?)");
  addRoom(m, "Kitchen", "Why is there a wrench in the kitchen?");
  addRoom(m, "Red Stairs Down", "Red stairs go down. Not sure why they're red.");
  addRoom(m, "Eastern Corridor", "A corridor. An east one by the looks of it.");
  addRoom(m, "A Tree", "Just a sapling. Maybe if you water it?");
  addRoom(m, "Monkey", "He's holding a flower. You REALLY want that flower. You need to trade something with it.");
  addRoom(m, "Ending Room", "This room has a sense of finality to it.");
  addRoom(m, "East Eastern Corridor", "Another corridor. Very east. You can tell because.");
  addRoom(m, "Red Ladder Up", "A ladder that goes up. Also suspiciously red.");
  addRoom(m, "Tree", "Looks like you can't go back down.");
  addRoom(m, "Art Room", "SO MANY ART SUPPLIES WOOOOOOOOO");
  addRoom(m, "Computer Room", "Coding looks cool");
  addRoom(m, "Red Ladder Down", "No but why is it red?");
  
  //Floor One
  (*m)["Chest Room"] -> setExit("EAST", (*m)["Waterfall"]);
  (*m)["Waterfall"] -> setExit("EAST", (*m)["Locksmith"]);
  (*m)["Waterfall"] -> setExit("SOUTH", (*m)["Red Stairs Up"]);
  (*m)["Waterfall"] -> setExit("WEST", (*m)["Chest Room"]);
  (*m)["Red Stairs Up"] -> setExit("NORTH", (*m)["Waterfall"]);
  (*m)["Red Stairs Up"] -> setExit("UP", (*m)["Red Stairs Down"]);
  
  //Floor Two
  (*m)["Lonely Room"] -> setExit("EAST", (*m)["Water Fountain"]);
  (*m)["Water Fountain"] -> setExit("WEST", (*m)["Lonely Room"]);
  (*m)["Water Fountain"] -> setExit("SOUTH", (*m)["Western Corridor"]);
  (*m)["Water Fountain"] -> setExit("EAST", (*m)["A Tree"]);
  (*m)["A Tree"] -> setExit("WEST", (*m)["Water Fountain"]);
  (*m)["A Tree"] -> setExit("UP", (*m)["Tree"]);
  
  (*m)["A Tree"] -> toggleLock("UP", 1);
  (*m)["Lonely Room"] -> toggleLock("EAST", 1);
  (*m)["Water Fountain"] -> toggleLock("EAST", 2);

  vector<Item*>* inventory = new vector<Item*>();
  Room* currentRoom = (*m)["Lonely Room"];
  bool running = true;
  char* command = new char();
  while (running) {
    command = new char();
    cout << "You are in " << currentRoom -> getName() << "." << endl;
    cout << currentRoom -> getDescription() << endl;
    cout << "Exits: ";
    map<char*, Room*>* exits = currentRoom -> getExits();
    map<char*, Room*>::iterator it;
    for(it = exits -> begin(); it != exits -> end(); ++it) {
      cout << it -> first << " ";
    }
    cout << endl;
    
    cin.get(command, 80);
    cin.clear();
    cin.ignore(9999, '\n');

    running = parse(command, &currentRoom, inventory);
  }
  return 0;
}

void addRoom(map<char*, Room*>* m, char* title, char* desc) {
  (*m)[title] = new Room(title, desc);
}

vector<char*>* split(char* c, char delim) {
  vector<char*>* v = new vector<char*>;
  char* build = new char[strlen(c)];
  int ind = 0;
  for (int i = 0; i < strlen(c); i++) {
    if (c[i] != delim) {
      build[ind++] = c[i];
    } else {
      v -> push_back(build);
      build = new char[strlen(c)];
      ind = 0;
    }
  }
  if (build) v -> push_back(build);
  return v;
}

bool parse(char* c, Room** currentRoom, vector<Item*>* inventory) {
  vector<char*>* commands = split(c, ' ');
  for(int i = 0; i < commands -> size(); i++) {
    for(int j = 0; j < strlen(commands -> at(i)); j++) {
      commands -> at(i)[j] = toupper(commands -> at(i)[j]);
    }
  }
  char* command = commands -> at(0);
  if (strcmp(command, "HELP") == 0) {
    printHelp();
  } else if (strcmp(command, "GO") == 0) {
    goExit(commands, currentRoom, inventory);
  } else {
    cout << "Sorry, command not recognized" << endl;
  }
  return true;
}

void printHelp() {
  cout << "Commands: " << endl;
  cout << "\"Go\" + (direction): Take an exit in a specific direction (If it exists)" << endl;
  cout << "\"Drop\" + (item): Drop item from your inventory (If it is in there) " << endl;
  cout << "\"Get\" + (item): Get item from the room (If it exists)" << endl;
  cout << "\"Quit\": Quit the game" << endl;
  cout << "\"Inventory\"/\"Items\": Print items in your inventory" << endl;
}

void goExit(vector<char*>* c, Room** currentRoom, vector<Item*>* inventory) {
  cout << "Go called" << endl;
  if (c -> size() < 2) {
    cout << "Where go?" << endl;
    return;
  }
  map<char*, Room*>* exits = (*currentRoom) -> getExits();

  char* direction = c -> at(1);
  for (int i = 0; i < strlen(direction); i++) {
    direction[i] = toupper(direction[i]);
  }

  map<char*, Room*>::iterator it;
  for(it = exits -> begin(); it != exits -> end(); ++it) {
    if (strcmp(it -> first, direction) == 0) {
      if ((*currentRoom)->getLocked(it->first) != 0) {
	int lockVal = (*currentRoom)->getLocked(it->first);
	vector<Item*>::iterator iit = inventory -> begin();
	while(iit != inventory -> end()) {
	  if (lockVal == (*iit) -> getKeyVal()) {
	    cout << "You have the key. Unlock? (y/n)" << endl;
	    char* in = new char();
	    bool firstTime = true;
	    while (strcmp(in, "y") != 0 && strcmp(in, "n") != 0) {
	      if(!firstTime) cout << "Please enter either \"y\" or \"n\"" << endl;
	      cin.get(in, 20);
	      firstTime = false;
	    }
	    if (strcmp(in, "y") == 0) {
	      (*currentRoom) -> toggleLock(it->first, 0);
	      (*currentRoom) = it -> second;
	      inventory -> erase(iit);
	      delete *iit;
	      return;
	    } else {
	      cout << "You don't use it." << endl;
	      return;
	    }
	  }
	}
	cout << "It's locked." << endl;
	return;
      }
      (*currentRoom) = it -> second;
      return;
    }
  }
  cout << "Could not find that exit" << endl;
}
