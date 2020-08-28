#include "list.h"
#include <iostream>

using namespace std;

/* Implementation file for Operators on 
 * list structure */

//TODO: Complementary work needed, fix indent each block for readability.                   --fixed

//TODO: Complementary work needed, deleting a nullptr doesn't do anything
//and should be removed. (This involves all the files)                                      --fixed

List::Link* List::insert(unsigned int const incoming) 
{
    Link* current {first};

    // Empty list OR Case where Incoming must be before first item
    if (first == nullptr || incoming < current->value)
    {
        List::Link* new_node {new List::Link{incoming, nullptr}};
        new_node->next = first;  
        first = new_node;     
        new_node = nullptr; 
    }
    else 
    {
        // Non-empty list (others): a.) traversal with look-forward
        //                          b.) Incoming is the greatest
        while(current->next!= nullptr) 
        {
            if (incoming > current->next->value)
                current = current->next;
            else
            {
                Link* new_node {new Link{incoming, nullptr}};
                new_node->next = current->next;
                current->next = new_node;
                new_node = nullptr;
                return first;
            }
        } 
        // Haven traversed the list, and we get to the very last element...
        if(incoming > current->value)
        {
            Link* new_node {new Link{incoming, nullptr}};
            current->next = new_node;
            new_node = nullptr;
            return first;
        }
        // Go recursive. Insertion scheme: 'append' i.e first--> item1--> ...
        first->next = insert(incoming);
    }
    return first;
}

void List::remove() 
{
    if(!is_empty())
    {
        Link* tmp{first};
        first = tmp->next;
        tmp->next = nullptr;
        tmp = nullptr;
    }
}

// Remove-by-index; zero-index scheme
void List::remove(int const index) 
{
    if(!is_empty())
    {
        if(index == 0) {remove();}
        else if(index < 0 || index >= size() )
        {
            // do nothing
        }
        else 
        {
            Link* tmp {first};
            Link* previous {nullptr}; 
            for(int i{0} ;tmp != nullptr; tmp = tmp->next, ++i)
            {
                if(index == i)
                {
                    previous->next = tmp->next;
                    tmp->next = nullptr;
                }
                previous = tmp;
            } 
            delete previous;
            delete tmp;
        }
    }
}

bool List::is_empty() const 
{ 
    return (first == nullptr); 
}

int List::size() const
{ 
    Link* tmp {first};
    int i{0};
    for( ; tmp != nullptr; tmp = tmp->next) {++i;}
    tmp = nullptr;
    return i;
}

void List::print() const
{ 
    if(!is_empty())      
    {
        Link *tmp {first};
        for( ; tmp != nullptr; tmp = tmp->next) 
            {std::cout << tmp->value << " ";}
        std::cout << std::endl;
        tmp = nullptr;
    }    
}

//TODO: Complementary work needed, engine is not a very good name for this function             --fixed
//copy or something similar would be more suitable.
void List::copier(List const& source)
{
Link* iter{source.first};
Link* disc_head{nullptr};

for( ; iter != nullptr; iter = iter->next)
{   
    Link* link{new Link{iter->value, nullptr}};

    if (first == nullptr)
        {first = link;}
    else
        {disc_head->next = link;}
    disc_head = link;
    link = nullptr;
}

iter = nullptr;
disc_head = nullptr; 
} 


//TODO: Complementary work needed, your program shouldn't need a sort
//so this function is uneccessary.                                              --fixed
