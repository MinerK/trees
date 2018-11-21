#include "tree.hpp"
#include "tree.cpp"
#include <string>

#include <thread>
#include <chrono>


using namespace std;
typedef uint_fast64_t phone;

void Pause(int t = 1);

int main()
{
    tree<phone, string> Phonebook([](phone a, phone b) {return a < b; });
	char Inp;
	bool exit = false;
	
	do
	{
		cout << "Phonebook." << endl;
		Phonebook.Print();
		cout<<"\n1 - Look up a phonenumber\n2 - Add a phonenumber\n3 - Change owner name of a phonenumber\n4 - Delete a phonenumber\n0 - Exit"<<endl;
		cin >> Inp;
		string str;
		phone x;
		cout << endl;
		switch (Inp)
		{
		case '1':
			cout << "Phonenumber to look up: "; cin >> x;
			try
			{
				str = Phonebook.Find(x);
			}
			catch (const char* r)
			{
				str = r;
			}
			cout << "Owner name: " << str << endl;
			Pause(2);
			break;
		case '2':
			cout << "Phonenumber to add: "; cin >> x;
			cout << "Owner name: "; cin >> str;
			Phonebook.Add(x, str);
			break;
		case '3':
			cout << "Phonenumber to change: "; cin >> x;
			cout << "New owner name: "; cin >> str;
			try
			{
				Phonebook.Change(x, str);
			}
			catch (const char* r)
			{
				cout << "Phonenumber " << r << endl;
				Pause();
			}
			break;
		case '4':
			cout << "Phonenumber to remove: "; cin >> x;
			Phonebook.Remove(x);
			break;
		case '0':
			exit = true;
		default:
			break;
		}
		if(system("cls")) system("clear");
	} while (!exit);
    return 0;
}

void Pause(int t)
{
	cout << "Returning"; this_thread::sleep_for(chrono::milliseconds(1000*t));
	cout << "."; this_thread::sleep_for(chrono::milliseconds(1000*t));
	cout << "."; this_thread::sleep_for(chrono::milliseconds(1000*t)); cout << ".";
}
