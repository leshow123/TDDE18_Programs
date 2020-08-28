#include "list.h"
#include <iostream>

/* Implementation file for Constructors
 * and Destructors only */

List::List(): first{nullptr} {}

List::List(std::initializer_list<unsigned int> const& il)
: first{nullptr}         
{  
    if(il.size() > 0)
    {
        for(unsigned int const& i : il)
        {
            first = insert(i);
        }
    }
}

List::List(List const& source)                      //copy constructor
{   
    std::cout << "copy con used..." << std::endl;
    copier(source);   
}

List::Link::Link(std::size_t const v, Link* n ) 
    : value{v}, next{n} {}

//List& List::operator=(List const& source)
List& List::operator=(List source)           // copy (and move) assignment
{
    // -- copy-swap idiom --

    // Especially good when we have pointers as members
    // e.g. copying string data piece-meal is costly, so
    // we can just swap the pointers!

    //std::cout << "copy-ass used..." << std::endl;
    std::cout << "copy/move-ass used..." << std::endl;
    std::swap(first, source.first);
    /* if (this == &source) {return *this;}
    delete first;                           
    copier(source); */ 
    return *this;                
}

List::List(List&& source)                           // move constructor
: first{source.first}  
{   
    std::cout << "move con used..." << std::endl;              
    source.first = nullptr;   
}

/* List& List::operator=(List&& source)                // move assignment
{
    std::cout << "move ass used..." << std::endl;
    if (this == &source){return *this;} 
    delete first;
    first = source.first;               
    source.first = nullptr;
    return *this;
} */

List::~List()
{    
    delete first;
}

List::Link::~Link()
{
    delete next;
}