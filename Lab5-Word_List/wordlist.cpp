#include <algorithm>
#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
#include <string>
#include <cctype>
#include <map>
#include <iomanip>
#include <regex>

#include "Functors.h"
#include "Obtain_Clean_Words.h"

using namespace std;

int main(int argc, char* argv[])
{  
bool o_flag{false};

if(argc < 2)
{
    cerr << "Error: No arguments given" 
         << "\nUsage: a.out FILE [-a][-f][-o N]"
         << endl;
}
else if(argc < 3 || ( strcmp(argv[2], "-a") != 0 
                        && strcmp(argv[2], "-f") != 0 
                        && strcmp(argv[2], "-o") != 0 ) )
{
    cerr << " Error: Second argument missing or invalid" 
         << "\nUsage: a.out FILE [-a][-f][-o]"
         << endl;
}
else if (strcmp(argv[2], "-o") == 0 && argv[3])
{
o_flag = true;
try
{
    regex catch_invalid_N("\\D"); //not a digit
    if (regex_search(argv[3], catch_invalid_N))
        throw std::invalid_argument {""};
}
catch(const std::invalid_argument& ia)
{
    cerr << "Error: Second argument missing or invalid" 
        << "\nUsage: a.out FILE [-a][-f][-o]" 
        << endl;
}
}

// Open, read file and extract 'cleaned word'

vector<string> cleaned_words;
try
{
    cleaned_words = obtain_clean_words (argv[1]);
}
catch(const std::_Ios_Iostate& e)
{
    cerr << "Error opening file. Program aborted." << '\n';
}

// Printing/Output tasks

map<string, unsigned int> dico{}; 
unsigned int longest {0};

transform(cleaned_words.begin(), cleaned_words.end(), cleaned_words.begin(), 
[&](string token)
{
// Compute longest word
longest = (longest >= token.length()) ? longest : token.length();
// Count ocurrences of each word 
unsigned int num = count(cleaned_words.begin(), cleaned_words.end(), token);
// Word-Frequency pairing
dico.insert({token, num});
return token;} );

if (strcmp(argv[2], "-a") == 0)
{
    auto printer_a = [&longest](auto const &p)
    {
    cout << left << setw(longest) << p.first 
         << right << setw(longest) << p.second << endl;
    };
    for_each(dico.begin(), dico.end(), printer_a);
}

if (strcmp(argv[2], "-f") == 0)
{
    // -- REVERSE THE MAPPING
    // Use multimap. We'll have no key uniqueness constraint
    multimap<unsigned int, string> value_key;
    auto flip_mapping = [&value_key](pair<string, unsigned int> const &p)
    {
    value_key.insert(make_pair(p.second, p.first));
    };
    for_each(dico.begin(), dico.end(), flip_mapping);

    // -- PRINT
    auto printer_f = [&longest](auto const &p)
    {
    cout << right << setw(longest) << p.second 
         << right << setw(longest) << p.first << endl;
    };
    // Use reverse iterators for print effect
    for_each(value_key.rbegin(), value_key.rend(), printer_f);
}

//for '-o n' arg
if (o_flag == true)   
{ 
    unsigned int N = stoi(argv[3]);
    // create function object instance 
    Printer_N prN (N, cleaned_words.size());
    for_each(cleaned_words.begin(), cleaned_words.end(), prN); 
}  
return 0;
}
