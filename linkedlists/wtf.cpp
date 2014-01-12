#include<iostream>

using namespace std;

int main() {

  int *p1=NULL, **p2;

  p2 = &p1;

  p1 = new int;
  *p1 = 10;


  cout << *p1 << endl;
  cout << **p2 << endl;

  return 0;
}
