#include<iostream>

using namespace std;

int main() {

  char plaintext[100], multitap[500];

  plaintext = "hello";

  multitap = encode(plaintext, multitap);
  cout << "'" << plaintext << "' in multitap format is " << multitap << endl;

  plaintext = "hello everyone how are we today?";
  multitap = encode(plaintext, multitap);
  cout << "'" << plaintext << "' in multitap format is " << multitap << endl;

  plaintext = "I am 22 years old.";
  multitap = encode(plaintext, multitap);
  cout << "'" << plaintext << "' in multitap format is " << multitap << endl;

  plaintext = "It'll take you, like, 20 minutes only! Seriously?";
  multitap = encode(plaintext, multitap);
  cout << "'" << plaintext << "' in multitap format is " << multitap << endl;
}
