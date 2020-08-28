#include <iostream>
#include <string>

using namespace std;

void print(string& );
void print(int& );

/* Note: however, consider default parameters*/

int main()
{
 cout << "Name:";
 string name;
 cin >> name;
 cout << "\nAge:";
 int age;
 cin >> age;

 print(name);
 print(age);

 return 0;
}

void print(string& name) 
{
 cout << "Your name:";
 cout << name << endl;
}

void print(int& age) 
{
 cout << "Your age:";
 cout << age << endl;
}

