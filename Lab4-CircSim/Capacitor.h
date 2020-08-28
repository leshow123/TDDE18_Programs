#ifndef _CAPACITOR_H
#define _CAPACITOR_H

#include "Component.h"
#include <string>

class Capacitor: public Component
{
public:
    Capacitor(std::string name, float farads, Connection &pstv, Connection &ngtv);
    float get_current() override;
    float simulate(float time) override;

private:
    float capacitance;
    float charge;  //in store
};

#endif