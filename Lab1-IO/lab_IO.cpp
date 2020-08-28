#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
 int a{0};
 cout << "Enter one integer: "; 
 cin >> a;
 cout << "You entered the number: " << a << endl << endl;

 /* 
  * Clear the buffer. Takes care of left-overs
 */ 
 cin.ignore(1000,'\n'); 
 cout << "Enter four integers:";
 cin >> a;

 /* Place 1st number, followed by space on the
  * output buffer
 */
 cout << "You entered the numbers: " << a << " ";

 /* Continues from where read-head paused */
 cin >> a;
 cout << a << " ";
 cin >> a;
 cout << a << " ";
 cin >> a;
 cout << a << endl << endl;

 cin.ignore(1000,'\n');
 double h{0.0}; 
 cout << "Enter one integer and one real number: ";
 cin >> a >> h;
 cout << "The real is: " << setw(12) << setfill(' ') 
      << fixed << setprecision(3) << h << endl; 
 cout << "The integer is: " << setw(8) << setfill(' ') 
      << a << endl << endl;
 
 cin.ignore(1000,'\n');
 cout << "Enter one real and one integer number: ";
 cin >> h >> a;
 cout << "The real is: " << setw(12) << setfill('.') 
      << h << endl;
 cout << "The integer is: " << setw(8) << setfill('.') 
      << a << endl << endl;            

 cin.ignore(1000,'\n');
 char x{'\0'};
 cout << "Enter a character:";
 cin >> x;
 cout << "You entered: " << x << endl << endl;

 cin.ignore(1000,'\n');
 string s;
 cout << "Enter a word: ";
 cin >> s;
 cout << "The word '" << s << "' has " << s.size() << " character(s)" 
      << endl << endl;

 cin.ignore(1000,'\n');
 cout << "Enter an integer and a word: ";
 cin >> a >> s;
 cout << "You entered '" << a << "' and the word '" << s << "'" 
      << endl << endl;

 cin.ignore(1000,'\n');
 cout << "Enter a character and a word: ";
 cin >> x >> s;
 cout << "You entered the string '" << s <<"' and the character '" << x << "'" 
      << endl << endl;

 cin.ignore(1000,'\n');
 cout << "Enter a word and a real number: ";
 cin >> s >> h;
 cout << "You entered '" << s <<"' and '" << setprecision(3) << h << "'" 
      << endl << endl;   

 cin.ignore(1000,'\n');
 cout << "Enter a text-line: "; 
 getline(cin,s);      
 cout << "You entered: \"" << s << "\"" << endl << endl;

 cout << "Enter a second line of text: ";
 getline(cin,s);  
 cout << "You entered: \"" << s << "\"" << endl << endl;

 cout << "Enter three words: ";
 cin >> s;
 cout << "You entered: \'" << s << " ";
 cin >> s;
 cout << s << " ";
 cin >> s;
 cout << s << "\'" << endl << endl;

 return 0;
}