#include <iostream>
#include <string> // this header is a must

using namespace std;
int main()
{
 char suffix[7] = {'\t','t','h','e','r','e'};  // C-Strng

 string str {"hello"}; // ... in order for this
 cout << str << endl
      << str.size() << endl
      << str.append(suffix) << endl
      << str.data() << endl
      << str.front() << endl;
 return 0;
}
