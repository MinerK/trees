#include "tree.hpp"
#include "tree.cpp"

#include <iostream>
#include <string>

using namespace std;
typedef uint_fast64_t phone;

int main()
{
    tree<phone, string> phonebook([](phone a, phone b) {return a < b; }, 214, "root");
    phonebook.insert(1, "ewq");
	phonebook.insert(2, "asg");
	phonebook.insert(3, "qgerg");
	phonebook.insert(4,"wef");
	phonebook.insert(5,"wet");
	phonebook.insert(6, "lol");
	phonebook.insert(7, "l");
	phonebook.printinfo();
    
	system("pause");
    return 0;
}
