#include <iostream>
#include <cstring>
#include <map>
#include "Room.h"
#include "Item.h"
using namespace std;

int main() {
  char* a[50][5] = {"hello", "goodbye", "i love you", "fuck" };
  cout << (*a)[1] << endl;
  return 0;
}
