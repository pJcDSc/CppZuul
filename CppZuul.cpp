#include <iostream>
#include <cstring>
#include <map>

using namespace std;

int main() {
  map<char*, int> names;
  names.insert({"hello", 3});
  names["hello"] = 4;
  cout << names["hello"] << endl;
  return 0;
}
