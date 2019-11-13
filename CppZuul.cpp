#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "Room.h"
#include "Item.h"
using namespace std;

void addRoom(map<char*, Room*>*, char*, char*); 
vector<char*>* split(char*, char);
bool parse(char*);
bool printHelp();

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
  addRoom(m, "Red Ladder Down", "Ladder, red, yadda yadda. Also goes down.");
  
  bool running = true;
  char* command;
  while (running) {
    cin.get(command, 80);
    cin.clear();
    cin.ignore(9999, '\n');

    running = parse(command);
  }
  return 0;
}

void addRoom(map<char*, Room*>* m, char* title, char* desc*) {
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

bool parse(char* c) {
  vector<char*>* commands = split(c, ' ');
  for(int i = 0; i < commands -> size(); i++) {
    for(int j = 0; j < strlen(commands -> at(i)); j++) {
      commands -> at(i) = toupper(commands -> at(i));
    }
  }
  char* command = commands -> at(0);
  if (strcmp(command, "HELP") == 0) {
    printHelp();
  } else if (strcmp(command, "GO")) {
    goExit(commands);
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
