#include<fstream>
#include<cctype>
#include<iostream>
#include<string>

using namespace std;

int encode_character(char ch, char multitap[500]) {
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


void encode(char plaintext[100], char multitap[500]) {
  bool hash = false;
  char ch, interim[5];
  int length, count = 0;

  encodethat(plaintext, multitap, 0, 100);

  for(length = encode_character(plaintext[j], interim);
      length != -1;
      length = encode_character(plaintext[j], interim)) {

    for (int i=0; i<length; i++)
multitap[count+i] = 
  }
  for (int i=0; i<500 && ; i++)
  /*test whether character is capital letter*/
  if (!islower(plaintext[count]) && isalpha(plaintext[count])) {
    hash = true;

  }
}

encodethat(char plaintext[100], char multitap[500], int beg, int end) {
  char ch;

  if (encode_character(ch, multitap) != -1) {

    encodethat(plaintext, multitap, i, end);
  }


}
