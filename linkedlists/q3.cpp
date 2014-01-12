#include"q3.h"


struct Node {
  char word[MAX_WORD_LENGTH];
  Node *next;
};


/* Function to assign a linked list to NULL a_list */
void assign_list(Node_ptr &a_list) {
  assign_new_node(a_list);
  Node_ptr current = a_list, previous;
  char word[MAX_WORD_LENGTH];

  cout << "enter word ('.' to finish): " << endl;
  cin.getline(word, MAX_WORD_LENGTH);

  while(strcmp(word, ".")!=0) {
    strcpy(current->word, word);
    assign_new_node(current->next);
    previous = current;
    current = current->next;
    cout << "enter word ('.' to finish): " << endl;
    cin.getline(word, MAX_WORD_LENGTH);
  }
  previous->next = NULL;
  delete current;
}	


/* Function to assign a new dynamic node variable to "a_node" */
void assign_new_node(Node_ptr &a_node) {
  a_node = new Node;
  a_node->next = NULL;
  strcpy(a_node->word,"*");
}


/* Function to print the strings in the list "a_node" */
void print_list(Node_ptr a_node) {
  Node_ptr temp = a_node; 

  while(temp->next!=NULL) {
    cout << temp->word << " ";
    temp = temp->next;
  }
  cout << temp->word << "." << endl;

  temp = NULL;
}


void add_after(Node_ptr &list, const char* a_word, const char* word_after) {
  if (list == NULL)
    return;

  if (strcmp(a_word," ")==0) {
    Node_ptr temp = NULL;
    assign_new_node(temp);
    strcpy(temp->word, word_after);
    temp->next = list;
    list = temp;
  }

  Node_ptr current = list, next = NULL;

  while(current != NULL && strcmp(current->word, a_word)!=0)
    current = current->next;

  if (current==NULL)
    return;

  if (current->next!=NULL) //reach here iif a_word found
    next = current->next;

  assign_new_node(current->next);
  current = current->next;
  strcpy(current->word, word_after);

  if(next)
    current->next = next;

  return;
}

void delete_node(Node_ptr &list, char* a_word) {
  if (list == NULL)
    return;

  cerr << "comparing " << list->word << " with " << a_word << endl;
  if (strcmp(list->word, a_word)==0) {
    list = list->next;
    return;
  }

  Node_ptr previous = list;

  while(previous->next != NULL && strcmp((previous->next)->word, a_word)!=0) {
    previous = previous->next;
    cerr << "comparing " << (previous->next)->word << " with " << a_word << endl;
  }


  if (strcmp((previous->next)->word, a_word)==0) {
    if (!(previous->next)->next) {
      previous->next = NULL;
      return;
    }
    // cerr << "found it" << endl;
    // cerr << previous->word << " will now be followed by " << ;
    previous->next = (previous->next)->next;
  }

  return;
}

void list_selection_sort(Node_ptr &a_list) {

}

void print_forwards(Node_ptr list) {
  if (list==NULL)
    return;

  cout << list->word << " ";
  list = list->next;
  print_forwards(list);
}


void print_backwards(Node_ptr list) {
  if (list==NULL)
    return;

  Node_ptr next = list->next;
  print_backwards(next);
  cout << list->word << " ";

}

