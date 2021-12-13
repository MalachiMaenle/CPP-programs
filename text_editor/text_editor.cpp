#include <iostream>
#include "util.h"

using namespace std;

int main() {
  cout << bg_black white << endl;
  wait(1);
  system("clear");

  getKey.startInput();
  while(true) {
    getKey.input();
    if(getKey.key == 65 || getKey.key == 66 || getKey.key == 67 || getKey.key == 68 || getKey.key == 127 || getKey.key == '1') {
      if(getKey.key == '1') {
        main();
        exit(42);
      }
      if(getKey.key == 65) {
        cout << cursor_up;
      }
      if(getKey.key == 66) {
        cout << cursor_down;
      }
      else if(getKey.key == 67) {
        cout << cursor_right;
      }
      else if(getKey.key == 68) {
        cout << cursor_left;
      }
      if(getKey.key == 127) {
        cout << backspace;
      }
    } else {
      cout << getKey.key;
    }
  }

  return 0;
}