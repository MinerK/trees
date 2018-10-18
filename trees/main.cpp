#include "tree.hpp"
#include "tree.cpp"

#include <iostream>
#include <string>

using namespace std;
typedef uint_fast64_t phone;

int main()
{
    tree<phone, string> phonebook([](phone a, phone b) {return a < b; }, 214, "root");
    phonebook.insert(50, "woah");
    cout<<phonebook.intree(214);
    
    return 0;
}
