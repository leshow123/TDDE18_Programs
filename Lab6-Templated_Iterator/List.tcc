#include <algorithm>
#include "List.h"

template <typename T>
void List<T>::insert(T const& d)
{
first = new Link(d, first);
sort();
}

template <typename T>
// typename keyword has to qualify since 
// Link* is dependent
typename List<T>::Link*           
List<T>::Link::clone(Link const* dolly)
{
if(dolly != nullptr)
  return new Link(dolly->data, clone(dolly->next));
else
  return nullptr;
}

template <typename T>
List<T>::List() : first(nullptr)
{
std::clog << "***Default construction" << std::endl;
}

template <typename T>
List<T>::List(List const& l)
{
std::clog << "***Copy construction" << std::endl;
first = Link::clone(l.first);
}

template <typename T>
List<T>::List(List&& l)
{
std::clog << "***Move construction" << std::endl;
first = l.first;
l.first = nullptr;
}

template <typename T>
List<T>& List<T>::operator=(List const& rhs)
{
std::clog << "***Copy assignment" << std::endl;
if(&rhs != this)
{
  List copy(rhs);
  std::swap(first, copy.first);
}
return *this;
}

template <typename T>
List<T>& List<T>::operator=(List&& rhs)
{
std::clog << "***Move assignment" << std::endl;
if (&rhs != this)
{
  std::swap(first, rhs.first);
}
return *this;
}

template <typename T>
typename List<T>::iterator List<T>::begin() const
{
return iterator(first);
}

template <typename T>
typename List<T>::iterator List<T>::end() const
{
return iterator(nullptr); 
}

template <typename T>
void List<T>::sort()
{
Link* iter{nullptr};
Link* end{nullptr};
int status {0};
        
do
{ 
status = 0;
iter = first;
for( ; iter->next != end; iter = iter->next)
{      
if (iter->data > iter->next->data)
{
  T temp = iter->data;          
  iter->data = iter->next->data;
  iter->next->data = temp;
  status = 1;       
}    
}  
end = iter;
} while (status); 
        
iter = nullptr;
end = nullptr;
delete iter;
delete end;
}

template <typename T>
typename List<T>::iterator& List<T>::iterator::operator++()
{
_first = _first->next;
return *this; 
}

template <typename T>
typename List<T>::iterator List<T>::iterator::operator++(int )
{
Link* temp {_first};
_first = _first->next;
return iterator(temp);
}

template <typename T>
auto List<T>::iterator::operator*() const 
{ return _first->data; }

template <typename T>
bool List<T>::iterator::operator!=(iterator const& ) const
{
return !(_first == nullptr);
}

template <typename T>
// -- This will not have a full name qualifier; its a non-member! -- 
std::ostream& operator<<(std::ostream& os, List<T> const& l)
{
//const typename List<T>::iterator b = l.begin();
auto it {l.begin()};

for( ; it!=l.end(); ++it)
  {os << *it << " ";}  
return os;  
}
