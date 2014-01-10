#include<iostream>
#include<cstring>
#include<cstdlib>
#include<sstream>
#include<string>
#include<boost/lexical_cast.hpp>

using namespace std;

#include "correct.h"

int main() {


  /* this section illustrates the use of the pre-supplied helper functions */
  cout << "================== Helper functions ====================" << endl << endl;

  char binary[9];

  ascii_to_binary('A',binary);
  cout << "The ASCII code of 'A' is " << int('A') << " which in binary is " << binary << endl;

  ascii_to_binary('r',binary);
  cout << "The ASCII code of 'r' is " << int('r') << " which in binary is " << binary << endl;

  ascii_to_binary('t',binary);
  cout << "The ASCII code of 't' is " << int('t') << " which in binary is " << binary << endl << endl;

  char ch;
  ch = binary_to_ascii("01000001");
  cout << "The character correspoding to the binary number 01000001 is '" << ch << "'" << endl << endl;

  cout << "====================== Question 1 ======================" << endl << endl;
  
  char encoded[512], text[32];

  text_to_binary("Art",encoded);
  cout << "'Art' encoded as binary is " << encoded << endl << endl;

  binary_to_text("010000010111001001110100", text);
  cout << "010000010111001001110100 decoded as text is '" << text << "'" << 
endl << endl;

  cout << "====================== Question * ======================" << endl << endl;

  cerr << "atoi('  73') = " << atoi("  73") << endl;
  cerr << "atoi('  -23') = " << atoi("  -23") << endl;
  cerr << "atoi('  4  3') = " << atoi("  4  3") << endl;
  cerr << "atoi('  7  -3') = " << atoi("  7  -3") << endl;

  //testing itoa
  string st;
  // int value = 234;
  // //st = itoa(value);
  // //p = itoa(value);
  // cerr << "itoa(234, st, 10) = " << itoa(234, st, 10) << endl;
  // cerr << "itoa(-234, st, 10) = " << itoa(234, st, 10) << endl;
  // cerr << "itoa(value, st, 10) = " << itoa(value, st, 10) << endl;

  //testing sstream with c++ strings
  stringstream ss;
  ss << 7*8;
  st = ss.str();
  cerr << "string st = ss.str() = " << st << endl;
  //p = ss.str();

  //testing stoi, which can only work on c++ strings
  //cerr << "stoi('   -23') = " << stoi("   -23", NULL, 10) << endl;
  //const char* s = "   92  ";
  //cerr << "stoi(constchar* '   92  ') = " << stoi(s, NULL, 10) << endl;
  // string s2 = "    -90 ";
  // stoi(s2, NULL, 10);
  //cerr << "stoi(string '   -90 ') = " << stoi(s2, NULL, 10) << endl;

  //testing to_string(), which can only work on c++ strings
  //cerr << "to_string(34) = " << to_string(34) << endl;
  //st = to_string(-21);
  //string s4 = to_string(-112);

  //test lexical_cast() from boost?
  //one nondigit int
  int lint = 237;
  string str = boost::lexical_cast<string>(lint); //boost:: crucial
  const char* const_cstr = str.c_str(); //const required
  char cstr[10];            //no need if const fine
  strcpy(cstr, const_cstr); //no need if const fine
  cerr << "lexical_cast<string> etc: " << cstr << endl;

  // char* p = boost::lexical_cast<char*>(a);
  // cerr << "char* p = boost::lexical_cast<char*>(a) = " << p << endl;
  //const char* cp = boost::lexical_cast<const char*>(a);


  //char arithmetic with +-'0'
  //one digit
  int digit = 6;
  char cdigit = digit + '0';
  cerr << "cdigit: " << cdigit << endl;
    
  //array of digits
  const int length = 5;
  int digits[length] = {0,1,2,3,4};
  char cdigits[length+1];
  for(int i=0; i<length; i++)
    cdigits[i] = digits[i] + '0';
  cdigits[length] = '\0';

  cerr << "cdigits: " << cdigits << endl;

  cout << "====================== Question 2 ======================" << endl << endl;

  char correct[512]; 
  add_error_correction("0100", correct);
  cout << "0100" << " with error correction bits inserted is: " << endl << correct << endl << endl;

  add_error_correction("0001", correct);
  cout << "0001" << " with error correction bits inserted is: " << endl << correct << endl << endl;

  add_error_correction("010000010111001001110100", correct);
  cout << "010000010111001001110100 with error correction bits inserted is: " << endl << correct << endl << endl;

  cout << "====================== Question 3 ======================" << endl << endl;

  char decoded[512];
  int errors = 0;

  strcpy(correct,"1001100");  
  errors = decode(correct, decoded);
  cout << correct << " decoded is " << decoded << " (" << errors << " errors corrected)" << endl << endl;  

  strcpy(correct,"1001110");  
  errors = decode(correct, decoded);
  cout << correct << " decoded is " << decoded << " (" << errors << " errors corrected)" << endl << endl;  
                         
  strcpy(correct,"100111011010010001110010101000011011001100");  
  errors = decode(correct, decoded);
  cout << correct << " decoded is:" << endl << decoded << " (" << errors << " errors corrected)" << endl;  
  binary_to_text(decoded, text);
  cout << "which as text is '" << text << "'" << endl << endl;  

  /* but can you decode this? you can only do it if you do what it says */
  strcpy(correct,"00011000001001010001000001001100110011010011101101111110000101111001101100110010010101010100000000100110010000110101010011001101010100110011");
  errors = decode(correct, decoded);
  cout << correct << " decoded is:" << endl << decoded << " (" << errors << " errors corrected)" << endl;  
  binary_to_text(decoded, text);
  cout << "which as text is '" << text << "'" << endl << endl;  

  cout << "======================= The End ========================" << endl << endl;

}
