#ifndef _OPERATORS_H_
#define _OPERATORS_H_

#include "Time.h"
#include <iostream>

Time& operator++(Time& );
Time operator++(Time& , int );
Time& operator--(Time& );
Time operator--(Time& , int );
bool operator<(Time const& , Time const& );
bool operator>(Time const& , Time const& );
bool operator==(Time const& , Time const& );
bool operator!=(Time const& , Time const& );
bool operator<=(Time const& , Time const& );
bool operator>=(Time const& , Time const& );
std::ostream& operator<<(std::ostream& , Time const& );
std::istream& operator>>(std::istream& , Time& );

#endif