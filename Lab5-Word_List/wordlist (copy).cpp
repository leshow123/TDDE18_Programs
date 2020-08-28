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

using namespace std;

void obtain_clean_words (std::string const& , std::vector<string>& );

int main (int argc,  char *argv[])
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
            std::regex catch_invalid_N("\\D"); //not a digit
            if (std::regex_search(argv[3], catch_invalid_N))
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
    std::vector<string> cleaned_words;
    try
    {
        obtain_clean_words (argv[1], cleaned_words);
    }
    catch(const std::_Ios_Iostate& e)
    {
        cerr << "File not found! Program aborted." << '\n';
    }

    map<string, unsigned int> dico{}; 
    unsigned int longest {0};

    std::transform(cleaned_words.begin(), cleaned_words.end(), cleaned_words.begin(), 
    [&](string token)
    {
    // Compute longest word
    longest = (longest >= token.length()) ? longest : token.length();
    // Count ocurrences of each word 
    unsigned int num = std::count(cleaned_words.begin(), cleaned_words.end(), token);
    // Word-Frequency pairing
    dico.insert({token, num});
    return token;} );

    if (strcmp(argv[2], "-a") == 0)
    {
        auto printer_a = [&longest](auto const &p){
        cout << left << setw(longest) << p.first 
                << right << setw(longest) << p.second << endl;
        };

        for_each(dico.begin(), dico.end(), printer_a);
    }

    if (strcmp(argv[2], "-f") == 0)
    {
        // Use multimap. We'll have no key uniqueness constraint
        multimap<unsigned int, string> value_key;

        auto flip_mapping = [&value_key](std::pair<string, unsigned int> const &p){
            value_key.insert(std::make_pair(p.second, p.first));
        };

        auto printer_f = [&longest](auto const &p){
        cout << right << setw(longest) << p.second 
                << right << setw(longest) << p.first << endl;
        };
        for_each(dico.begin(), dico.end(), flip_mapping);
        // Use reverse iterators for print effect
        for_each(value_key.rbegin(), value_key.rend(), printer_f);
    }

    if (o_flag == true)    //for '-o n' arg  
    { 
        vector<string> accumulator;
        unsigned int sum {0};
        unsigned int inc {0};
        unsigned int N = stoi(argv[3]);

        auto printer_N = [&](string token){
            ++inc;
            /* Look forward; are we going to definitely exceed? */

            // If number of xters we have seen thus far, add this token's 
            // xters (with its space xter) will cause an overshoot, then 
            // print what we have now on the accumulator; i.e whatever we 
            // have strung together thus far.

            if(sum + token.length() + 1 > N)  
            {
                std::copy (accumulator.begin(), accumulator.end(),
                            std::ostream_iterator<string>(cout));   
                cout << endl;
                // clean the buffer
                accumulator.erase(accumulator.begin(), accumulator.end());
                // insert this current token
                accumulator.push_back(token + " ");
                // reset sum to length of this current token plus 1(for the space)
                sum = token.length() + 1 ;
            }
            else
            {
                //...continue to string tokens together with space demarcating
                accumulator.push_back(token + " ");
                sum += (token.length() + 1);
            }
            
            // If all tokens exhauted, print whatever is left on the accumulator
            if(inc % cleaned_words.size() == 0)  
            {
                std::copy(accumulator.begin(), accumulator.end(),
                          std::ostream_iterator<string>(cout));   
                cout << endl;
            }
        };

        for_each(cleaned_words.begin(), cleaned_words.end(), printer_N );
    }  
    return 0;
}

auto tag_or_not = [](string token){
    // find html tags
    regex tag("<[\\/]*\\S+[\\s\\S+=\\S+]*");  //  or  ("^<") ...but simpler is not always better
    // reverse polarity; so we get non-tags
    return !(regex_search(token, tag)) ;
}; 

auto leftover_tag = [](string token){
    return (token.front() == '<'|| token.back() == '>') ;
};

unsigned int mode{0};
auto spec_xter = [&](string token){
    
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

auto punctuated = [](string token){

    regex punctuation_front("\"|\'|\\("); 
    regex punctuation_back("\\!|\\?|;|,|:|\\.|\"|\'|\\)"); 
    string front, back, temp;

    front.push_back(token.front());
    string res = regex_replace(front, punctuation_front, "");
    if (res.empty())
    { // indicates that lead was a punctuation
        token = token.substr(1);
    }

    back.push_back(token.back());
    res = regex_replace(back, punctuation_back, "");
    if (res.empty())
    { // indicates that trail was a punctuation
        token = token.substr(0, token.length()-1);
    } 
    return token;
};

auto snake_case = [&](string token){
    std::transform(token.begin(), token.end(), token.begin(),
    [](unsigned char c){ return std::tolower(c); });
    return token;
};

void obtain_clean_words (string const& filename, std::vector<string>& v)
{
    ifstream infile;
    infile.open(filename);
    if (!infile)
    {
        throw infile.exceptions();
    }
    
    istream_iterator<string> begin{infile};
    istream_iterator<string> end{};
    copy_if(begin, end, back_inserter(v), tag_or_not);

    /* -- BEGIN: Data Cleaning Pipeline -- */

    // Take out any tag leftovers
    v.erase(remove_if(v.begin(), v.end(), leftover_tag), v.end());

    // Take out any token that has =@#$%^&.* etc. lodged within it
    v.erase(remove_if(v.begin(), v.end(), spec_xter), v.end());

    // Check front and back for Punctuations: !?;,:"')( and reform
    std::transform(v.begin(), v.end(), v.begin(), punctuated);

    // Take out any non-words that have =@#$%^&.* etc. lodged within them
    mode = 1;
    v.erase(remove_if(v.begin(), v.end(), spec_xter), v.end());

    // Reform for case: 's
    std::transform(v.begin(), v.end(), v.begin(),
    [](string token){regex sxter("\\'s"); return regex_replace(token, sxter, "");} );

    // Remove invalid tokens
    v.erase(remove_if(v.begin(), v.end(), 
    [](string const& token){ return !(token.length() >= 3); }), v.end());

    /* -- END: Data Cleaning Pipeline -- */

    std::transform(v.begin(), v.end(), v.begin(), snake_case);
}






