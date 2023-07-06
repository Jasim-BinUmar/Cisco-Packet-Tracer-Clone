#ifndef List_H
#define List_H

#include<iostream> 
using namespace std; 
template<class M, class R>
class RoutEntry{
    public:
    RoutEntry<M,R>* next;
    M* machine;
    R* route;
};
// declaring linked list class   
template<class M,class R>                                                             
class RoutTable
{ 
public:
    int size=0;
    RoutEntry<M,R>* head;
    RoutEntry<M,R>* last;
    RoutTable<M,R>() {
        head = NULL;
        last = NULL;
    }
    RoutEntry<M, R>* getHead() {
        return head;
    }
    void add(M *machine,R *route) {
        if (!head) {
            // when there is no element in the list
            head = new RoutEntry<M,R>;
            head->machine = machine;
            head->route = route;
            head->next = NULL;
            last = head;
            size++;
        }
        else {
            // when the list is not empty
            if (last == head) {
                // when the list has one element
                last = new RoutEntry<M,R>;
                last->machine = machine;
                last->route = route;
                last->next = NULL;
                head->next = last;
                size++;
            }
            else {
                // when the list has more than one element
                RoutEntry<M,R>* insmachine = new RoutEntry<M,R>;
                insmachine->machine = machine;
                insmachine->route = route;
                insmachine->next = NULL;
                last->next = insmachine;
                last = insmachine;
                size++;
            }
        }
    }
    RoutEntry<M, R>* get(int index) {
        if (index == 0) {
            // returning the head element
            //return this->head->route;
            return this->head;
        }
        else {
            // Get the index'th element
            RoutEntry<M,R>* curr = this->head;
            for (int i = 0; i < index; ++i) {
                curr = curr->next;
            }
            //return curr->route;
            return curr;
        }
    }
};

#endif // !LIST_H