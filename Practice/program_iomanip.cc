#include <iostream>
#include <string>

#include <iomanip>

using namespace std;
int main()
{

 // Reading from terminal

 cout << "Type a word:" << endl;
 string word;
 cin >> word;

 cout << "size of input: " << word.size() << endl;
 cout << "setw(8):" << setw(8) << word << endl;
 cout << "setfill('-') & setw(8):" << setw(8) << setfill('-') << word << endl;
 cout << "setfill('-') & setw(8), text left-align:" << setw(8) << left 
      << setfill('-') << word << endl;

 cout<< setfill(' ');   // setfill, right, left are 'sticky', so...

 cout << "setw(8), text left-align:" << setw(8) 
      << word << "|" << right << setw(8) << "are" << endl;

 cout << "Enter a floating number" << endl;
 float number{};
 cin >> number;

 cout << "fixed: " << fixed << number << '\n'
      << "scientific: " << scientific << number << '\n'
      << "hexfloat: " << hexfloat << number << '\n'
      << "default: " << defaultfloat << number << '\n';

 cout << "default precision (6): " << number << '\n'   
              << "setprecision(8): " << setprecision(8) << number << '\n';

 return 0;
}
