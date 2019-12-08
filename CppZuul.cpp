/*
Author: Peter Jin
Date: 11/26/19
CppZuul: A text based game where you run around between rooms.
Pick up items AND drop them!
You can also open doors with corresponding key colors. 
Try to get to the ending room!
*/
#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "Room.h"
#include "Item.h"
using namespace std;

//Declare function prototypes
void addRoom(map<char*, Room*>*, char*, char*); 
vector<char*>* split(char*, char);
bool parse(char*, Room**, vector<Item*>*);
void printHelp();
void goExit(vector<char*>*, Room**, vector<Item*>*);
void getItem(vector<char*>*, Room**, vector<Item*>*);
void dropItem(vector<char*>*, Room**, vector<Item*>*);
void printInv(vector<Item*>*);

int main() {
  //Make map to store rooms and access them by name
  map<char*, Room*>* m = new map<char*, Room*>;

  //Declare and Initialize all rooms into map
  addRoom(m, "Chest Room", "A chest sits in the center of the room.");
  addRoom(m, "Waterfall", "Music box triggers memories within you.");
  addRoom(m, "Red Stairs Up", "Stairs, but red. Probably not blood.");
  addRoom(m, "Locksmith", "Many keys hang on the walls. This guy is good at making keys.");
  addRoom(m, "Lonely Room", "Only one door lies in the east.");
  addRoom(m, "Water Fountain", "It appears to be broken. Maybe you can fix it with a wrench?");
  addRoom(m, "Western Corridor", "A loooong corridor. Feels like the west one (?)");
  addRoom(m, "Kitchen", "Why is there a wrench in the kitchen?");
  addRoom(m, "Red Stairs Down", "Red stairs go down. Not sure why they're red.");
  addRoom(m, "Eastern Corridor", "The Eastern Corridor. There's a slide west but you won't be able to go back up.");
  addRoom(m, "A Tree", "Just a sapling. Maybe if you water it?");
  addRoom(m, "Monkey", "He's holding a flower. You REALLY want that flower. You need to trade something with it.");
  addRoom(m, "Ending Room", "This room has a sense of finality to it.");
  addRoom(m, "East Eastern Corridor", "Another corridor. Very east. You can tell because it feels east.");
  addRoom(m, "Red Ladder Up", "A ladder that goes up. Also suspiciously red.");
  addRoom(m, "Tree", "Looks like you can't go back down.");
  addRoom(m, "Art Room", "SO MANY ART SUPPLIES WOOOOOOOOO");
  addRoom(m, "Computer Room", "Coding looks cool");
  addRoom(m, "Red Ladder Down", "No but why is it red?");
  
  //Floor One Exits
  (*m)["Chest Room"] -> setExit("EAST", (*m)["Waterfall"]);
  (*m)["Waterfall"] -> setExit("EAST", (*m)["Locksmith"]);
  (*m)["Waterfall"] -> setExit("SOUTH", (*m)["Red Stairs Up"]);
  (*m)["Waterfall"] -> setExit("WEST", (*m)["Chest Room"]);
  (*m)["Red Stairs Up"] -> setExit("NORTH", (*m)["Waterfall"]);
  (*m)["Red Stairs Up"] -> setExit("UP", (*m)["Red Stairs Down"]);
  (*m)["Locksmith"] -> setExit("WEST", (*m)["Waterfall"]);

  //Floor One Locks 
  (*m)["Waterfall"] -> toggleLock("EAST", 3);
  (*m)["Waterfall"] -> setExitDesc("EAST", "A man blocks your way. He says: \"Give me flowers, or give me death.\"");

  //Floor One Items
  (*m)["Chest Room"] -> addItem(new Item("Red_Key", 2));
  (*m)["Locksmith"] -> addItem(new Item("Green_Key", 4));
  
  //Floor Two Exits
  (*m)["Lonely Room"] -> setExit("EAST", (*m)["Water Fountain"]);
  (*m)["Water Fountain"] -> setExit("WEST", (*m)["Lonely Room"]);
  (*m)["Water Fountain"] -> setExit("SOUTH", (*m)["Western Corridor"]);
  (*m)["Water Fountain"] -> setExit("EAST", (*m)["A Tree"]);
  (*m)["A Tree"] -> setExit("WEST", (*m)["Water Fountain"]);
  (*m)["A Tree"] -> setExit("UP", (*m)["Tree"]);
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

  //Floor Two Locks
  (*m)["Lonely Room"] -> toggleLock("EAST", 1);
  (*m)["Lonely Room"] -> setExitDesc("EAST", "A locked yellow door blocks your way.");
  (*m)["Water Fountain"] -> toggleLock("EAST", 2);
  (*m)["Water Fountain"] -> setExitDesc("EAST", "A locked red door blocks your way.");
  (*m)["Monkey"] -> toggleLock("SOUTH", 4);
  (*m)["Monkey"] -> setExitDesc("SOUTH", "A locked green door blocks your way. Something cool is behind it.");
  (*m)["A Tree"] -> toggleLock("UP", -1);
  (*m)["A Tree"] -> setExitDesc("UP", "You could go up here if you grew the tree....");

  //Floor Two Items
  (*m)["Lonely Room"] -> addItem(new Item("Yellow_Key", 1));
  (*m)["Kitchen"] -> addItem(new Item("Wrench"));
  (*m)["Ending Room"] -> addItem(new Item("A lot of gold"));
  (*m)["Ending Room"] -> addItem(new Item("Gaming Console"));
  (*m)["Ending Room"] -> addItem(new Item("Many more bananas"));

  //Floor Three Exits
  (*m)["Tree"] -> setExit("EAST", (*m)["Art Room"]);
  (*m)["Art Room"] -> setExit("WEST", (*m)["Tree"]);
  (*m)["Art Room"] -> setExit("EAST", (*m)["Computer Room"]);
  (*m)["Computer Room"] -> setExit("WEST", (*m)["Art Room"]);
  (*m)["Computer Room"] -> setExit("SOUTH", (*m)["Red Ladder Down"]);
  (*m)["Red Ladder Down"] -> setExit("DOWN", (*m)["Red Ladder Up"]);
  (*m)["Red Ladder Down"] -> setExit("NORTH", (*m)["Computer Room"]);

  //Floor Three Items
  (*m)["Art Room"] -> addItem(new Item("Pencils"));

  //Vector to act as player inventory
  vector<Item*>* inventory = new vector<Item*>();

  //current room player is in, starts in lonely room
  Room* currentRoom = (*m)["Lonely Room"];
  bool running = true;
  char* command = new char();

  //Main game loop
  while (running) {
    cout << endl;
    command = new char();

    //Tell name and description of room
    cout << "You are in " << currentRoom -> getName() << "." << endl;
    cout << currentRoom -> getDescription() << endl;

    //Tell exits
    cout << "Exits: ";

    //Get current room exits
    map<char*, Room*>* exits = currentRoom -> getExits();
    map<char*, Room*>::iterator it;

    //Loop through exits, name them
    for(it = exits -> begin(); it != exits -> end(); ++it) {
      cout << it -> first << " ";
    }
    cout << endl;

    //Check whether this room has items
    bool hasItems = false;

    //Get current room items
    vector<Item*>* items = currentRoom -> getItems();
    vector<Item*>::iterator itemIt = items -> begin();

    //Loop through items, name them
    while (itemIt != items -> end()) {
      if (!hasItems) {
	cout << "Items in this room: ";
	hasItems = true;
      }
      if (itemIt != items -> begin()) cout << ", ";
      cout << (*itemIt) -> getName();
      ++itemIt;
    }
    if(!hasItems) cout << "No items in this room.";
    cout << endl << endl;

    //Check if they have reached the ending room and tell them
    if(strcmp(currentRoom -> getName(), "Ending Room") == 0) {
      cout << "CONGRATULATIONS! YOU BEAT THE GAME!" << endl;
      cout << "Good job. You got to the ending room. The end." << endl;
      running = false;
      continue;
    }

    //Read in a line (command) from the user
    cin.get(command, 80);
    cin.clear();
    cin.ignore(9999, '\n');
    
    //Parse the command
    running = parse(command, &currentRoom, inventory);
  }
  return 0;
}

//Function to add room to map (for convenience)
void addRoom(map<char*, Room*>* m, char* title, char* desc) {
  (*m)[title] = new Room(title, desc);
}

//Split function to seperate char* separated by delimiter(char) into vector<char*>
vector<char*>* split(char* c, char delim) {
  //Final vector here
  vector<char*>* v = new vector<char*>;

  //Store temporary string
  char* build = new char[strlen(c)]();
  int ind = 0;

  //loop through string
  for (int i = 0; i < strlen(c); i++) {
    //If character isn't delimiter add to temporary string
    if (c[i] != delim) {
      build[ind++] = c[i];
    } else { //If it matches delimiter add it to vector and clear temporary string
      v -> push_back(build);
      build = new char[strlen(c)]();
      ind = 0;
    }
  }
  //If anything is in temporary string push to vector
  if (build) v -> push_back(build);
  return v;
}

//Function that calls other game functions
bool parse(char* c, Room** currentRoom, vector<Item*>* inventory) {
  //Split input by spaces
  vector<char*>* commands = split(c, ' ');
  //Capitalize all words
  for(int i = 0; i < commands -> size(); i++) {
    for(int j = 0; j < strlen(commands -> at(i)); j++) {
      commands -> at(i)[j] = toupper(commands -> at(i)[j]);
    }
  }
  //Main command is first word
  char* command = commands -> at(0);
  //Call functions by first command
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

//Help print function (prints commands)
void printHelp() {
  cout << "Commands: " << endl;
  cout << "\"Go\" + (direction): Take an exit in a specific direction (If it exists)" << endl;
  cout << "\"Drop\" + (item): Drop item from your inventory (If it is in there) " << endl;
  cout << "\"Get\" + (item): Get item from the room (If it exists)" << endl;
  cout << "\"Quit\": Quit the game" << endl;
  cout << "\"Inventory\"/\"Items\": Print items in your inventory" << endl;
}

//Function to take a certain exit
void goExit(vector<char*>* c, Room** currentRoom, vector<Item*>* inventory) {
  //If only one element in vector don't know where they want to go
  if (c -> size() < 2) {
    cout << "Where go?" << endl;
    return;
  }

  //Get exits of currentRoom
  map<char*, Room*>* exits = (*currentRoom) -> getExits();

  //Loop through each exit and check if it matches user exit
  char* direction = c -> at(1);
  map<char*, Room*>::iterator it;
  for(it = exits -> begin(); it != exits -> end(); ++it) {
    if (strcmp(it -> first, direction) == 0) {
      //Check if room is locked
      if ((*currentRoom)->getLocked(it->first) != 0) {
	//If locked, get the lock value
	int lockVal = (*currentRoom)->getLocked(it->first);
	vector<Item*>::iterator iit = inventory -> begin();
	//Iterate through the player inventory to see if item matches with lock value
	while(iit != inventory -> end()) {
	  if (lockVal == (*iit) -> getKeyVal()) {
	    //If they do have a key, ask if they want to unlock, and do so if they do
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
	    //If they do, unlock, move rooms, and remove the key
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

      //If it isn't locked just move rooms
      (*currentRoom) = it -> second;
      return;
    }
  }

  //If it gets here it doesn't match an exit, so it doesn't exist
  cout << "Could not find that exit" << endl;
}

//Get Item function (gets an item from a room)
void getItem(vector<char*>* commands, Room** currentRoom, vector<Item*>* inventory) {
  //If there is no second command then we don't know what to get
  if (commands -> size() < 2) {
    cout << "Get what?" << endl;
    return;
  }

  //Get the items in the current room
  vector<Item*>* roomItems = (*currentRoom) -> getItems();

  //Loop though items in the room to see if one matches user input
  vector<Item*>::iterator it = roomItems -> begin();
  while (it != roomItems -> end()) {
    char* modItem = new char();
    strcpy(modItem, (*it)->getName());
    for (int i = 0; i < strlen(modItem); i++) {
      modItem[i] = toupper(modItem[i]);
    }
    if (strcmp(commands->at(1), modItem) == 0) {
      //Add to inventory
      cout << (*it) -> getName() << " has been added to your inventory." << endl;
      inventory -> push_back(*it);
      //Unless it is water in the water fountain, remove the item from the room
      if (strcmp((*currentRoom)->getName(), "Water Fountain") != 0 || strcmp(modItem, "WATER") != 0) (*currentRoom)->removeItem(*it);
      return;
    }
    ++it;
  }

  //If gets here, no item matched, so its not in the room
  cout << "Item not found. " << endl;
}

//Drop Item function (drop an item into the room)
void dropItem(vector<char*>* commands, Room** currentRoom, vector<Item*>* inventory) {
  //If no second command we don't know what to drop
  if (commands -> size() < 2) {
    cout << "Drop What?" << endl;
    return;
  }

  //Loop through player inventory and check to see if it matches user input
  vector<Item*>::iterator it = inventory -> begin();
  while (it != inventory -> end()) {
    char* modItem = new char();
    strcpy(modItem, (*it)->getName());
    for (int i = 0; i < strlen(modItem); i++) {
      modItem[i] = toupper(modItem[i]);
    }
    //Once it matches, add to room inventory
    if (strcmp(modItem, commands -> at(1)) == 0) {
      (*currentRoom)->addItem(*it);
      //Special Case: Water fountain and wrench, fix water fountain (add water)
      if (strcmp((*currentRoom)->getName(), "Water Fountain") == 0 && strcmp(modItem, "WRENCH") == 0 && ((*currentRoom)->getDescription())[0] != 'A') {
	cout << "Congratulations! You fixed the water fountain!" << endl;
	cout << "Not sure why dropping a wrench fixes the fountain though..." << endl;
	(*currentRoom) -> setDescription("A water fountain sprays water everywhere...");
	(*currentRoom) -> addItem(new Item("Water"));
      }
      //Special Case: Water and tree, tree grows, banana is added
      if(strcmp(modItem, "WATER") == 0 && strcmp((*currentRoom)->getName(), "A Tree") == 0 && (*currentRoom)->getLocked("UP") != 0) {
	cout << "The tree grows. You can climb it now." << endl;
	cout << "Also apparently it grew a banana. Nice." << endl;
	(*currentRoom) -> toggleLock("UP", 0);
	(*currentRoom) -> addItem(new Item("Banana"));
	(*currentRoom) -> setDescription("A large tree that you can climb.");
      }
      //Special Case: Water, water doesn't go into room, instead dissappears.
      if (strcmp(modItem, "WATER") == 0) {
	cout << "The water splashes into the ground. It's gone." << endl;
	(*currentRoom) -> removeItem(*it);
      }
      //Special Case: Monkey and banana, Monkey gives player the flower
      if (strcmp(modItem, "BANANA") == 0 && strcmp((*currentRoom) -> getName(), "Monkey") == 0 && (*currentRoom) -> getDescription()[0] == 'H') {
	cout << "The monkey takes the banana, and hands you the flower" << endl;
	(*currentRoom) -> setDescription("A happy monkey with a banana.");
	(*currentRoom) -> removeItem(*it);
	inventory -> push_back(new Item("Flower", 3));
      }

      //Remove item from player inventory
      cout << "You dropped " << (*it)->getName() << endl;
      inventory -> erase(it);
      return;
    }
    ++it;
  }

  //If gets here, no item matched with user input, so its not in the inventory
  cout << "Could not find item." << endl;
}

//Function prints items in inventory
void printInv(vector<Item*>* inventory) {
  vector<Item*>::iterator it = inventory -> begin();
  bool hasItems = false;
  //loop through items in the inventory
  while (it != inventory -> end()) {
    if (!hasItems) {
      cout << "You have: ";
      hasItems = true;
    }
    //If it isn't the first item add a comma to separate items
    if (it != inventory -> begin()) cout << ", ";
    cout << (*it)->getName();
    ++it;
  }
  //If they don't have items tell them.
  if(!hasItems) cout << "You have no items :(";
  cout << endl;
}
