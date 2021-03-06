#include<iostream>
#include<fstream>
#include<cctype>
#include<cstring>

using namespace std;

#include"piglatin.h"


int findFirstVowel(const char* word) {
  char letter;

  for(int i=0; word[i]!='\0'; i++) {

    letter = tolower(word[i]);  //any other 'preprocessing'?

    switch(letter) {
    case'y':
      if (i==0 || word[i+1]=='\0')  //will this work as planned?
	break;
    case'a':
    case'e':
    case'i':
    case'o':
    case'u':
      return i;  
    // default:     do I need this?
    //   break;
    }
  }
  return -1;
}


void translateWord(const char* word, char* translated) {
  int index;
  char temp[20], word2[50];
  bool capital=false;

  //handle potential capital letter or digit at beg
  strcpy(word2, word);

  if(isdigit(word[2])) {
    strcpy(translated, word2);
    return;
  }

  word2[0] = tolower(word[0]);

  if(word2[0] != word[0])
    capital = true;

  //cerr << "word2 should have no capital letters: " << word2 << endl;

  //1st letter
  index = findFirstVowel(word2);

  if(index==0) {
    strcpy(translated, word2);
    strcat(translated, "way");  //MUST REMAIN AT END OF WORD2 so use strcat afterwards
  }

  else if (index==-1) {
    strcpy(translated, word2);
    return;
  }

  else {
    strcpy(temp, word2);
    temp[index] = '\0';  //should copy word2 until index-th char!

    //cerr << "temp: " << temp << endl;

    strcpy(translated, &word2[index]);
    strcat(translated, temp);  //should append temp to end of word2!

    //cerr << "should append " << temp << " to end of translated: " << translated << endl;

    strcat(translated, "ay");
  }

  if (capital)
    translated[0] = toupper(translated[0]);

  return;
}


void translateStream(istream& input, ostream& output) {
  char word[64], translated[64], last='\0';
  int end;
  bool punct = false;

  input.getline(word, 64, ' ');

  if (input.fail())
    return;

  else {

    //does word contain punctuation at end?
    for(end=0; word[end]!='\0'; end++);

    //cerr << endl << "checking whether " << word[end-1] << " is punct" << endl;

    if (ispunct(word[end-1])) {
      punct = true;
      last = word[end-1];
      word[end-1]='\0';
    }

    //cerr << "\t(translateStream) about to translate word: " << word << endl;

    translateWord(word, translated);

    if (punct) {
      for(end=0; translated[end]!='\0'; end++);
      translated[end] = last;
      translated[end+1] = '\0';
    }

    //   cerr << endl << "\ttranslation of " << word << " is " << translated << endl;

    output << translated << ' ';
    translateStream(input, output);
    return;
  }
}



