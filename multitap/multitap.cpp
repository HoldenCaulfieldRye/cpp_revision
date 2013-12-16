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
    file.getline(multitap, 500);  //this works

  file.getline(multitap, 500);

  if (file.eof()) {
    cerr << ch << " cannot be multitapped" << endl;
    return -1;
  }
  
  cerr << "looking at: ";
  for (int i=0; i<7; i++)
    cerr << multitap[i] << " ";
  cerr << endl;


  //  getline(file, multitap); //doesn't work
  //  file.getline(line);      //doesn't work
  //  file.getline(multitap);  //doesn't work
  //  cin.getline(multitap);   //doesn't work

  return 0;
}


void encode(char plaintext[100], char multitap[500]) {

}
