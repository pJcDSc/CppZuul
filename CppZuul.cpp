
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
void getItem(vector<char*>*, Room**, vector<Item*>*);
void dropItem(vector<char*>*, Room**, vector<Item*>*);
void printInv(vector<Item*>*);

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

  (*m)["Waterfall"] -> toggleLock("EAST", 3);
  (*m)["Waterfall"] -> setExitDesc("EAST", "A man blocks your way. He says: \"Give me flowers, or give me death.\"");
  
  (*m)["Chest Room"] -> addItem(new Item("Red_Key", 2));
  (*m)["Locksmith"] -> addItem(new Item("Green_Key", 4));
  
  //Floor Two
  (*m)["Lonely Room"] -> setExit("EAST", (*m)["Water Fountain"]);
  (*m)["Water Fountain"] -> setExit("WEST", (*m)["Lonely Room"]);
  (*m)["Water Fountain"] -> setExit("SOUTH", (*m)["Western Corridor"]);
  (*m)["Water Fountain"] -> setExit("EAST", (*m)["A Tree"]);
  (*m)["A Tree"] -> setExit("WEST", (*m)["Water Fountain"]);
  (*m)["Western Corridor"] -> setExit("NORTH", (*m)["Water Fountain"]);
  (*m)["Western Corridor"] -> setExit("WEST", (*m)["Kitchen"]);
  (*m)["Western Corridor"] -> setExit("SOUTH", (*m)["Red Stairs Down"]);
  (*m)["Kitchen"] -> setExit("EAST", (*m)["Western Corridor"]);
  (*m)["Red Stairs Down"] -> setExit("NORTH", (*m)["Western Corridor"]);
  (*m)["Red Stairs Down"] -> setExit("DOWN", (*m)["Red Stairs Up"]);
  (*m)["Eastern Corridor"] -> setExit("WEST", (*m)["Western Corridor"]);
  (*m)["Eastern Corridor"] -> setExit("EAST", (*m)["East Eastern Corridor"]);
  (*m)["Eastern Corridor"] -> setExit("SOUTH", (*m)["Monkey"]);
  (*m)["East Eastern Corridor"] -> setExit("WEST", (*m)["Eastern Corridor"]);
  (*m)["East Eastern Corridor"] -> setExit("EAST", (*m)["Red Ladder Up"]);
  (*m)["Red Ladder Up"] -> setExit("WEST", (*m)["East Eastern Corridor"]);
  (*m)["Red Ladder Up"] -> setExit("UP", (*m)["Red Ladder Down"]);
  (*m)["Monkey"] -> setExit("NORTH", (*m)["Eastern Corridor"]);
  (*m)["Monkey"] -> setExit("SOUTH", (*m)["Ending Room"]);
  
  (*m)["Lonely Room"] -> toggleLock("EAST", 1);
  (*m)["Lonely Room"] -> setExitDesc("EAST", "A locked yellow door blocks your way.");
  (*m)["Water Fountain"] -> toggleLock("EAST", 2);
  (*m)["Water Fountain"] -> setExitDesc("EAST", "A locked red door blocks your way.");
  (*m)["Monkey"] -> toggleLock("SOUTH", 4);
  (*m)["Monkey"] -> setExitDesc("SOUTH", "A locked green door blocks your way. Something cool is behind it.");

  (*m)["Lonely Room"] -> addItem(new Item("Yellow_Key", 1));
  (*m)["Kitchen"] -> addItem(new Item("Wrench"));

  //Floor Three
  (*m)["Tree"] -> setExit("EAST", (*m)["Art Room"]);
  (*m)["Art Room"] -> setExit("WEST", (*m)["Tree"]);
  (*m)["Art Room"] -> setExit("EAST", (*m)["Computer Room"]);
  (*m)["Computer Room"] -> setExit("WEST", (*m)["Art Room"]);
  (*m)["Computer Room"] -> setExit("SOUTH", (*m)["Red Ladder Down"]);
  (*m)["Red Ladder Down"] -> setExit("DOWN", (*m)["Red Ladder Up"]);

  (*m)["Art Room"] -> addItem(new Item("Pencils"));
  
  vector<Item*>* inventory = new vector<Item*>();
  Room* currentRoom = (*m)["Lonely Room"];
  bool running = true;
  char* command = new char();
  while (running) {
    cout << endl;
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
    bool hasItems = false;
    vector<Item*>* items = currentRoom -> getItems();
    vector<Item*>::iterator itemIt = items -> begin();
    while (itemIt != items -> end()) {
      if (!hasItems) {
	cout << "Items in this room: ";
	hasItems = true;
      }
      cout << (*itemIt) -> getName() << " ";
      ++itemIt;
    }
    if(!hasItems) cout << "No items in this room.";
    cout << endl << endl;
    
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
  } else if (strcmp(command, "GET") == 0) {
    getItem(commands, currentRoom, inventory);
  } else if (strcmp(command, "DROP") == 0) {
    dropItem(commands, currentRoom, inventory);
  } else if (strcmp(command, "INVENTORY") == 0 || strcmp(command, "ITEMS") == 0) {
    printInv(inventory);
  } else if (strcmp(command, "QUIT") == 0) {
    cout << "Thanks for playing!" << endl;
    return false;
  }
  else {
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
	      cin.clear();
	      cin.ignore();
	      firstTime = false;
	    }
	    if (strcmp(in, "y") == 0) {
	      (*currentRoom) -> toggleLock(it->first, 0);
	      (*currentRoom) = it -> second;
	      inventory -> erase(iit);
	      return;
	    } else {
	      cout << "You don't use it." << endl;
	      return;
	    }
	  }
	  ++iit;
	}
	cout << (*currentRoom)->getExitDesc(it -> first) << endl;
	return;
      }
      (*currentRoom) = it -> second;
      return;
    }
  }
  cout << "Could not find that exit" << endl;
}

void getItem(vector<char*>* commands, Room** currentRoom, vector<Item*>* inventory) {
  if (commands -> size() < 2) {
    cout << "Get what?" << endl;
    return;
  }
  vector<Item*>* roomItems = (*currentRoom) -> getItems();
  
  vector<Item*>::iterator it = roomItems -> begin();
  while (it != roomItems -> end()) {
    char* modItem = new char();
    strcpy(modItem, (*it)->getName());
    for (int i = 0; i < strlen(modItem); i++) {
      modItem[i] = toupper(modItem[i]);
    }
    if (strcmp(commands->at(1), modItem) == 0) {
      (*currentRoom)->removeItem(*it);
      inventory -> push_back(*it);
      cout << (*it) -> getName() << " has been added to your inventory." << endl;
      return;
    }
    ++it;
  }
  cout << "Item not found. " << endl;
}

void dropItem(vector<char*>* commands, Room** currentRoom, vector<Item*>* inventory) {
  if (commands -> size() < 2) {
    cout << "Drop What?" << endl;
    return;
  }

  vector<Item*>::iterator it = inventory -> begin();
  while (it != inventory -> end()) {
    char* modItem = new char();
    strcpy(modItem, (*it)->getName());
    for (int i = 0; i < strlen(modItem); i++) {
      modItem[i] = toupper(modItem[i]);
    }
    if (strcmp(modItem, commands -> at(1)) == 0) {
      inventory -> erase(it);
      (*currentRoom)->addItem(*it);
      cout << "You dropped " << (*it)->getName() << endl;
      return;
    }
    ++it;
  }
  cout << "Could not find item." << endl;
}

void printInv(vector<Item*>* inventory) {
  vector<Item*>::iterator it = inventory -> begin();
  bool hasItems = false;
  while (it != inventory -> end()) {
    if (!hasItems) {
      cout << "You have: ";
      hasItems = true;
    }
    cout << (*it)->getName() << " ";
    ++it;
  }  
  if(!hasItems) cout << "You have no items :(";
  cout << endl;
}
