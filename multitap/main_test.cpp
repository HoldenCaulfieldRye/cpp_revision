#include<iostream>

using namespace std;

#include"multitap.h"

int main() {

  //  char plaintext[100];
  char multitap[500];
  cout << "an empty static char array's contents look like this: ";
  for (int i=0; i<6; i++)
    cout << multitap[i] << ", ";
  cout << endl << "and like this: ";
  for (int i=0; i<6; i++)
    cout << (int) multitap[i] << ", ";
  cout << endl;

  encode_character('c', multitap);

  cout << multitap << endl;

  return 0;
}
