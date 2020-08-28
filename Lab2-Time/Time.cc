#include "Time.h"
#include <string>
#include <iostream>
#include <cmath>

using namespace std;

bool Time::is_valid() const
{
    if( hours >= 0 && hours <= 23
        && minutes >= 0 && minutes <= 59
        && seconds >= 0 && seconds <= 59 )
        { return true; }
    return false;        
}

string Time::is_am() const
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

string Time::to_string(int const format)
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
    string th;
    string tm; 
    string ts;
    
    if (std::to_string(hours-12).length() < 2)
        {th = "0" + std::to_string(hours-12);}
    else
        {th = std::to_string(hours-12);}

    if (std::to_string(minutes).length() < 2)
        {tm = "0" + std::to_string(minutes);}
    else
        {tm = std::to_string(minutes);}

    if (std::to_string(seconds).length() < 2)
        {ts = "0" + std::to_string(seconds);} 
    else
        {ts = std::to_string(seconds);}
    
    t = th + ":" + tm + ":" + ts + " pm";
    return t;
    }
    else // 24-hr default
    {
    t = this->format();
    return t;
    }
}

string Time::format()
{
    string th;
    string tm; 
    string ts;

    if (std::to_string(hours).length() < 2)
        {th = "0" + std::to_string(hours);}
    else
        {th = std::to_string(hours);}

    if (std::to_string(minutes).length() < 2)
        {tm = "0" + std::to_string(minutes);}
    else
        {tm = std::to_string(minutes);}

    if (std::to_string(seconds).length() < 2)
        {ts = "0" + std::to_string(seconds);}
    else
        {ts = std::to_string(seconds);}

    return th + ":" + tm + ":" + ts;
}


Time Time::operator+(int const val) const
{
    int ts{0};
    int basix{0};
    int remainder{0};
    int hours_out{0};
    int minutes_out{0};
    int seconds_out{0}; 

    ts = seconds + val;
    basix = ts / 60;
    remainder = ts % 60;
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
    basix = minutes_out / 60;
    remainder = minutes_out % 60;
    
    if (basix > 0)
    {
    minutes_out = remainder;
    hours_out = hours + basix;

    // check the hour! *sigh*
    basix = hours_out/24;
    remainder = hours_out%24;
    if (basix > 0)
    { hours_out = remainder;}
    }
    else // basix @ minute < 1
    {
    minutes_out = remainder;
    hours_out = hours;
    }
    }
    
    Time out{hours_out, minutes_out, seconds_out};
    //return out.to_string(); 
    std::cout << out.to_string() << endl;
    return out;
}


Time Time::operator-(int const val) const
{
    int hours_out{0};
    int minutes_out{0};
    int seconds_out{0};

    if (val <= seconds)
    {
    seconds_out = seconds - val;
    minutes_out = minutes;
    hours_out = hours;
    }
    else if(val > seconds) // we'll be borrowing
    {
    // How much (in minutes)? At least (how_much * 60) seconds
    int how_much = val / 60;
    if(minutes/how_much > 0)  //we can borrow from minutes
    {
    seconds_out = seconds + 60*how_much - val;
    minutes_out = minutes - how_much;
    hours_out = hours;    
    }
    else // we can't borrow from minutes; hours then
    {
    // we need to borrow at least 'how_much_hour' 
    int how_much_hour = std::ceil((how_much * 1.0) / 60.0);   
    seconds_out = seconds + 60*how_much - val;
    minutes_out = minutes + 60*how_much_hour - how_much;
    hours_out = hours - how_much_hour;

    // handle scenario where its back in time to previous day
    if (hours_out < 0) 
    { hours_out = hours_out + 24; }               
    }
        
    }

    Time out{hours_out, minutes_out, seconds_out};
    std::cout << out.to_string() << endl;
    return out;
}