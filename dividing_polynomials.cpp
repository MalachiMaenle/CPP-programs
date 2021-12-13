#include <iostream>

using namespace std;

double a1, b1, c1, d1, a2, b2, a3, b3, c3;

void printEquation();

int main() {

  cout << "1 - A, B, C, D: ";
  cin >> a1 >> b1 >> c1 >> d1;
  cout << "2 - A, B: ";
  cin >> a2 >> b2;
  cout << endl << endl;

  printEquation();

  a3 = (a1 / a2);
  b1 = b1 - (b2 * (a1 / a2));
  a1 = a1 - a2 * (a1 / a2);

  printEquation();

  b3 = (b1 / a2);
  c1 = c1 - b2 * (b1 / a2);
  b1 = b1 - a2 * (b1 / a2);

  printEquation();

  c3 = (c1 / a2);
  d1 = d1 - b2 * (c1 / a2);
  c1 = c1 - a2 * (c1 / a2);

  printEquation();

  cout << endl << endl;

  cout << a3 << "x" << "\u00B2";
  if(b3 >= 0) {
    cout << "+";
  }
  cout << b3 << "x";
  if(c3 >= 0) {
    cout << "+";
  }
  cout << c3 << endl;
  cout << d1;

  return 0;
}

void printEquation() {
  cout << a1 << "x" << "\u00B3";
  if(b1 >= 0) {
    cout << "+";
  }
  cout << b1 << "x" << "\u00B2";
  if(c1 >= 0) {
    cout << "+";
  }
  cout << c1 << "x";
  if(d1 >= 0) {
    cout << "+";
  }
  cout << d1 << endl;
}
