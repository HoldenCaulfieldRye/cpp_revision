#include<iostream>
#include<cstring>
#include<cctype>

using namespace std;

/* You are supplied with two helper functions */

/* converts a character into a binary string representation */
void ascii_to_binary(char ch, char *binary);

/* converts a binary string representation into a character */
char binary_to_ascii(char *binary);

void ascii_to_binary(char ch, char *binary) {
  for (int n = 128; n; n >>= 1) 
    *binary++ = (ch & n) ? '1' : '0';
  *binary = '\0';
}

char binary_to_ascii(char *binary) {
  int ch = 0;
  for (int n=0, slide=128; n<8; n++, slide >>= 1) {
    if (binary[n] == '1')
      ch = ch | slide;
  }
  return ch;
}

/* now add your own functions here */


void text_to_binary(const char* str, char* binary) {
  if (str[0]=='\0')
    return;

  ascii_to_binary(str[0], binary);
  text_to_binary(&str[1], &binary[8]);
}


void binary_to_text(const char* binary, char* str) {
  if (binary[0]=='\0') {
    str[0] = '\0';
    return;
  }

  char temp[512];
  strcpy(temp, binary);
  temp[8]='\0';

  str[0] = binary_to_ascii(temp);

  // //cerr << temp << " to text is " << str[0] << endl;

  binary_to_text(&binary[8], &str[1]);
}


/*insert check bits*/
void add_error_correction(const char* data, char* correct) {

  if(data[0]=='\0') {
    correct[0] = '\0';
    return;
  }

  char checkBits[3];

  checkBits[0] = ((data[0] + data[1] + data[3]) % 2) + '0';
  checkBits[1] = ((data[0] + data[2] + data[3]) % 2) + '0';
  checkBits[2] = ((data[1] + data[2] + data[3]) % 2) + '0';

  //cerr << "checkbits: " << checkBits //add sentinel for this!

  correct[0] = checkBits[0];
  correct[1] = checkBits[1]; 
  correct[2] = data[0];
  correct[3] = checkBits[2]; 
  correct[4] = data[1]; 
  correct[5] = data[2]; 
  correct[6] = data[3];

  add_error_correction(&data[4], &correct[7]);
}



int decode(const char* received, char* decoded) {

  if (received[0]=='\0') {
    decoded[0] = '\0';
    return 0;
  }

  int p[3];

  decoded[0] = received[2];
  decoded[1] = received[4];
  decoded[2] = received[5];
  decoded[3] = received[6];

  p[0] = (received[3] + received[4] + received[5] + received[6]) % 2;
  p[1] = (received[1] + received[2] + received[5] + received[6]) % 2;
  p[2] = (received[0] + received[2] + received[4] + received[6]) % 2;

  //cerr << "parities: " << p[0] << p[1] << p[2] << endl;

  if (p[0] + p[1] + p[2] == 0)  {//ie p[0]==p[1]==p[2]==0 
    //cerr << "no error" << endl;
    return decode(&received[7], &decoded[4]);
  }

  int errorPos = p[0]*4 + p[1]*2 + p[2] - 1; //reach here iif a bit error exists

  //cerr << "there is an error at position " << errorPos << endl;
   //cerr << "entry no " << errorPos << " was " << (char) received[errorPos] << endl;

  /*only really need to flip bit if data*/
   switch(errorPos) {
   case 2:
     decoded[0] = ((decoded[0] + 1) % 2) + '0'; 
     //cerr << "it is now " << (char) decoded[0] << endl;
     break;
   case 4:
     decoded[1] = ((decoded[1] + 1) % 2) + '0';
     //cerr << "it is now " << (char) decoded[1] << endl; 
     break;
   case 5:
     decoded[2] = ((decoded[2] + 1) % 2) + '0';
     //cerr << "it is now " << (char) decoded[2] << endl; 
     break;
   case 6:
     decoded[3] = ((decoded[3] + 1) % 2) + '0';
     //cerr << "it is now " << (char) decoded[3] << endl; 
     break;
   }

  return 1 + decode(&received[7], &decoded[4]);
}


