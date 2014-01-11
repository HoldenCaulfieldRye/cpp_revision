/* You are pre-supplied with the functions below. Add your own 
   function prototypes to the end of this file. */

/* helper functions to allocate and deallocate dynamic 2D arrays */
char **allocate_2D_array(int rows, int columns);
void deallocate_2D_array(char **m, int rows);

/* pre-supplied function to load a maze from a file */
char **load_maze(const char *filename, int &height, int &width);

/* pre-supplied function to print a maze */
void print_maze(char **m, int height, int width);

bool find_marker(char ch, char** maze, int height, int width, int& row, int& column);

bool valid_solution(const char* route, char** maze, int height, int width);

char next_pos(int& pos_r, int& pos_c, char direction, char** maze, int height, int width);

const char* find_path(char** maze, int height, int width, char start, char finish); //return char*?

bool recursive(char** maze, char pos, int row, int column, char* path, int path_length, char start, char finish, int height, int width);

const char* free_directions(char** maze, int row, int column, int height, int width);

bool isValid(char** maze, int row, int column, int height, int width);

char previous(char* path, int path_length);

char opposite(char ch);
