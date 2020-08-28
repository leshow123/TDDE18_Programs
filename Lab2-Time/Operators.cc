#include "Operators.h"
#include <iostream>

using namespace std;

ostream& operator<< (ostream& os, Time const& out)
{
Time tmp{out};
os << tmp.to_string();
return os;
}

istream& operator>>(istream& is, Time& in)
{  
while( cout << "Enter HH:MM:SS\n" 
    && is >> in.hours
    && is.ignore(1,':')
    && is >> in.minutes
    && is.ignore(1,':')
    && is >> in.seconds
    && !(in.is_valid()) )
{
    is.setstate(ios_base::failbit);
    cout << "Warning! HH:[0-23] MM:[0-59] SS:[0-59]."
         << "Try again.\n" << endl;
    is.clear();
}
return is;
}

bool operator<(Time const& a, Time const& b)
{
int a_secs = a.hours*3600 + a.minutes*60 + a.seconds;
int b_secs = b.hours*3600 + b.minutes*60 + b.seconds;
if(a_secs > b_secs)
    {return false;}
return true;
}

bool operator>(Time const& a, Time const& b)
{
bool is_less_than = a < b;
if(!is_less_than && a!=b)
    {return true;}
return false;
}

bool operator!=(Time const& a, Time const& b)
{
if(a < b || b < a)
    {return true;}
return false;
}

bool operator==(Time const& a, Time const& b)
{
if (a != b)
    {return false;}
return true;
}

bool operator<=(Time const& a, Time const& b)
{
if (a < b || a == b)
    {return true;}
return false;
}

bool operator>=(Time const& a, Time const& b)
{
if (a > b || a == b)
    {return true;}
return false;
}

Time& operator++(Time& t)
{
 /* Version: Pre-Increment */
 Time tmp = t + 1;
 t.seconds = tmp.seconds;
 t.minutes = tmp.minutes;
 t.hours = tmp.hours;
 return t;
}

Time operator++(Time& t, int )
{
 std::cout << "Called post-increment..." << std::endl;   
 Time tmp{t};
 // Call Pre-Increment version
 ++t;          
 return tmp;   
}

/* Version: Pre-Decrement */
Time& operator--(Time& t)
{
 Time tmp = t - 1;
 t.seconds = tmp.seconds;
 t.minutes = tmp.minutes;
 t.hours = tmp.hours;
 return t;
}

Time operator--(Time& t, int )
{
 Time tmp{t};
 // Calls Pre-Dec version
 --t;           
 return tmp;   
}