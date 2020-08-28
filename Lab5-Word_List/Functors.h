#ifndef _FUNCTORS_H
#define _FUNCTORS_H

#include <vector>
#include <string>

class Printer_N
{
public:
    Printer_N(unsigned int in_argv3, unsigned int num_of_tokens_in_clean)
            : N{in_argv3}, size_of_clean{num_of_tokens_in_clean} {}
    std::string operator() (std::string const &token);

private:
    unsigned int N;
    unsigned int size_of_clean;
    std::vector<std::string> accumulator;
    unsigned int sum {0};
    unsigned int inc {0};
};

#endif