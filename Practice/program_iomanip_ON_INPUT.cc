#include <iostream>
#include <string>
#include <iomanip>

#include <sstream>   // Introducing String Stream

using namespace std;
int main()
{

 // Create a string stream

 istringstream is{"Boy is mine."};
 char arr[7];
 is >> setw(4) >> arr;  // to the effect that 3 xters + '\0' will be read

 /* Recall that C++ treat strings as null terminated sequence of
    characters; including the std::string which resolves to NTCs. 
 */

 cout << "Actual: " << is.str() << " ; Read: " << arr << endl;
 
 return 0;
}
