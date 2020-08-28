#include <algorithm>
#include <iterator>
#include <string>
#include <cctype>
#include <regex>
#include <functional>

#include "Utility_Lambda_Functions.h"

using namespace std;

std::function<bool(string const&)> tag_or_not = [](string const &token)
{
// find html tags
// ...or ("^<")
regex tag("<[\\/]*\\S+[\\s\\S+=\\S+]*");  
// reverse polarity; so we get non-tags
return !(regex_search(token, tag));
}; 

std::function<bool(string const&)> leftover_tag = [](string const &token)
{
return (token.front() == '<'|| token.back() == '>');
};

std::function<bool(string const&, unsigned int)> spec_xter = [&](string const &token, unsigned int mode) 
{    
if(mode == 1)
{   // Mode == 1 indicating non-words remnants of html tags
    regex sxter(";|,|\\.|\"|!|\\?|:|\\)|\\(|=|@|_|#|\\$|%|\\^|&|\\*|\\+|\\]|\\[|~|\\||<|>|/|\\{|\\}");
    return (regex_search(token, sxter));    
}
else
{   //DONT INCLUDE APOSTROPHEs and VALID PUCTUATIONS for Mode = 0 (default)
    regex sxter("=|@|_|#|\\$|%|\\^|&|\\*|\\+|\\]|\\[|~|\\||<|>|/|\\{|\\}");
    return (regex_search(token, sxter));     
}
};

std::function<string(string const&)> punctuated = [](string const &token)
{
regex punctuation_front("\"|\'|\\("); 
regex punctuation_back("\\!|\\?|;|,|:|\\.|\"|\'|\\)"); 
string front;
string back; 
string temp;

front.push_back(token.front());
string res = regex_replace(front, punctuation_front, "");
if (res.empty())
{   // indicates that lead was a punctuation
    temp = token.substr(1);
}
else
{   // otherwise, lead is valid xter
    temp = token;
}

back.push_back(temp.back());
res = regex_replace(back, punctuation_back, "");
if (res.empty())
{   // indicates that trail was a punctuation
    temp = temp.substr(0, temp.length()-1);
} 
return temp;
};

std::function<string(string const&)> snake_case = [](string const &token)
{
string temp = token;
std::transform(temp.begin(), temp.end(), temp.begin(),
[](unsigned char c){ return std::tolower(c); });
return temp;
};
