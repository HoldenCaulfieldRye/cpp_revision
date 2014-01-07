#include<iostream>
#include<cctype>
#include<cstring>
#include<fstream>

using namespace std;

#include"braille.h"

int encode_character(char ch, char* braille) {
  //lower case letter
  if (isalpha(ch)) {

    int ret=6;

    if (isupper(ch)) {
      strcpy(braille,".....0");
      ch = tolower(ch);
      ret+=6;
    }

    switch(ch) { 
    case 'a':
      strcat(braille, "0....."); return ret;
    case 'b':
      strcat(braille, "00...."); return ret;
    case 'c':
      strcat(braille, "0..0.."); return ret;
    case 'd':
      strcat(braille, "0..00."); return ret;
    case 'e':
      strcat(braille, "0...0."); return ret;
    case 'f':
      strcat(braille, "00.0.."); return ret;
    case 'g':
      strcat(braille, "00.00."); return ret;
    case 'h':
      strcat(braille, "00..0."); return ret;
    case 'i':
      strcat(braille, ".0.0.."); return ret;
    case 'j':
      strcat(braille, ".0.00."); return ret;
    case 'k':
      strcat(braille, "0.0..."); return ret;
    case 'l':
      strcat(braille, "000..."); return ret;
    case 'm':
      strcat(braille, "0.00.."); return ret;
    case 'n':
      strcat(braille, "0.000."); return ret;
    case 'o':
      strcat(braille, "0.0.0."); return ret;
    case 'p':
      strcat(braille, "0000.."); return ret;
    case 'q':
      strcat(braille, "00000."); return ret;
    case 'r':
      strcat(braille, "000.0."); return ret;
    case 's':
      strcat(braille, ".000.."); return ret;
    case 't':
      strcat(braille, ".0000."); return ret;
    case 'u':
      strcat(braille, "0.0..0"); return ret;
    case 'v':
      strcat(braille, "000..0"); return ret;
    case 'w':
      strcat(braille, ".0.000"); return ret;
    case 'x':
      strcat(braille, "0.00.0"); return ret;
    case 'y':
      strcat(braille, "0.0000"); return ret;
    case 'z':
      strcat(braille, "0.0.00"); return ret;
    }
  }

  //number
  if (isdigit(ch)) {
    switch(ch) { 
    case '1':
      strcpy(braille,"..00000....."); return 12;
    case '2':
      strcpy(braille,"..000000...."); return 12;
    case '3':
      strcpy(braille,"..00000..0.."); return 12;
    case '4':
      strcpy(braille,"..00000..00."); return 12;
    case '5':
      strcpy(braille,"..00000...0."); return 12;
    case '6':
      strcpy(braille,"..000000.0.."); return 12;
    case '7':
      strcpy(braille,"..000000.00."); return 12;
    case '8':
      strcpy(braille,"..000000..0."); return 12;
    case '9':
      strcpy(braille,"..0000.0.0.."); return 12;
    case '0':
      strcpy(braille,"..0000.0.00."); return 12;
    }
  }

  //punctuation
  if (ispunct(ch)) {
    switch(ch) {
    case '.':
      strcpy(braille,".0..00"); return 6;
    case ',':
      strcpy(braille,".0...."); return 6;
    case ';':
      strcpy(braille,".00..."); return 6;
    case '-':
      strcpy(braille,"..0..0"); return 6;
    case '!':
      strcpy(braille,".00.0."); return 6;
    case '?':
      strcpy(braille,".00..0"); return 6;
    case '(':
      strcpy(braille,".00.00"); return 6;
    case ')':
      strcpy(braille,".00.00"); return 6;
    }
  }

  return -1;
}


void encode(const char* str, char* braille) {
  if (str[0]=='\0')
    return;          //braille[0] = '\0' first?

  else {
    int length = encode_character(str[0], braille);
    return encode(&str[1], &braille[length]);       //length+1? length-1?
  }
}


void print_braille(const char* str, ostream& out) {
  char braille[100], matrix[4][600];
  char *mat = &matrix[0][0];
  char **m = &mat;

  //create encoded text
  encode(str, braille);

  //write out braille in appropriate format in matrix, encoded char by encoded char
  matrify(str, braille, mat, m);

  //print matrix to out
  for (int row=0; row<4; row++) {
    for (int col=0; matrix[0][col]!='\0'; col++)
      out << matrix[row][col];
  }

  return;
}


void matrify(const char* str,  char* braille, char* mat, char** m) {
  int count=0, col=0;

  if (str[0]=='\0') {
    m[0][0] = '\0';   //sentinel character to mark last column
    return;  
  }

  if (isupper(str[0])) {

    cerr << "isupper true" << endl;

    for (col=0; col<6; col++) {
      for (int row=0; row<3; row++) {

	cerr << endl << "m[" << row << "][" << col << "] = " << braille[count] << endl;

	m[row][col] = braille[count];
	count++;
      }
    }

    cerr << endl << "m[3][" << col << "] = " << str[0] << endl;

    m[3][col] = str[0];
    mat = &m[0][6];
    m = &mat;
    return matrify(&str[1], &braille[12], mat, m); //is  &m[][k] going to work?
  }

  else {

    cerr << "isupper false" << endl;

    for (col=0; col<3; col++) {
      for (int row=0; row<3; row++) {

	cerr << endl << "m[" << row << "][" << col << "] = " << braille[count] << endl;

	m[row][col] = braille[count];
	count++;
      }
    }

    cerr << endl << "m[0][" << col << "] = " << str[0] << endl;

    m[0][col] = str[0];
    mat = &m[0][3];
    m = &mat;

    return matrify(&str[1], &braille[6], mat, m);      
  }
}
