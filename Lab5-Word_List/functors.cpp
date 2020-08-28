#include <algorithm>
#include <iterator>
#include <iostream>
#include "Functors.h"

using namespace std;

// Look forward; are we going to definitely exceed? 

// If number of xters we have seen thus far, add this token's 
// xters (with its space xter) will cause an overshoot, then 
// print what we have now on the accumulator; i.e whatever we 
// have strung together thus far.

string Printer_N::operator() (string const &token)      
{
++inc;
if(sum + token.length() + 1 > N)  
{
    std::copy (accumulator.begin(), accumulator.end(),
                std::ostream_iterator<string>(cout));   
    cout << endl;
    // clean the buffer
    accumulator.erase(accumulator.begin(), accumulator.end());
    // insert this current token
    accumulator.push_back(token + " ");
    // reset sum to length of this token plus 1(for the space)
    sum = token.length() + 1 ;
}
else
{
    //...continue to string tokens together
    accumulator.push_back(token + " ");
    sum += (token.length() + 1);
}

// If all tokens exhausted, print whatever is left on the buffer
if(inc % size_of_clean == 0)  
{
    std::copy(accumulator.begin(), accumulator.end(),
                std::ostream_iterator<string>(cout));   
    cout << endl;
}
return token;
}