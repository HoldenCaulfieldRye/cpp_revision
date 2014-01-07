int encode_character(char ch, char* braille);

void encode(const char* str, char* braille);

void print_braille(const char* str, ostream& out);

void matrify(const char* str,  char* braille, char* mat, char** m);
