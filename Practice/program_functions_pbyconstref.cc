#include <iostream>
#include <string>

using namespace std;

void read_name(string& );

/* Header anticipating a pass-by-CONST-reference */
void print_name(string const&); 

int main()
{
 string my_name;
 read_name(my_name);
 print_name(my_name);

 return 0;
}

void read_name(string& name) 
{
 cout << "Your name:";
 cin >> name;
}

void print_name(string const& name) 
{
 cout << "Your said it is: ";
 //name = "Olamide"; // will not work!!!
 cout << name << endl;
}

