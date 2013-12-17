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
  char* interim[2];
  multitap[0] = interim[0][0] = interim[1][0] = '\0';
  int length[2];
  // int count = 0, j=0;
  // encodethat(plaintext, multitap, 0, 100);

  cerr << "encoding '" << plaintext << "' into multitap which should be empty: " << multitap << endl;

  length[0] = check_hash(plaintext[0], interim[0], hash);
  strcat(multitap, interim[0]);
  ch=plaintext[1];

  for (int i=1; plaintext[/**/]!='\0'; i++, ch=plaintext[i]) {

    length[1] = check_hash(ch, interim[1], hash);

    if (interim[0][length-1] == interim[1][0]) {
      cerr << "did I get length-1 right? " << interim[0] << " and " << interim[0][length-1] << endl;
      strcat(multitap, "|");
    }

    strcat(multitap, interim[1]);

    strcpy(interim[0], interim[1]);
    length[0] = length[1];
  }
  /*last char to encode needs no '|'*/
  encode_character(ch, interim);
  strcat(multitap, interim);
  strcat(multitap, "'\0'");

}

void check_hash(char ch, char* interim, bool& hash) {
  char* temp;

  temp[0] = interim[0] = '\0';
  encode_character(ch, temp);

  if ( (hash==false && isupper(ch)) || (hash==true && !isupper(ch)) ) {
      interim[0] = '#';
      hash = !hash;
  }

  strcat(interim, temp);
  // cerr << "strcat-ing '|' to " << multitap << endl;
  // cerr << "multitap now looks like " << multitap << endl << endl;
}


bool isupper(char ch) {
  if (isalpha(ch) && !islower(ch))
    return true;
  return false;
}
