#include "tree.h"
#include "tree.cpp"

#include <iostream>
#include <string>

using namespace std;
typedef uint_fast64_t phone;

void main()
{
	tree<phone, string> phonebook([](phone a, phone b) {return a < b; }, 214, "root");
	phonebook.insert(100, "stuff");
	cout << phonebook.intree(100);
	system("pause");
}