#ifndef _UTILITY_LAMBDA_FUNCTIONS_H
#define _UTILITY_LAMBDA_FUNCTIONS_H

#include <string>
#include <vector>
#include <functional>

/* Technical Note:
 * 
 * https://stackoverflow.com/questions/40735138/forward-declaration-of-lambdas-in-c
 */
extern std::function<bool(std::string const&)> tag_or_not;
extern std::function<bool(std::string const&)> leftover_tag;
extern std::function<bool(std::string const&, unsigned int)> spec_xter; 
extern std::function<std::string(std::string const&)> punctuated;
extern std::function<std::string(std::string const&)> snake_case;

#endif