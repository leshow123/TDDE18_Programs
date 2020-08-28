#ifndef _RESISTOR_H
#define _RESISTOR_H

#include "Component.h"
#include <string>

class Resistor: public Component
{
public:
    Resistor(std::string name, float ohms, Connection &pstv, Connection &ngtv);
    float get_current() override;
    float simulate(float time) override;

private:
    float resistance;
};

#endif