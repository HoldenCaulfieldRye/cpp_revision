#include<iostream>
#include<cstring>

using namespace std;

int substring_position_other(const char* substring, const char* target) {
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


bool isbeg(char const* substring, char const* target) {
  if (substring[0]=='\0')
    return true;

  if (target[0]=='\0')
    return false;

  if (substring[0]=target[0])
    return isbeg(&substring[1], &target[1]);

  return false;
}


int match(char const* substring, char const* target, int length) {
  int otherlength, ret;
  for (otherlength=1; target[otherlength]!='\0'; otherlength++);

  //  cerr << "substring: " << substring << ", target: " << target << ", length: " << length << endl;

  if (otherlength<length)
    return -1;

  if (substring[0] == '\0' || isbeg(substring, target))
    return 0;

  ret = match(substring, &target[1], length);
  if (ret==-1)
    return -1;
  else return 1 + ret;
}


int substring_position(char const* substring, char const* target) {
  int length;

  for(length=1; substring[length]!='\0'; length++);

  return match(substring, target, length);
}
