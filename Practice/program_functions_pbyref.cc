#include <iostream>
#include <string>

using namespace std;

/* Header anticipating a pass-by-reference */
void read_name(string& );  // Function Declaration

int main()
{
 string my_name;
 read_name(my_name);
 cout << my_name << endl;

 return 0;
}

void read_name(string& name) //Function Definition, passed a reference
{
 cout << "Your name:";
 cin >> name;
 // However, there's a chance that original data might be overriden intentionally
 // or otherwise; See 'program_functions_pbyconstref.cc'
}

