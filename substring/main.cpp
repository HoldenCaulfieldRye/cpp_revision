#include <iostream>
#include "substring.h"

using namespace std;

int main() {
  cout << substring_position("this", "this is a simple exercise") << endl;
  cout << substring_position("is", "this is a simple exercise") << endl;
  cout << substring_position("is a", "this is a simple exercise") << endl;
  cout << substring_position("is an", "this is a simple exercise") << endl;
  cout << substring_position("exercise", "this is a simple exercise") << endl;
  cout << substring_position("simple exercise", "this is a simple") << endl;
  cout << substring_position("", "this is a simple exercise") << endl;
  cout << substring_position("", "") << endl;

  cout << endl << endl;

  cout << substring_position_other("this", "this is a simple exercise") << endl;
  cout << substring_position_other("is", "this is a simple exercise") << endl;
  cout << substring_position_other("is a", "this is a simple exercise") << endl;
  cout << substring_position_other("is an", "this is a simple exercise") << endl;
  cout << substring_position_other("exercise", "this is a simple exercise") << endl;
  cout << substring_position_other("simple exercise", "this is a simple") << endl;
  cout << substring_position_other("", "this is a simple exercise") << endl;
  cout << substring_position_other("", "") << endl;
  return 0;
}
