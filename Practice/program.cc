#include <iostream>
#include <algorithm>
#include <string>
#include <cstring>
using namespace std;
int main()
{
/*  cout <<"A C++ program"<< endl;
 cout <<"Some Text!\n";
 cout <<"Continue to push to buffer don\'t flush\n";
 cout <<"Now push out buffer to screen"<< endl;
 cout <<"The "<<flush;
 cout <<"End!"<<endl; */

int noiter{5};

string sequence {"A"};
for (int i{1}; i <= noiter; ++i)
{
    std::replace_if(sequence.begin(), sequence.end(), [] (auto gene){if (string(1,gene)=="A") return true;}, 'P');
    /* std::replace_if(sequence.begin(), sequence.end(), [] (auto gene){if (string(1,gene)=="T") return true;}, 'L');
    std::replace_if(sequence.begin(), sequence.end(), [] (auto gene){if (string(1,gene)=="C") return true;}, 'N'); */
    cout << sequence << endl;
}

return 0;
}
