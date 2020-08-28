#include<vector>
#include<iostream>
using namespace std;
int main()
{
    vector<int> values{};
    int value{};
    //read values until ctrl+D
    while(cin >> value)
    {
        values.push_back(value);
    }
    //double each value 
    for(int& e : values)
    {
        e = 2*e;
        cout << e << endl;
    }
}