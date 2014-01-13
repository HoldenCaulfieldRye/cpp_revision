#include<iostream>
#include<fstream>

using namespace std;


void recursive(char ch, istream& in, ostream& out, bool ignoring);

int main() {

  cout << "Testing: " << 16/2 << " = " << 4*2 << ".\n\n";

  ifstream in;
  ofstream out;
  char ch;
  bool ignoring = false;

  in.open("ex.cpp");
  out.open("WithoutComments.cpp");

  if (in.fail()) {
    cerr << "could not open ex.cpp" << endl;
    return -1;
  }

  if (out.fail()) {
    cerr << "could not create WithoutComments.cpp" << endl;
    return -2;
  }

  recursive(ch, in, out, ignoring);

  return 0;
}


void recursive(char ch, istream& in, ostream& out, bool ignoring) {
  ch = in.get(); /*check eof before?*/

  if (in.eof())
    return;

  if (!ignoring && ch != '/') {
    out.put(ch);
    return recursive(ch, in, out, false);
  }

  if (!ignoring && ch == '/') {
    ch = in.get();

    if (ch == '*')
      return recursive(ch, in, out, true);

    if (ch != '*') {
      out.put('/');
      out.put(ch);
      return recursive(ch, in, out, false);
    }
  }

  if (ignoring && ch != '*')
    return recursive(ch, in, out, true);

  if (ignoring && ch == '*'){
    ch = in.get();

    if (ch == '/') /*CHANGE*/
      return recursive(ch, in, out, false);

    if (ch != '/') /*CHANGE*/
      return recursive(ch, in, out, true);
  }

  cerr << "error!" << endl;

}

/*just to trick you duuuude*/
