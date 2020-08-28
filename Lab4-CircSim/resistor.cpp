#include "Resistor.h"
#include <string>

Resistor::Resistor(std::string name, float ohms, Connection &pstv, Connection &ngtv):
Component(name, pstv, ngtv), resistance(ohms) {}

float Resistor::simulate(float time)
{    
    float pd = peed();
    float charge = (pd / resistance * time);
    update_terminals(charge);
    return peed(); // return updated p.d
}

float Resistor::get_current()
{
    float pd = peed();
    float current = pd / resistance;
    return current;
}