#include "Capacitor.h"
#include <string>

Capacitor::Capacitor(std::string name, float farads, Connection &pstv, Connection &ngtv):
Component(name, pstv, ngtv), capacitance{farads}, charge{0} {}
  
float Capacitor::simulate(float time)
{
    float pd = peed();
    float v = capacitance * (pd - charge) * time; // "C times deeV-deeT"
    charge = charge + v;                          // Update stored charge value
    update_terminals(v);                          // Dont mix-up stored and +ve an -ve charge on plates
    return peed();
}

float Capacitor::get_current()
{
    float pd = peed();
    float current = capacitance * (pd - charge);
    return current;
}