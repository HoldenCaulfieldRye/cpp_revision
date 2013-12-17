#include<fstream>
#include<cctype>
#include<iostream>
#include<cstring>

using namespace std;

#include"multitap.h"

int encode_character(char ch, char* multitap) {
  ifstream file;

  file.open("multitap.txt");
  if (file.fail()) {
    cerr << "could not open file" << endl;
    return -1;
  }

  while(multitap[0] != ch)
    file.getline(multitap, 500);//this works
  file.getline(multitap, 500);

  if (file.eof()) {
    cerr << ch << " cannot be multitapped" << endl;
    return -1;
  }
  
  int i;
  for (i=1; i<500 && multitap[i] == multitap[i-1]; i++);
  return i;

  //  getline(file, multitap); //doesn't work
  //  file.getline(line);      //doesn't work
  //  file.getline(multitap);  //doesn't work
  //  cin.getline(multitap);   //doesn't work
}


void encode(const char* plaintext, char* multitap) {
  bool hash = false;
  char ch;
  char* interim;
  multitap[0] = interim[0] = '\0';
  // int length;
// int count = 0, j=0;

  // encodethat(plaintext, multitap, 0, 100);

  cerr << "encoding '" << plaintext << "' into multitap which should be empty: " << multitap << endl;

  for (int i=0; plaintext[i+1]!='\0'; i++, ch=plaintext[i]) {

    encode_character(ch, interim);

    if (ch==' ' || islower(ch) || isdigit(ch)) {
      cerr << "encoding " << ch << " as " << interim << endl;
      cerr << "strcat-ing it to " << multitap << endl;

      if(hash==true) {
	strcat(multitap, "#");
	hash = false;
      }
    }

    else if (isalpha(ch) && hash==false) { //capital letter
	strcat(multitap, "#");
	hash = true;
    }

      strcat(multitap, interim);
    cerr << "strcat-ing '|' to " << multitap << endl;

    strcat(multitap, "|");

    cerr << "multitap now looks like " << multitap << endl << endl;
  }
  /*last char to encode needs no '|'*/
    encode_character(ch, interim);
    strcat(multitap, interim);
    strcat(multitap, "'\0'");

}

void encodethat(char* plaintext, char* multitap, int beg, int end) {
  // char ch;

  // if (encode_character(ch, multitap) != -1) {

  //   encodethat(plaintext, multitap, i, end);
  // }


}
