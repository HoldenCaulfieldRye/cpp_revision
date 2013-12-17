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
  
  //cerr << "encoding " << ch << " as " << multitap << endl; 

  int i;
  for (i=1; i<500 && multitap[i] == multitap[i-1]; i++);
  return i;
}


int check_hash(char ch, char* interim, bool& hash) {
  char temp[4];
  interim[0] = temp[0] = '\0';
  int length = 0;

  // if (hash)
  //   cerr << "hash is true" << endl;

  if ((hash==false && isupper(ch)) || (hash==true && !isupper(ch))) {
    //    cerr << "need #!" << endl;
    strcat(interim, "#");
    length++;
    hash = !hash;
  }
  // cerr << "ch = " << ch << endl;
  ch = tolower(ch);
  // cerr << "and now ch = " << ch << endl;
  length = encode_character(ch, temp);
  // cerr << "(check_hash) interim should be roughly empty: " << interim << " and temp should contain encoding for " << ch << ": " << temp << endl;
  strcat(interim, temp);

  // cerr << "(check_hash) after strcat(interim, temp), temp: " << temp << " and interim: " << interim << endl;

  return length;
}


void encode(const char* plaintext, char* multitap) {
  bool hash = false;
  char ch;
  char interim[2][5];
  multitap[0] = interim[0][0] = interim[1][0] = '\0';

  int length, templength;

  // cerr << "encoding '" << plaintext << "' into multitap which should be empty: " << multitap << endl;

  /*first step: encode first character*/
  length = check_hash(plaintext[0], interim[0], hash);

  if (length == -1) {
    cerr << "invalid input:"
  //   cerr << "strcat-ing " << interim[0] << " to " << multitap << endl;
  strcat(multitap, interim[0]);
  // cerr << "multitap is now: " << multitap << endl;
  ch=plaintext[1];

  /*inductive step: while there is another character to encode, encode it by checking for whether '|' is needed by comparing its multitap encoding with that of previous character*/
  for (int i=1; plaintext[i]!='\0'; i++, ch=plaintext[i]) {

    /*get encoding for current character, and take its length - useful if there is another loop after this one*/
    templength = check_hash(ch, interim[1], hash);

    /*compare first multitap key of encoding for current character with last multitap key of encoding for previous character. if same, append '|' to multitap*/
    if (interim[0][length] == interim[1][0] || interim[0][length-1] == interim[1][0]) {
      // cerr << "did I get length-1 right? " << interim[1][0] << " and " << interim[0][length-1] << endl;
      //  cerr << "strcat-ing '|' to " << multitap << endl;
      strcat(multitap, "|");
      // cerr << "multitap is now: " << multitap << endl;
    }

    /*append encoding for current character*/
    //   cerr << "strcat-ing " << interim[1] << " to " << multitap << endl;
    strcat(multitap, interim[1]);
    // cerr << "multitap now looks like " << multitap << endl << endl;

    /*update interim[0] and length in case there is a next loop*/
    strcpy(interim[0], interim[1]);
    length = templength;
  }

  /*multitap is complete, just needs a sentinel character*/
  strcat(multitap, "'\0'");
}



bool isupper(char ch) {
  if (isalpha(ch) && !islower(ch))
    return true;
  return false;
}
