#include"q3.h"

/* MAIN PROGRAM */
int main()
{
	Node_ptr my_list = NULL;

	assign_list(my_list);

	cout << "\nTHE LIST IS NOW:\n";
	print_list(my_list);

	cout << "forwards: ";
	print_forwards(my_list);
	cout << endl;

	cout << "backwards: ";
	print_backwards(my_list);
	cout << endl;

	char word[20], lookfor[20];

	cout << endl << "word to insert: ";
	cin.getline(word,20);

	cout << endl << "to be inserted after (' ' for right at beginning): ";
	cin.getline(lookfor,20);

	add_after(my_list, lookfor, word);

	cout << endl << "\nTHE LIST IS NOW:\n";
	print_list(my_list);

	cout << endl << "word to delete: ";
	cin.getline(word,20);

	delete_node(my_list, word);

	cout << endl << "\nTHE LIST IS NOW:\n";
	print_list(my_list);

	return 0;
}
/* END OF MAIN PROGRAM */
