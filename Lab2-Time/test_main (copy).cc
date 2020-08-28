#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include <iostream>
#include <string>
#include <cmath>

using namespace std;

struct Time
{
    int hours;
    int minutes;
    int seconds;

    Time(): hours(0), minutes(0), seconds(0) {}   
    Time(int const h, int const m, int const s)
        : hours(h), minutes(m), seconds(s) {}  

    bool is_valid()
    {
        if( hours >= 0 && hours <= 23
            && minutes >= 0 && minutes <= 59
            && seconds >= 0 && seconds <= 59 )
            {
                return true;
            }
        return false;        
    }

    string is_am()
    {
        // mmid-night or mid-day
        if ((hours == 0 && minutes == 0 && seconds == 0) 
            || (hours == 12 && minutes == 0 && seconds == 0))
        { /* return nothing*/ }

        // morning
        if (hours >= 0 && hours < 12 && minutes >=0 && 
            minutes <= 59 && seconds >=0 && seconds <= 59)
        { return "am"; }
        else
        { return "pm"; }
    }

    string to_string(int const format = 24)
    {
        string t;

        // 12-hr clock 
        if(format == 12)
        {
            // mmid-night
            if (hours == 0 && minutes == 0 && seconds == 0)
            {                 
                t = std::to_string(12) + ":0" + std::to_string(0) + ":0" + std::to_string(0); 
                return t;
            }
            // mid-day 
            if (hours == 12 && minutes == 0 && seconds == 0)
            {                 
                t = std::to_string(12) + ":0" + std::to_string(0) + ":0" + std::to_string(0); 
                return t;
            } 
            // morning
            if (hours >= 0 && hours < 12 && minutes >=0 && 
                minutes <= 59 && seconds >=0 && seconds <= 59)
            {   
                t = this->format() + " am";
                return t;
            }
            // afternoon
            string th, tm, ts;
            
            if (std::to_string(hours-12).length() < 2)
                th = "0" + std::to_string(hours-12);
            else
                th = std::to_string(hours-12); 
            if (std::to_string(minutes).length() < 2)
                tm = "0" + std::to_string(minutes);
            else
                tm = std::to_string(minutes);
            if (std::to_string(seconds).length() < 2)
                ts = "0" + std::to_string(seconds); 
            else
                ts = std::to_string(seconds);
            
            t = th + ":" + tm + ":" + ts + " pm";
            return t;
        }
        else // 24-hr default
        {
            t = this->format();
            return t;
        }
    }

    string format()
    {
        string th, tm, ts;
        if (std::to_string(hours).length() < 2)
            th = "0" + std::to_string(hours); 
        else
            th = std::to_string(hours);
        if (std::to_string(minutes).length() < 2)
            tm = "0" + std::to_string(minutes);
        else
            tm = std::to_string(minutes);
        if (std::to_string(seconds).length() < 2)
            ts = "0" + std::to_string(seconds);
        else
            ts = std::to_string(seconds);

        return th + ":" + tm + ":" + ts;
    }

    Time operator+(int const val)
    {
        int ts;
        int basix;
        int remainder;
        int hours_out;
        int minutes_out;
        int seconds_out; 

        ts = seconds + val;
        basix = ts/60;
        remainder = ts%60;
        if (basix == 0)
        {   
            seconds_out = ts;
            minutes_out = minutes;
            hours_out = hours;
        }
        else
        {
            seconds_out = remainder;
            minutes_out = minutes + basix;

            // check similarly for minutes!
            basix = minutes_out/60;
            remainder = minutes_out%60;
            
            if (basix > 0)
            {
                minutes_out = remainder;
                hours_out = hours + basix;

                // check the hour! *sigh*
                basix = hours_out/24;
                remainder = hours_out%24;
                if (basix > 0)
                {
                    hours_out = remainder;
                }
            }
            else // basix @ minute < 1
            {
                minutes_out = remainder;
                hours_out = hours;
            }
        }
        
        Time out{hours_out, minutes_out, seconds_out};
        //return out.to_string(); 
        cout << out.to_string() << endl;
        return out;
    }

    Time operator-(int const val)
    {
        int hours_out;
        int minutes_out;
        int seconds_out;

        if (val <= seconds)
        {
            seconds_out = seconds - val;
            minutes_out = minutes;
            hours_out = hours;
        }
        else if(val > seconds) // we'll be borrowing
        {
            // How much (in minutes)? At least (how_much*60) seconds
            int how_much = val/60;
            //remainder = val%60;
            if(minutes/how_much > 0)  //we can borrow from minutes
            {
                seconds_out = seconds + 60*how_much - val;
                minutes_out = minutes - how_much;
                hours_out = hours;    
            }
            else // we can't borrow from minutes; hours then
            {
                int how_much_hour = std::ceil((how_much * 1.0) / 60.0); //we need to borrow at least 'how_much_hour'   
                seconds_out = seconds + 60*how_much - val;
                minutes_out = minutes + 60*how_much_hour - how_much;
                hours_out = hours - how_much_hour;
                if (hours_out < 0) // handle scenario where its back in time to previous day
                {
                    hours_out = hours_out + 24;
                }               
            }
            
        }

        Time out{hours_out, minutes_out, seconds_out};
        cout << out.to_string() << endl;
        return out;
    }
};

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
ostream& operator<<(ostream& , Time const& );
istream& operator>>(istream& , Time& );

ostream& operator<<(ostream& os, Time const& out)
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
           && !(in.is_valid())
         )
    {
        is.setstate(ios_base::failbit);
        cout << "Warning! HH:[0-23] MM:[0-59] SS:[0-59]. Try again.\n" << endl;
        is.clear();
    }
    return is;
}

bool operator<(Time const& a, Time const& b)
{
    int a_secs = a.hours*3600 + a.minutes*60 + a.seconds;
    int b_secs = b.hours*3600 + b.minutes*60 + b.seconds;
    if(a_secs > b_secs)
        return false;
    return true;
}

bool operator>(Time const& a, Time const& b)
{
    bool is_less_than = a<b;
    if(!is_less_than && a!=b)
        return true;
    return false;
}

bool operator!=(Time const& a, Time const& b)
{
    if(a<b || b<a)
        return true;
    return false;
}

bool operator==(Time const& a, Time const& b)
{
    if (a!=b)
        return false;
    return true;
}

bool operator<=(Time const& a, Time const& b)
{
    if (a<b || a==b)
        return true;
    return false;
}

bool operator>=(Time const& a, Time const& b)
{
    if (a>b || a==b)
        return true;
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
 Time tmp{t};
 ++t;           // Calls Pre-Increment version
 return tmp;   
}

Time& operator--(Time& t)
{
 /* Version: Pre-Decrement */
 Time tmp = t - 1;
 t.seconds = tmp.seconds;
 t.minutes = tmp.minutes;
 t.hours = tmp.hours;
 return t;
}

Time operator--(Time& t, int )
{
 Time tmp{t};
 --t;           // Calls Pre-Dec version
 return tmp;   
}


TEST_CASE( "Test function is_valid()" ) {
  Time t{-18, 20, 10};
  REQUIRE( t.is_valid() == false );
} 

/* Note: Midnight and Mid-day have no suffix in 12 hr format */

TEST_CASE( "Test function to_string(); default 24-hour format" ) {
  Time t{19, 25, 40};
  REQUIRE( t.to_string().length() == 8 );
} 

TEST_CASE( "Test function to_string(); 12-hour format" ) {
  Time t{19, 25, 40};
  REQUIRE( t.to_string(12).length() == 11 );
} 

TEST_CASE( "1. Test function is_am()" ) {
  Time t{15, 25, 40};
  REQUIRE( t.is_am() == "pm" );
} 

TEST_CASE( "2. Test function is_am()" ) {
  Time t{04, 25, 40};
  REQUIRE( t.is_am() == "am" );
} 

TEST_CASE( "Test operator+ and operator-" ) {
  Time t{};
  REQUIRE( (t+5).to_string() == "00:00:05" );
  REQUIRE( t.to_string() == "00:00:00" );
  Time t2 = t+5;
  REQUIRE( (t2-5).to_string() == "00:00:00" );
  REQUIRE( t2.to_string() == "00:00:05" ); 
} 

TEST_CASE( "Test POSTFIX operator++ and operator--" ) {
  Time t{};
  Time copy_prior_inc = t++;
  REQUIRE( copy_prior_inc.to_string() == "00:00:00" ); //test the logic
  REQUIRE( (t++).to_string() == "00:00:01" );
  REQUIRE_FALSE( t.to_string() == "00:00:00" );
  Time t2 = t++;
  Time copy_prior_dec = t2--;
  REQUIRE( copy_prior_dec.to_string() == "00:00:02" ); //test the logic
  REQUIRE( (t2--).to_string() == "00:00:01" );
} 

TEST_CASE( "Test PREFIX operator++ and operator--" ) {
  Time t{};
  Time inc_then_copy = ++t;
  REQUIRE( inc_then_copy.to_string() == "00:00:01" ); //test the logic
  REQUIRE( (++t).to_string() == "00:00:02" );
  Time t2 = ++t;
  Time dec_then_copy = --t2;
  REQUIRE( dec_then_copy.to_string() == "00:00:02" ); //test the logic
  REQUIRE( (--t2).to_string() == "00:00:01" ); 
} 

TEST_CASE( "Test operator<<" ) {
  Time t{18, 20, 10};
  REQUIRE( (cout << t << "\n").good() == true );
} 

TEST_CASE( "Test operator>>" ) {
  Time t;
  REQUIRE( (cin >> t).good() == true );
} 

TEST_CASE( "Test Comparison operators" ) {
  Time t{15, 02, 55};
  Time s{18, 20, 10};
  REQUIRE( t<s );
  REQUIRE_FALSE( t>s );
  REQUIRE_FALSE( t==s );
  REQUIRE( t!=s );
  REQUIRE( t<=s );
  REQUIRE_FALSE( t>=s );
} 



