#include "Component.h"
#include <string>

Component::Component(std::string name, Connection &pstv, Connection &ngtv):
name{name}, c1{pstv}, c2{ngtv} {}

float Component::peed()
{   
    float high = std::max(c1.voltage, c2.voltage);
    float low = std::min(c1.voltage, c2.voltage);
    return high-low;
}

void Component::update_terminals(float change)
{
if(c1.voltage > c2.voltage)
{
    c1.voltage -= change;
    c2.voltage += change;
}
else
{
    c1.voltage += change;
    c2.voltage -= change;
}
}

std::string Component::get_name() const
{ return name; }

float Component::get_current()
{ return current; }

Component::~Component() {c1.voltage = 0; c2.voltage = 0;}