#ifndef _LIST_H_
#define _LIST_H_

#include <iostream>
#include <string>

template <typename T>
class List
{
public:
List();
~List() { delete first; }
void insert(T const& d);
List(List const&);
List(List&&);
List& operator=(List const&);
List& operator=(List&&);

// forward declare class Link or bring
// class Link before class iterator, because
// iterator creates an instance of Link
private: class Link;

public:
class iterator: public std::iterator <
                std::forward_iterator_tag,   
                T >{     
  friend iterator List<T>::begin() const;
  friend iterator List<T>::end() const;
  Link* _first;
  
  private:
    explicit iterator(Link* _init): _first(_init) {}

  public:
    auto operator*() const;
    iterator& operator++();
    iterator operator++(int );
    bool operator!=(iterator const& ) const;
  };

using value_type = T;
using Iterator = iterator;
typename List<T>::iterator begin() const;
typename List<T>::iterator end() const;

private:
class Link
{
public:
  Link(T const& d, Link* n)
    : data(d), next(n) {}
  ~Link() { delete next; }
  static Link* clone(Link const*);

friend class List;

private:
  T data;
  Link* next;
};

Link* first;
void sort();

};

// IMPORTANT: Non-Member Template Class Template Function (Op)

// Forward declare (as) function template
// before use in (Template) class body [[which is actually .tcc]].
// See: https://en.cppreference.com/w/cpp/language/friend

template <typename T>
std::ostream& operator<<(std::ostream& os, List<T> const& l); 

#include "List.tcc"
#endif
