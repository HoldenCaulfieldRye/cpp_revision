#include<iostream>

using namespace std;

#include"multitap.h"

int main() {

  //  char plaintext[100];
  char multitap[500];
  // char ch;


  //====== QUESTION 1 ===============================================

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


  //====== QUESTION 2 ===============================================

  strcpy(plaintext, "hello there");
  multitap = encode(plaintext, multitap);
  cout << "'" << plaintext << "' in multitap format is " << multitap << endl;

  // strcpy(plaintext, "Hello Everyone How Are We Today?");
  // plaintext = "Hello Everyone How Are We Today?";
  // multitap = encode(plaintext, multitap);
  // cout << "'" << plaintext << "' in multitap format is " << multitap << endl;

  // strcpy(plaintext, "I am 22 Years Old.");
  // plaintext = "I am 22 Years Old.";
  // multitap = encode(plaintext, multitap);
  // cout << "'" << plaintext << "' in multitap format is " << multitap << endl;

  // strcpy(plaintext, "It'll take you, like, 20 minutes only! Seriously?");
  // plaintext = "It'll take you, like, 20 minutes only! Seriously?";
  // multitap = encode(plaintext, multitap);
  // cout << "'" << plaintext << "' in multitap format is " << multitap << endl;

  return 0;
}
