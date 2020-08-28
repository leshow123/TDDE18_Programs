#include <iostream>
#include <string.h>
#include <iomanip>
#include <stdexcept>
#include <vector>
#include "Connection.h"
#include "Component.h"
#include "Resistor.h"
#include "Capacitor.h"
#include "Battery.h"

using namespace std;

void simulation(vector<Component*> const& net, unsigned int const iter, unsigned int const lines, float const steps);
void construction(unsigned int const iter, unsigned int const lines, float const steps, float const voltage);
void deallocate_component(vector<Component*> const &n);

int main(int argc, char *argv[])
{
    unsigned int iter{0};
    unsigned int lines{0};
    float steps{0.0};
    float voltage{0.0};

    try
    {

    if(argc < 5)
    {  
    cout<<"Missing input argument(s). Program exiting."<< endl;
    return 1;
    }
    else 
    {
    iter = stoi(argv[1]);
    lines = stoi(argv[2]);
    steps = stof(argv[3]);
    voltage = stof(argv[4]);
    
    if(steps < 0.0f || lines < 1 || voltage < 0.0f) 
    {   
       cout << "Arguments: No. of Lines Pritnted and/or Steps must be "
            << "positive values. Program aborting." << endl;       
       return 1; 
    }

    construction(iter, lines, steps, voltage);
    } 
   
    }
    catch(std::out_of_range& e) 
    { 
       cout << "Exception: Argument is out of range. Program aborting."
            << endl; 
       return 2;
    }
    catch(std::invalid_argument& e) 
    { 
       cout << "Exception: Invalid argument supplied. Program aborting."
            << endl; 
       return 3;
    }
    
    return 0;
}

void simulation(vector<Component*> const& net, unsigned int const iter,
              unsigned int const lines, float const steps)
{
for(auto const &i : net)
{
    cout << "\t\t" << i->get_name();
}
cout << endl;

for(int i{0}; i < net.size(); ++i)
{
    cout << "\t" << "volt";
    cout << "\t" << "curr";  
}      
cout << endl;

int ita = iter / lines;
float v{0.0};
float cur{0.0};

for(int i{1}; i <= iter; i++)
{
    for(auto const &j: net)
    {
    v = j->simulate(steps);
    cur = j->get_current();        
    if(i % ita == 0)
    {
    cout << "\t" << fixed << setprecision(2) << v; 
    cout << "\t" << fixed << setprecision(2) << cur;
    }
    }  
    if(i % ita == 0)
    {cout << endl;}
}
}

void construction(unsigned int const iter, unsigned int const lines,
               float const steps, float const voltage)
{
    Connection p, n, r124, r23, r134, r235, conn134, conn235;      
    vector<Component*> circuit1;    

    circuit1.push_back(new Battery("Bat", voltage, p, n));
    circuit1.push_back(new Resistor("R1", 6.0, p, r124));
    circuit1.push_back(new Resistor("R2", 4.0, r124, r23));
    circuit1.push_back(new Resistor("R3", 8.0, r23, n));
    circuit1.push_back(new Resistor("R4", 12.0, r124, n));
    simulation(circuit1, iter, lines, steps);
    deallocate_component(circuit1);
    
    vector<Component*> circuit2; 
    circuit2.push_back(new Battery("Bat", voltage, p, n));
    circuit2.push_back(new Resistor("R1", 150.0, p, r134));
    circuit2.push_back(new Resistor("R2", 50.0, p, r235));
    circuit2.push_back(new Resistor("R3", 100.0, r134, r235));
    circuit2.push_back(new Resistor("R4", 300.0, r134, n));
    circuit2.push_back(new Resistor("R5", 250.0, r235, n));
    simulation(circuit2, iter, lines, steps);
    deallocate_component(circuit2);
   
    vector<Component*> circuit3;
    circuit3.push_back(new Battery("Bat", voltage, p, n));
    circuit3.push_back(new Resistor("R1", 150.0, p, conn134));
    circuit3.push_back(new Resistor("R2", 50.0, p, conn235));
    circuit3.push_back(new Capacitor("C3", 1.0, conn134, conn235));
    circuit3.push_back(new Resistor("R4", 300.0, conn134, n));
    circuit3.push_back(new Capacitor("C5", 0.75, conn235, n));
    simulation(circuit3, iter, lines, steps);
    deallocate_component(circuit3);

}

void deallocate_component(vector<Component*> const &n)
{   
for(auto const &i : n) {delete i;}
}

