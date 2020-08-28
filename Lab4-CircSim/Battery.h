#ifndef _BATTERY_H
#define _BATTERY_H

#include "Component.h"
#include <string>

class Battery: public Component
{
public:
    Battery(std::string name, float volts, Connection &pstv, Connection &ngtv);
    float get_current() override;
    float simulate(float time) override;

private:
    float voltage;
};

#endif
