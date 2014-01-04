#include<iostream>
#include<cstring>

using namespace std;

int substring_position(const char* substring, const char* target) {
  char *pt, string[100];
  int length;
  strcpy(string, target);

  for(length=0; substring[length]!='\0'; length++);

  //  cerr << "length is " << length << endl;

  if(substring[0]=='\0' && string[0]=='\0')
    return 0;

  for(int i=0; string[i]!='\0'; i++) {
    pt = &string[i];

    //    cerr << "about to compare '" << substring << "' with '" << pt << "'" << endl;

    if (strncmp(substring, pt, length)==0)
      return i;
  }

  return -1;
}


