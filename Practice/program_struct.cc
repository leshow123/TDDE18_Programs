#include <iostream>
#include <string>

using namespace std;

int main()
{

 struct Person{
     string name{};
     int age{};
 };
 
 Person p;
 p.name = "Chris";
 p.age = 26;

 Person p1{"Sade", 24};
 Person p2{"Danladi", ++p.age}; // p.age++ will give 26 due to 'read b4 increment'

 // Copy a struct object
 Person p2_copy{p2};
 cout << p2_copy.age << endl;
 
 return 0;
}
