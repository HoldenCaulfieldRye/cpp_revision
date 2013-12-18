#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <vector>

using namespace std;

#include "tube.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* internal helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* internal helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* internal helper function which gets the dimensions of a map */
bool get_map_dimensions(const char *filename, int &height, int &width) {
  char line[512];
  
  ifstream input(filename);

  height = width = 0;

  input.getline(line,512);  
  while (input) {
    if ( (int) strlen(line) > width)
      width = strlen(line);
    height++;
    input.getline(line,512);  
  }

  if (height > 0)
    return true;
  return false;
}

/* pre-supplied function to load a tube map from a file*/
char **load_map(const char *filename, int &height, int &width) {

  bool success = get_map_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];
  char space[] = " ";

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
    while ( (int) strlen(m[r]) < width )
      strcat(m[r], space);
  }
  
  return m;
}

/* pre-supplied function to print the tube map */
void print_map(char **m, int height, int width) {
  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(2) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(2) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}

/* pre-supplied helper function to report the errors encountered in Question 3 */
const char *error_description(int code) {
  switch(code) {
  case ERROR_START_STATION_INVALID: 
    return "Start station invalid";
  case ERROR_ROUTE_ENDPOINT_IS_NOT_STATION:
    return "Route endpoint is not a station";
  case ERROR_LINE_HOPPING_BETWEEN_STATIONS:
    return "Line hopping between stations not possible";
  case ERROR_BACKTRACKING_BETWEEN_STATIONS:
    return "Backtracking along line between stations not possible";
  case ERROR_INVALID_DIRECTION:
    return "Invalid direction";
  case ERROR_OFF_TRACK:
    return "Route goes off track";
  case ERROR_OUT_OF_BOUNDS:
    return "Route goes off map";
  }
  return "Unknown error";
}

/* presupplied helper function for converting string to direction enum */
Direction string_to_direction(const char *token) {
  const char *strings[] = {"N", "S", "W", "E", "NE", "NW", "SE", "SW"};
  for (int n=0; n<8; n++) {
    if (!strcmp(token, strings[n])) 
      return (Direction) n;
  }
  return INVALID_DIRECTION;
}

/*given symbol character 'target', finds the coordinates (r,c) of the first occurrence of that symbol on an ASCII map with height rows and width columns when scanned in a row-by-row fashion*/
bool get_symbol_position(char **map, int height, int width, char target, int& r, int& c) {
  for (r=0; r<height; r++) {
    for (c=0; c<width; c++) {
      if (map[r][c] == target)
	return true;
    }
  }
  r = c = -1;
  return false; //if fail to find anything
}

/*given the input parameter name describing the name of a station or line, returns the corresponding map symbol character*/
char get_symbol_for_station_or_line(const char* name) {
  ifstream file;
  char line[30]; 
  const char fname[2][14] = {"stations.txt","lines.txt"};
  char* candidate;
  line[0] = '\0';

  int i=0;
  for(file.open(fname[i]); i<2; file.open(fname[i])) {
    for (file.getline(line, 30); !file.fail(); file.getline(line, 30)) {
      candidate = &line[2];

      // cerr << "considering candidate: ";
      // cerr << candidate << endl;

      if (strcmp(candidate, name)==0) {
	file.close();
	return line[0];
      }
    }
    file.close();
    i++;
  }

  return ' ';
}

void get_directions(Direction* directions, char* route) {
  char dir[2];
  int i = 0, nb_dir = 0;

  for(int k=i; route[i]!='\0'; k=0) {

    /*set first direction char*/
    dir[k] = route[i];
    k++;
    i++;

    /*possibly set 2nd direction char*/
    if (route[i]!=',') {
      dir[k] = route[i];
      k++;
      i++;
    }

    /*skip the comma*/
    if (route[i]==',')
      i++;

    /*set sentinel*/
    dir[k] = '\0';
    nb_dir++;
    //cerr << "(get_directions) hope no segfault here!" << endl;
    directions[nb_dir-1] = string_to_direction(dir);
  }
  directions[nb_dir] = END;
  //cerr << "(end of get_directions) hope no segfault here!" << endl;
}


bool one_move(char** map, Direction direction, int r_cur, int c_cur, int& r_next, int& c_next) {

  cerr << "moving coordinates from (" << r_cur << ", " << c_cur << ") with direction " << direction << endl; 

  switch(direction) {
  case N:
    r_next = r_cur - 1;
    c_next = c_cur;
    return true;
  case S:
    r_next = r_cur + 1;
    c_next = c_cur;
    return true;
  case W:
    r_next = r_cur;
    c_next = c_cur - 1;
    return true;
  case E:
    r_next = r_cur;
    c_next = c_cur + 1;
    return true;
  case NE:
    r_next = r_cur - 1;
    c_next = c_cur + 1;
    return true;
  case NW:
    r_next = r_cur - 1;
    c_next = c_cur - 1;
    return true;
  case SE:
    r_next = r_cur + 1;
    c_next = c_cur + 1;
    return true;
  case SW:
    r_next = r_cur + 1;
    c_next = c_cur - 1;
    return true;
  case END:
    return true;
  case INVALID_DIRECTION:
    break;
  }
  //cerr << "(one move) returning false!" << endl;
  return false;
}

void get_name_for_station(char target, char * name) {
  ifstream file;
  char line[30];
  //  char* candidate;
  line[0] = '\0';

  //cerr << "looking for symbol " << target << endl;

  file.open("stations.txt");
  for (file.getline(line, 30); !file.fail(); file.getline(line, 30)) {
    strcpy(name, &line[2]);

    // cerr << "considering name: ";
    // cerr << line[0] << endl;

    if (line[0]==target) {
      file.close();
      //cerr << "found station: " << name << endl;
      return;
    }
  }
  file.close();
  //cerr << "no station found" << endl;
}


int validate_route(char** map, int height, int width, const char* start, char* route, char* dest) {
  char prev, current, next;
  Direction directions[500];
  int r_prev=0, c_prev=0, r_cur=0, c_cur=0, r_next=0, c_next=0, line_changes=0;

  /*get Direction vector*/
  get_directions(directions, route);

  //cerr << "directions: ";
  // for (int i=0; directions[i]!=END; i++)
  //   cerr << directions[i] << ", ";
  // cerr << endl; 

  /*get symbol and coordinates for start*/
  current = get_symbol_for_station_or_line(start);
   cerr << "start station " << start << " has symbol " << current << endl;

  if (!isalnum(current))
    return -1; //start station invalid (if line, still invalid)
  get_symbol_position(map, height, width, current, r_cur, c_cur);
     cerr << "current station has coordinates (" << r_cur << ", " << c_cur << ")"<< endl;

  /*navigate from start to finish with Direction array*/
  //  cerr << "(for beg) hope no segfault here!" << endl;
  for (int i=0; directions[i]!=END; i++) {

    if(!one_move(map, directions[i], r_cur, c_cur, r_next, c_next))
      return -5;         //invalid direction

    if (r_next<0 || c_next<0 || r_next>=height || c_next>=width)
      return -7;         //out of bounds

    /*not out of bounds so can safely get symbol for next*/
    next = map[r_next][c_next];
    //  cerr << "next point on map has coordinates (" << r_next << ", " << c_next << ")"<< endl;

    //  cerr << "next point on map has symbol " << next << endl;

    if (i>1 && r_prev==r_next && c_prev==c_next)
      return -4;         //backtracking

    if (next==' ')
      return -6;         //off track

    if (!isalnum(next) && !isalnum(current) && next != current)
      return -3;         //line hopping


    if (i>2 && !isalnum(next) && !isalnum(prev) && next != prev)
      line_changes++;

    //get_symbol_position(map, height, width, target, r, c);
    prev = current;
    c_prev = c_cur;
    r_prev = r_cur;
    current = next;
    c_cur = c_next;
    r_cur = r_next;
     cerr << "move successfully to (" << r_cur << ", " << c_cur << ", " <<current << ")" << endl << endl;
    //  cerr << "(for loop) hope no segfault here!" << endl;
  }


  /*evaluate destination*/
  if (!isalnum(current))
    return -2; //route endpoint not a station
  get_name_for_station(current, dest);

  //  cerr << "check that dest has sentinel (else segfault): " << dest << endl;

  return line_changes;
}
