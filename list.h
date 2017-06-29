#ifndef HW4_LIST_H
#define HW4_LIST_H
#include <iostream>
#include "Exceptions.h"
#include <functional>
template <class T>
class List {
    class node {
        friend class Iterator;
        friend class List<T>;
        T data;
        node *previous;
        node *next;

        // Constructs a new node with the specified data.
        //
        // @param node_data : the data we save inside the list
        // @param *node_previous : pointer to the previous element
        // @param *node_next: pointer to the next element
        node(T node_data, node *node_previous, node *node_next) :
                data(node_data), previous(node_previous), next(node_next) {}
    };

    int size;
    node *head;
    node *tail;
public:
    //constructs a new list with NULL pointers and size zero.
    List();

    //List destructor
    ~List();

    //copy constructor of the list
    //@param list: the list to copy the elements from
    List(const List&);

    //assignment operator of lists.
    //@param list: assigns the list into *this list
    //@return ths new list we assigned.
    List& operator=(const List&);

    //comparison operator between lists.
    //@param list: the list we want to compare with.
    //@ return true: if they are equal
    //@return false: if they are different
    bool operator==(const List&) const;

    //comparison operator between lists. (not equal)
    //@param list: the list we want to compare with.
    //@ return false: if they are equal
    //@return true: if they are different
    bool operator!=(const List&) const;

    //Iterates through the list.
    class Iterator{
        const List<T>* linked_list;
        node *current;
        // Constructs a new iterator with the specified data.
        //
        // @param *linked_list: the list we are iterate through
        // @param *current: the pointer to the current element that the iterator
        //is holding
        Iterator(const List<T> *linked_list, node *current):
                linked_list(linked_list), current(current) {}
        friend class List<T>;
    public:
        //advance the iterator to point to the next element in the list.
        //return: the next element pointer
        //return: null if its the end of the list
        Iterator& operator++();

        //advance the iterator to point to the next element in the list.
        //return: the element we pointed to before the ++
        Iterator operator++(int);

        //decrement operator.
        //return: the previous element pointer
        //return: null if its we tried to decrease the head element.
        Iterator& operator--();

        //decrement operator.
        //return: the element we pointed to before the --
        Iterator operator--(int);

        //comparison operator between iterators.
        //@param iteratorPosition: the iterator we want to compare with.
        //@ return true: if they are equal
        //@return false: if they are different
        bool operator==(const Iterator &iteratorPosition) const;

        //comparison operator between iterators. (not equal)
        //@param iteratorPosition: the iterator we want to compare with.
        //@ return false: if they are equal
        //@return true: if they are different
        bool operator!=(const Iterator &iteratorPosition) const;

        //value function.
        //@return: the data inside of the node that the iterator is pointing at.
        T &operator*() const;

        //default copy constructor
        Iterator(const Iterator &) = default;
        //default assignment operator
        Iterator &operator=(const Iterator &) = default;

        //default destructor
        ~Iterator()= default;


    };

    //Sets the iterator to point to the first element of the list.
    //return- the first element of the list.
    Iterator begin() const;

    //Sets the iterator to point to the first element of the list.
    //return- the element that is after the last element- NULL.
    Iterator end() const;

    //Inserts data to be the previous of the iterator's node.
    //@param data: the data we want to insert to the list
    //@param iterator: the element we want the inserted data to be his previous.
    //throw: ElementNotFound if the iterator element is not in the list
    void insert(const T &data, Iterator iterator);

    //Inserts data to the end of the list.
    //@param data: the data we want to insert to the list
    void insert(const T &data);

    //Removes the eleent that the iterator is pointint at.
    //@param iterator- the element we want to remove from the list
    //throw: ElementNotFound- there is no element like this in the list
    void remove(Iterator iterator);

    //Function oject that finds an element using the predicate function
    //@param: Predicate functions is a condition function- return true if the
    //element fullfils the conditions, and false other wise.
    //return: the first element that returns true, or null if there is no element
    //like this
    template<typename Predicate>
    Iterator find(const Predicate& predicate);

    //Function oject that sorts the list using compare function.
    //@param: Predicate functions is a comparison function- return true if the
    //elements fullfils the conditions, and false other wise.
    template <typename Compare>
    void sort(const Compare& compare);

    //@return: the size of the list we are working on.
    int getSize();
};
template<class T>
List<T>::List() :
        size(0), head(NULL) , tail(NULL)
{}
template<class T>
List<T>::~List() {
    while(head!=NULL){
        node* to_delete=head;
        head=head->next;
        delete to_delete;
        size--;
    }
}
template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator++() {
    current=current->next;
    return *this;
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::operator++(int) {
    Iterator result=*this;
    ++(*this);
    return result;
}
template<class T>
typename List<T>::Iterator& List<T>::Iterator::operator--() {
    current=current->previous;
    return *this;
}
template<class T>
typename List<T>::Iterator List<T>::Iterator::operator--(int) {
    Iterator result=*this;
    --*this;
    return result;
}
template<class T>
bool List<T>::Iterator::operator==(const Iterator &iteratorPosition) const {
    return (((iteratorPosition.current==linked_list->tail)&&
             (current==linked_list->tail))
            ||((((iteratorPosition.linked_list==this->linked_list)))&&
            (iteratorPosition.current)==(current)));
}
template<class T>
bool List<T>::Iterator::operator!=(const Iterator& iteratorPosition)const {
    return !(*this == iteratorPosition);
}

template<class T>
T& List<T>::Iterator::operator*() const {
    if (current==NULL){
        throw mtm::ListExceptions::ElementNotFound();
    };
    return current->data;
}
template<class T>
typename List<T>::Iterator List<T>:: begin() const {
    return Iterator(this,head);
}
template<class T>
typename List<T>::Iterator List<T>::end() const {
    List<T>::Iterator iterator=Iterator(this,tail);
    if (iterator.current!=NULL){
        iterator++;
    }
    return iterator;
}

template<class T>
void List<T>::insert(const T &data) {
    node* temp = new node(data,tail,NULL);
    if(size==0){
        head=temp;
        tail=temp;
    }
    else {
        tail->next = temp;
        tail = temp;
    }
    size++;
}
template<class T>
void List<T>::insert(const T &data, Iterator iterator) {
    if (iterator.linked_list!=this){
        throw mtm::ListExceptions::ElementNotFound();
    }
    if (getSize()==0) {
        insert(data);
    }
    else if (iterator==end()){
        insert(data);
    }
    else if (iterator.current==head){
        node* temp= new node(data, NULL, iterator.current);
        iterator.current->previous=temp;
        head=temp;
        size++;
    }
    else {
        node* temp= new node(data, iterator.current->previous, iterator.current);
        iterator.current->previous->next=temp;
        iterator.current->previous=temp;
        size++;
    }
}
template <class T>
void List<T>::remove(Iterator iterator) {
    if ((iterator.linked_list!=this || this->getSize()==0)||
        iterator.current==NULL){
        throw mtm::ListExceptions::ElementNotFound();
    }
    if((iterator!=begin())&&(iterator!=end())) {
        iterator.current->previous->next = iterator.current->next;
        iterator.current->next->previous = iterator.current->previous;
    }
    else if (iterator==begin()){
        head=iterator.current->next;
        if (size!=1) {
            head->previous = NULL;
        }
        else{
            head=NULL;
            tail=NULL;
        }
    }
    else{
        tail=iterator.current->previous;
        tail->next=NULL;
    }
    delete iterator.current;
    iterator.current = NULL;
    size--;
}

template <class T>
template <typename Predicate>
typename List<T>::Iterator List<T>::find(const Predicate &predicate) {
    for (Iterator it = begin(); it.current != NULL; it++) {
        if (predicate(*it)) {
            return it;
        }
    }
    return end();
}
template <class T>
template <typename Compare>
void List<T>::sort(const Compare &compare) {
    T tempData;
    Iterator currentTail = Iterator(this, tail);
    for (int i = 0; i < size; i++) {
        Iterator it = begin();
        while (it.current!= currentTail.current) {
            T &x=*it;
            T &y=*(++it);
            bool compare_=compare(x,y);
            if (!(compare_)) {
                tempData=x;
                x=y;
                y=tempData;
            }
        }
        currentTail--;
    }
}

template <class T>
List<T>::List(const List<T>& list):size(0),head(NULL),tail(NULL){
    for (Iterator it=list.begin(); it.current!=NULL; it++){
        this->insert(*it);
    }
}


template <class T>
List<T>& List<T>::operator=(const List<T>& list) {///destractor/////////////////////////???
    if (*this==list){
        return *this;
    }
    while(head!=NULL){
        node* to_delete=head;
        head=head->next;
        delete to_delete;
        size--;
    }
    for (Iterator it=list.begin(); it.current!=NULL; it++){
        this->insert(*it);
    }
    return *this;
}

template<class T>
bool List<T>::operator==(const List& list) const {
    if (list.size!=this->size){
        return false;
    }
    Iterator it1 = list.begin();
    Iterator it2 = this->begin();
    while ((it1.current != NULL) && (it2.current != NULL)) {
        if ((it1.current->data) != (it2.current->data)) {
            return false;
        }
        it1++;
        it2++;
    }
    return true;
}

template <class T>
bool List<T>::operator!=(const List& list) const {
    return !(*this==list);
}
template <class T>
int List<T>::getSize() {
    return size;
}


//iterator functions


#endif //HW4_LIST_H