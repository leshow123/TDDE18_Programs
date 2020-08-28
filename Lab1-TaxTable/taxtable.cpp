#include <iostream>
#include <iomanip>

using namespace std;

int main()
{
    float const pdiv{100.0};
    
    cout << "\n" << "INPUT PART" << "\n";
    cout << "=========" << "\n";

    float fprice{0.0};
    cout << "Enter First Price: ";
    cin >> fprice;
    while(fprice < 0.0f)
      {
       cin.ignore(1000,'\n');   
       cerr << "ERROR: First price must be at least 0 (zero) SEK \n";
       cout << "Enter First Price: ";
       cin >> fprice;
      }
    
    float lprice{0.0};
    cout << "Enter Last Price: ";
    cin >> lprice;
    while (lprice <= fprice)                               
      {
       cin.ignore(1000,'\n');
       cerr << "ERROR: Last Price must be G.T. First Price by at least 0.01 \n";
       cout << "Enter Last Price: ";
       cin >> lprice;
      }

    float stride{0.0};
    cin.ignore(1000,'\n');        
    cout << "Enter Stride: ";
    cin >> stride;

    do
    {

    if(stride < 0.01f) 
      {   
       cerr << "ERROR:Stride must be at least 0.01 \n";
       cout << "Enter Stride: ";
       cin >> stride;
      } 

    if(stride > (lprice-fprice))
      {
       cerr << "WARNING: Keep Stride equal-to OR below " 
            << setprecision(2) << lprice-fprice << "\n";
       cout << "Enter Stride: ";
       cin >> stride;
      }  
          
    } while((stride < 0.01f) || (stride > (lprice-fprice)) );     

    float taxrate{0.0};
    cout << "Enter Tax Percentage: ";
    cin >> taxrate;

    while(taxrate < 0.0f || taxrate > 100.0f)  
    { 
      cin.ignore(1000,'\n');      
      cerr << "ERROR:Tax Percentage must be at least 0 (and no more than 100)\n";
      cout << "Enter Tax Percentage: ";
      cin >> taxrate;
    }

    cout << "\n" << "TAX TABLE" << "\n";
    cout << "=========" << "\n";

    cout << setw(12) << "Price" << setw(12) << "Tax" << setw(18)     
         << "Price With Tax" << endl;

    // (1.) 12+12+18=42 (2.) Second 'setfill' is to revert effect of first
    cout << setw(43) << setfill('-') << " " << setfill(' ') << endl;

    float iter{0.0};
    iter = (lprice-fprice) / stride;
    float price_with_tax{0.0};
    float tax{0.0};

    for(float i{0.0}; i <= iter; i++)
     {
      tax = (taxrate * fprice) / pdiv;   
      price_with_tax = fprice + tax;
      
      /* 'fixed' here for global effect */ 
      cout << fixed 
           << setw(12) << setprecision(2) << fprice << setw(12) 
           << setprecision(2) << tax << setw(18) << setprecision(2) 
           << price_with_tax << endl;     
      fprice += stride;
    }

    cout << endl;
    return 0;
}