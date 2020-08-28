#include <iostream>
#include <string> 
#include <fstream>

using namespace std;
int main()
{

 // Reading from terminal

 cout << "Type sentences:" << endl;
 string line;
 getline(cin, line);
 cout << "Dumped: "<< line << endl << endl;

 //Reading from file

  /* create a input file stream */
  ifstream dataset{"data.txt"};

  /* read from the input file-stream - one line */
  getline(dataset, line);

  cout << "File Dumped (One Line): "
       << line << endl; 

  /* ...and the rest of the lines in the file */
  cout << endl;
  while(getline(dataset, line)){
      cout << line << '\n';
  }

  /* write the last line to an outout file */
  ofstream out{"output.txt"};
  out << line;

 return 0;
}
