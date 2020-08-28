#include <iostream>
#include <string> // this header is a must

using namespace std;
int main()
{
 cout << "Enter a word and a number:";
 string word;
 double number;
 char letter;

 cin >> word;
 cin >> number;
 cin >> letter;
 
 cout << word << endl;
 cout << number << endl;
 cout << letter << endl;

 return 0;
}
