#ifndef _COMPONENT_H
#define _COMPONENT_H
#include "Connection.h"
#include <string>

class Component
{
public:
    std::string get_name() const;
    virtual float get_current();
    virtual float simulate(float time) = 0;
    virtual ~Component() = 0;

protected:
    Component(std::string name, Connection &pstv, Connection &ngtv);
    float peed();
    void update_terminals(float change);

    std::string name;
    float current;
    Connection &c1;
    Connection &c2;   
};

#endif