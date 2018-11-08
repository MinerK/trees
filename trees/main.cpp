#include "tree.hpp"
#include "tree.cpp"

#include <string>

using namespace std;
typedef uint_fast64_t phone;

int main()
{
    tree<phone, string> phonebook([](phone a, phone b) {return a < b; }, 9, "root");
    phonebook.insert(8, "ewq");
    phonebook.insert(7, "asg");
    phonebook.insert(65, "qgerg");
    phonebook.insert(6,"wef");
    phonebook.insert(5,"wet");
    phonebook.insert(4, "lol");
    phonebook.insert(2, "l");
    phonebook.printinfo();
    
    system("pause");
    return 0;
}
