#ifndef _TIME_H_
#define _TIME_H_

#include <string>

struct Time
{
    Time(): hours(0), minutes(0), seconds(0) {}   
    Time(int const h, int const m, int const s)
        : hours(h), minutes(m), seconds(s) {}  

    bool is_valid() const;
    std::string is_am() const;
    std::string to_string(int const format = 24);
    std::string format();
    Time operator+(int const val) const;
    Time operator-(int const val) const;

    int hours;
    int minutes;
    int seconds;
};

#endif