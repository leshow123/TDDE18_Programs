#include "Battery.h"
#include <string>

Battery::Battery(std::string name, float volts, Connection &pstv, Connection &ngtv):
Component(name, pstv, ngtv), voltage(volts) {}
    
float Battery::simulate(float time)
{   
    c1.voltage = voltage;
    c2.voltage = 0.0;
    return voltage;
}

float Battery::get_current()
{  
    return current;
}
