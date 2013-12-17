#include<iostream>
#include<cstring>

using namespace std;

#include"multitap.h"

int main() {

  char multitap[500];
  // char ch;


  cout << "====== QUESTION 1 ===============================================" << endl << endl;

  encode_character('a', multitap);
  cout << "'a' is encoded as " << multitap << endl;

  encode_character('r', multitap);
  cout << "'r' is encoded as " << multitap << endl;

  encode_character('6', multitap);
  cout << "'6' is encoded as " << multitap << endl;

  encode_character('0', multitap);
  cout << "'0' is encoded as " << multitap << endl;

  encode_character('?', multitap);
  cout << "'?' is encoded as " << multitap << endl;

  encode_character(',', multitap);
  cout << "',' is encoded as " << multitap << endl;


  cout << endl << "====== QUESTION 2 ===============================================" << endl << endl;

  encode("hello there", multitap);
  cout << "'hello there' in multitap format is " << multitap << endl;

  // encode(plaintext, multitap);
  // cout << "'Hello Everyone How Are We Today?' in multitap format is " << multitap << endl;

  // encode("I am 22 Years Old.", multitap);
  // cout << "'I am 22 Years Old.' in multitap format is " << multitap << endl;

  // encode("It'll take you, like, 20 minutes only! Seriously?", multitap);
  // cout << "'It'll take you, like, 20 minutes only! Seriously?' in multitap format is " << multitap << endl;

  return 0;
}
