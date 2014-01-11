#include <iostream>
#include <iomanip>
#include <fstream>
#include <cassert>
#include <cstring>

using namespace std;

#include"maze.h"

/* You are pre-supplied with the functions below. Add your own 
   function definitions to the end of this file. */

/* helper function which allocates a dynamic 2D array */
char **allocate_2D_array(int rows, int columns) {
  char **m = new char *[rows];
  assert(m);
  for (int r=0; r<rows; r++) {
    m[r] = new char[columns];
    assert(m[r]);
  }
  return m;
}

/* helper function which deallocates a dynamic 2D array */
void deallocate_2D_array(char **m, int rows) {
  for (int r=0; r<rows; r++)
    delete [] m[r];
  delete [] m;
}

/* helper function for internal use only which gets the dimensions of a maze */
bool get_maze_dimensions(const char *filename, int &height, int &width) {
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

/* pre-supplied function to load a maze from a file*/
char **load_maze(const char *filename, int &height, int &width) {

  bool success = get_maze_dimensions(filename, height, width);
  
  if (!success)
    return NULL;

  char **m = allocate_2D_array(height, width);
  
  ifstream input(filename);

  char line[512];

  for (int r = 0; r<height; r++) {
    input.getline(line, 512);
    strcpy(m[r], line);
  }
  
  return m;
}

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width) {
  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    if (c && (c % 10) == 0) 
      cout << c/10;
    else
      cout << " ";
  cout << endl;

  cout << setw(4) << " " << " ";
  for (int c=0; c<width; c++)
    cout << (c % 10);
  cout << endl;

  for (int r=0; r<height; r++) {
    cout << setw(4) << r << " ";    
    for (int c=0; c<width; c++) 
      cout << m[r][c];
    cout << endl;
  }
}


bool find_marker(char ch, char** maze, int height, int width, int& row, int& column) { 

  // cerr << "ehight = " << height << ", width = " << width << endl;

  for(int i=0; i<width; i++) {
    for(int j=0; j<height; j++) {

      //  cerr << "maze[" << i << "][" << j << "] = " << maze[i][j] << endl;

      if (maze[i][j]==ch) {
	row = i;
	column = j;
	return true;
      }
    }
  }
  row = column = -1;
  return false;
}

bool valid_solution(const char* route, char** maze, int height, int width) { 
  int row=0, column=0;
  char pos='>';

  //find start marker
  if (!find_marker('>', maze, height, width, row, column)) {
    cerr << "error: could not find start marker on map" << endl;
    return false;
  }

  //follow each step of the route
  for (int i=0; route[i]!='\0'; i++) {
    pos = next_pos(row, column, route[i], maze, height, width);
    if (pos=='!')
      return false;
  }

  //check if final step is finish mark
  if (pos=='X')
    return true;
  else {
    cerr << "error: path doesn't end on finish marker" << endl;
    return false;
  }
}


char next_pos(int& row, int& column, char direction, char** maze, int height, int width) {
  char pos;

  switch(direction) {
  case'N':
    row -= 1; break;
  case'E':
    column += 1; break;
  case'S':
    row += 1; break;
  case'W':
    column -= 1; break;
  }

  if (row >= height || row < 0 || column >= width || column < 0) {
    cerr << "error: out of bounds" << endl;
    return '!';
  } 

  pos = maze[row][column];

  if (pos == '|' || pos == '-') {
    cerr << "error: passage blocked by fence" << endl;
    return '!';
  }

  //cerr << "next_pos: all good, next position is valid" << endl;

  return pos;
}


const char* find_path(char** maze, int height, int width, char start, char finish) { //return char*?
  int row=0, column=0;
  char *path = new char[100];
  char pos;

  //initialise
  find_marker(start, maze, height, width, row, column);
  pos = maze[row][column];
  strcpy(path, "");

  //iterate
  if(!recursive(maze, pos, row, column, path, 0, start, finish, height, width))
    return "no solution";

  const char* solution = path;
  return solution;  //how can I return contents from a cstring defined locally?
} 

bool recursive(char** maze, char pos, int row, int column, char* path, int path_length, char start, char finish, int height, int width) {

  //base case: has end been met
  if(pos == finish) {
    path[path_length] = '\0';
    return true;
  }

  //are there any free directions
  char freeDir[4];
  strcpy(freeDir, free_directions(maze, row, column, height, width));

  if (strcmp(freeDir,"")==0) {

    if(pos == start || strcmp(path, "")==0) {
      cerr << "\nI've tried everything, nothing works. there's no solution to this maze" << endl;
      return false;
    }

    //dont go here
    maze[row][column] = '/';
    cerr << "figured that shouldn't go to maze[" << row << "][" << column << "]" << " so direction " << path[path_length-1] << " is no good" << endl;

    //go back one step
    cerr << "going back one step in direction " << opposite(path[path_length-1]) << " from maze[" << row << "][" << column << "]  to ";
    pos = next_pos(row, column, opposite(path[path_length-1]), maze, height, width);
    cerr << "maze[" << row << "][" << column << "]" << endl;

    //edit path
    cerr << "shrinking path" << endl;
    path[path_length-1] = '\0';
    path_length--;
    cerr << "path is now " << path << endl;

    return recursive(maze, pos, row, column, path, path_length, start, finish, height, width);
  }

  //reach here iif pos is a valid position to be in

  //place mark
  cerr << "being at maze[" << row << "][" << column << "]" << " seems fine; placing '#'" << endl;
  maze[row][column] = '#';

  //take first free direction
  cerr << "going forward in direction " << opposite(path[path_length-1]) << " from maze[" << row << "][" << column << "]  to ";
  pos = next_pos(row, column, freeDir[0], maze, height, width);
  cerr << "maze[" << row << "][" << column << "]" << endl;

  //edit path
  cerr << "increasing path" << endl;
  path[path_length] = freeDir[0];
  path_length++;
  cerr << "path is now" << path << endl;

  return recursive(maze, pos, row, column, path, path_length, start, finish, height, width);
}


const char* free_directions(char** maze, int row, int column, int height, int width) {
  char freeDir[4];
  strcpy(freeDir, "");

  if (isValid(maze, row-1, column, height, width))
    strcat(freeDir, "N");

  if (isValid(maze,row+1,column, height, width))
    strcat(freeDir, "S");

  if (isValid(maze,row,column-1, height, width))
    strcat(freeDir, "W");

  if (isValid(maze,row,column+1, height, width))
    strcat(freeDir, "E");

  cerr << "free_directions at maze[" << row << "][" << column << "] are: " << freeDir << endl;

  return freeDir;
}


/* positions marked by '/' are not valid so they won't be visited again (although technically,
it is legal to go onto them)*/
bool isValid(char** maze, int row, int column, int height, int width) {
  if ((maze[row][column]==' ' || maze[row][column]=='X') && !(row >= height || row < 0 || column >= width || column < 0))
    return true;
  return false;
}


char opposite(char ch) {
  if (ch == 'N')
    return 'S';
  if (ch == 'E')
    return 'W';
  if (ch == 'S')
    return 'N';
  return 'E';
}
