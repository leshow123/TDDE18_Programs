#include <iostream>
#include <string>

using namespace std;

/* EXample depicting unary operator overloading */

struct Person{
     string name{};
     int age{};
 };

Person& operator++(Person& );
Person operator++(Person& , int );

int main()
{
 
 Person p;
 p.name = "Chris";
 p.age = 26;

 Person p2{"Danladi", p.age}; 
 ++p2; 

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

Person& operator++(Person& ind)
{
 /* Version: Pre-Increment */
 cout << "Call to pre-increment" << endl;
 ++ind.age;
 return ind;
}

Person operator++(Person& ind, int )
{
 Person tmp{ind};
 ++ind;           // Calls the other version
 return tmp;   
}

