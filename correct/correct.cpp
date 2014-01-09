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
  binary_to_text(&binary[8], &str[1]);
}


/*insert check bits*/
void add_error_correction(const char* data, char* corrected) {
  int checkBit[3];
  // numdata[512];

  // for(int i=0; data[i]!='\0'; i++) {
  //   if (data[i]=='0')
  // 	 numdata[i] = 0;
  //   else numdata[i] = 1;
  // }

  //  cerr << "numdata[0] + numdata[1] + numdata[3] = " << numdata[0] + numdata[1] + numdata[3] << endl;

  checkBit[0] = (isdigit(data[0]) + isdigit(data[1]) + isdigit(data[3])) % 2;
  checkBit[1] = (isdigit(data[0]) + isdigit(data[2]) + isdigit(data[3])) % 2;
  checkBit[2] = (isdigit(data[1]) + isdigit(data[2]) + isdigit(data[3])) % 2;

  checkBit[3]='\0';

  cerr << "checkbits:";
  for(int i=0; i<3; i++)
    cerr << checkBit[i];
  cerr << endl;

  corrected[0] = (char) checkBit[0];
  corrected[1] = (char) checkBit[1];
  corrected[2] = data[0];
  corrected[3] = (char) checkBit[2];
  corrected[4] = data[1];
  corrected[5] = data[2];
  corrected[6] = data[3];

  corrected[7] = '\0';
}



int decode(const char* received, char* decoded) {
  return -1;
}


