#include "stack.h"
#include <ctime>
#include <locale>
void main() {
	setlocale(LC_CTYPE, "Rus");
	HashTable<std::string> b ;
	b.insert(1, "djsfi");
	b.insert(2, "vidfuvih");
	b.insert(43, "dgeufcu");
	b.insert(9, "dchd");
	b.remove(43);
	std::cout << b;

	
}