#include <iostream>
#include <cstdlib>
#include <cstring>
#include <istream>
#include <cassert>

using namespace std;


const int MAX_WORD_LENGTH = 80;

struct Node;

typedef Node *Node_ptr;


void assign_list(Node_ptr &a_list);

void assign_new_node(Node_ptr &a_node);

void print_list(Node_ptr a_node);

void assign_list(Node_ptr &a_list);

void assign_new_node(Node_ptr &a_node);

void print_list(Node_ptr a_node);

void add_after(Node_ptr &list, const char* a_word, const char* word_after);

void delete_node(Node_ptr &a_list, char* a_word);

void list_selection_sort(Node_ptr &a_list);

void print_forwards(Node_ptr list);

void print_backwards(Node_ptr list);
