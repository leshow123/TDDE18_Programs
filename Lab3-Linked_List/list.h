#ifndef LIST_H
#define LIST_H

#include <initializer_list>                        

class List
{
public:
    List();                                                 // default constructor
    List(std::initializer_list<unsigned int> const& list);  // initializer constructor
    List(List const& );                                     // copy constructor
    //List& operator=(List const& source);                    // copy assignment
    List& operator=(List source);                           // copy-swap idiom nills off need for separate move-ass!
    List(List&& source);                                    // move constructor
    //List& operator=(List&& source);                         // move assignment
    ~List();                                                // destructor

    void remove(int const index);                           // remove at index x
    int size() const;                                  
    void print() const;
    bool is_empty() const;

private:
    class Link
    {
    public:
        Link(std::size_t v, Link* n );    
        ~Link();
        std::size_t value;
        Link* next;    
    };

    Link* first{nullptr};
    void copier(List const& );
    void remove();                                            

public:
    Link* insert(unsigned int const value);              // Recursive Insert-Sort
};

#endif
