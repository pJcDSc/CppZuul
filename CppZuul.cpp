#include <iostream>
#include <cstring>
#include <map>
#include <vector>
#include "Room.h"
#include "Item.h"
using namespace std;

vector<char*>* split(char*, char);
bool parse(char*);
bool printHelp();

int main() {  
  
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
  if (strcmp(command, "HELP")) {
    printHelp();
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
