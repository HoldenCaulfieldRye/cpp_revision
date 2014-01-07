#include<iostream>
#include<cctype>
#include<cstring>

using namespace std;

#include"words.h"


void reverse(const char* str1, char* str2) {

  int length=0;
  for (; str1[length+1] != '\0'; length++);

  //  cerr << "length: " << length << endl;

  for (int i=length, j=0; i>=0; i--, j++)
    str2[j] = str1[i];

  str2[length+1] = '\0';
}


int compare(const char* str1, const char* str2) {

  //  cerr << endl;

  //  cerr << "considering str1, str2:" << endl << str1 << endl << str2 << endl;

  if (different_letters(str1[0], str2[0])) {

    if (ignorable(str1[0]) && ignorable(str2[0]))
      return compare(&str1[1], &str2[1]);

    if (ignorable(str1[0]))               //maybe also need case when both are ignorable?
      return compare(&str1[1], str2);

    else if (ignorable(str2[0]))          //maybe ignorable doesn't discriminate properly?
      return compare(str1, &str2[1]);

    else {
      // cerr << "str1[0], str2[0]:" << str1[0] << " " << str2[0] << endl;
      return 0;
    }
  }

  if (str1[0] == '\0') //reach here only if both chars are the same letter (?)
    return 1;

  return compare(&str1[1], &str2[1]);
}


bool different_letters(char ch1, char ch2) {
  if (ch1 != ch2 && toupper(ch1) != ch2 && toupper(ch2) != ch1)
    return true;
  return false; //note that false will be returned if they are identical punctuations chars
}


bool ignorable(char ch) {
  if (!isalpha(ch) && ch!='\0')
    return true;
  return false;
}


int palindrome(const char* str1) {
  char str2[100];
  reverse(str1, str2);
  return compare(str1, str2);
}

/*for each non-ignorable character in str1, look for it in str2 and remove it from str2. this fails at any point iif str1 and str2 are not anagrams. */
int anagram(const char* str1, const char* str2) {

  //  cerr << endl << endl << "str1, str2:" << endl << str1 << endl << str2 << endl;

  if (str1[0]=='\0')
    return 1;

  if (ignorable(str1[0]))
    return anagram(&str1[1], str2);

  else {
    for (int j=0; str2[j]!='\0'; j++) {

      //      cerr << "comparing " << str2[j] << " vs " << str1[0] << endl;

      if (!different_letters(str2[j], str1[0])) {
	char next[100];
	strcpy(next, str2);
	strcpy(&next[j], &str2[j+1]);

	//	cerr << "next: " << next << endl;

	return anagram(&str1[1], next);
      }
    }
    return 0;
  }
}
