#include <iterator>
#include <fstream>
#include <string>
#include <cctype>
#include <regex>
#include <iostream>
#include <functional>

#include "Obtain_Clean_Words.h"

using namespace std;

vector<string> obtain_clean_words (string const& filename)
{

ifstream infile;
infile.open(filename);
if (!infile)
{
    throw infile.exceptions();
}

vector<string> cleaned;
istream_iterator<string> begin{infile};
istream_iterator<string> end{};

copy_if(begin, end, back_inserter(cleaned), tag_or_not);

/* -- BEGIN: Data Cleaning Pipeline --
 * 
 *    Designed to generalize mostly for .html
 *    files
 */

// Take out any tag leftovers
cleaned.erase(remove_if(cleaned.begin(), cleaned.end(), leftover_tag), cleaned.end());

// Take out any token that has =@#$%^&.* etc. lodged within it
unsigned int mode{0};
cleaned.erase(remove_if(cleaned.begin(), cleaned.end(),
[&](string const& token){ return spec_xter(token, mode); }), cleaned.end());

// Check front and back for Punctuations: !?;,:"')( and reform
transform(cleaned.begin(), cleaned.end(), cleaned.begin(), punctuated);

// Take out any non-words that have =@#$%^&.* etc. lodged within them
mode = 1;
cleaned.erase(remove_if(cleaned.begin(), cleaned.end(),
[&](string const& token){ return spec_xter(token, mode); }), cleaned.end());

// Reform for case: 's
transform(cleaned.begin(), cleaned.end(), cleaned.begin(),
[](string token){regex sxter("\\'s"); return regex_replace(token, sxter, "");} );

// Remove invalid tokens
cleaned.erase(remove_if(cleaned.begin(), cleaned.end(), 
[](string const& token){ return !(token.length() >= 3); }), cleaned.end());

/* -- END: Data Cleaning Pipeline -- */

transform(cleaned.begin(), cleaned.end(), cleaned.begin(), snake_case);
return cleaned;
}