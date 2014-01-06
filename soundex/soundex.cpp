#include<iostream>
#include<cctype>
#include<cstring>

using namespace std;

#include"soundex.h"


void encode(const char* surname, char* soundex) {
  int i,j;

  soundex[0] = toupper(surname[0]);

  for(i=j=1; j<4 && surname[i]!='\0'; i++) {

    soundex[j] = encode_char(surname[i]);

    if (soundex[j]!='0' && encode_char(surname[i]) != encode_char(surname[i-1])) 
      j++;
  }

  if (j<4) {
    for(; j<4; j++)
      soundex[j] = '0';
  }

  soundex[4] = '\0';

  return;
}


char encode_char(char ch) {
    switch(ch) {
    case 'b':
    case 'f':
    case 'p':
    case 'v':
      return '1';

    case 'c':
    case 'g':
    case 'j':
    case 'k':
    case 'q':
    case 's':
    case 'x':
    case 'z':
      return '2';

    case 'd':
    case 't':
      return '3';

    case 'l':
      return '4';

    case 'm':
    case 'n':
      return '5';

    case 'r':
      return '6';

    default:
      return '0';
    }
}

int compare(const char* soundx, const char* soundex) {
  if (soundx[0]=='\0') //assume only valid soundex codes will be given as args
    return 1;

  if (soundx[0] != soundex[0])
    return 0;

  return compare(&soundx[1], &soundex[1]); //reach here only if both chars are same
}


int count(const char* str, const char* string) {
  char target[100], *tok, soundx[5], soundex[5];
  int amount=0;

  strcpy(target, string);
  encode(str, soundx);

  for (tok=strtok(target, ", ."); tok!=NULL; tok=strtok(NULL, ", .")) {

    encode(tok, soundex);

  // cerr << "considering token: " << tok << endl;
  // cerr << "considering soundex's: " << soundx << " and " << soundex << "... strcmp: " << strcmp(soundx, soundex) << endl;

    if (strcmp(soundx, soundex)==0)
      amount++;
  }

  // strcpy(stringcpy, string);
  // // for(stringgetline(string,30,' '); !target.fail(); target=getline(string,30,' ')) {
  
  // stringcpy.get(target,30,' ');
  // cerr << "considering target: " << target << endl;

  // //   if (strcmp(str, target)==0)
  // amount++;
  // // }

  return amount;
}
