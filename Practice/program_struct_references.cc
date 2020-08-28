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

 Person p2{"Danladi", ++p.age}; // p.age++ will give 26 due to 'read b4 increment'

 // Copy a struct object
 Person p2_copy{p2};
 cout << p2_copy.age << endl;

 // REFERENCE : create an alias for the same value
 Person& p2_alias{p2};
 cout << p2_alias.name << endl;

 // Constant REFERENCEs : for safety and security of original data
 Person const& p2_alias_immutable{p2};
 //p2_alias_immutable.name = "Danlady";  // will not work!!!
 p2.name = "Danlady";  //will work; chnaging the original will
 cout << p2_alias_immutable.name << endl;

 return 0;
}
