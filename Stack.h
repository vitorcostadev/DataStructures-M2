#ifndef STACK_H_INCLUDED
#define STACK_H_INCLUDED

#include <iostream>
using namespace std;

template<typename T>
struct Node{
    T element;
    Node<T> *topo;
};

template<typename T>
struct Stack{
    int topo;
    Node<T>* inicio;
};

// create a default stack
template<typename T>
void create(Stack<T> &stack){
    stack.inicio = NULL;
    stack.topo = 0;
}

// size or cardinalidade of stack
template<typename T>
int size(Stack<T> stack) { return stack.topo; }

// add a new element to stack
template<typename T>
void push(Stack<T> &stack, T element){
    Node<T> *newStack = new Node<T>();
    newStack->element = element;
    newStack->topo = stack.inicio;
    stack.inicio = newStack;

    stack.topo++;
}

// remove the last element of stack
template<typename T>
void pop(Stack<T> &stack){
    if(size(stack) == 0) throw "EMPTY_STACK";

    Node<T> *temp = stack.inicio;
    stack.inicio = stack.inicio->topo;
    delete temp;
    stack.topo--;
}

// print all elements of stack
template<typename T>
void imprime(Stack<T> stack){
    cout << "[";
    for(Node<T> *aux = stack.inicio; aux != NULL; aux = aux->topo){
        cout << aux->element;
        if(aux->topo != NULL) cout << ",";
    }
    cout << "]" << endl;
}

// destroy stack and free memory
template<typename T>
void destroy(Stack<T> &stack){
    Node<T> *aux = stack.inicio;
    while(aux != NULL){
        Node<T> *temp = aux;
        aux = aux->topo;
        delete temp;
    }
    stack.inicio = NULL;
    stack.topo = 0;

}

// check if stack contains an element
template<typename T>
bool contains(Stack<T> stack, T element){
    if(size(stack) == 0) return false;

    Node<T> *aux = stack.inicio;
    while(aux != NULL && aux->element != element) aux=aux->topo;

    return aux == NULL ? false : true;
}

// check if index exists in stack
template<typename T>
bool exists(Stack<T> stack, int index){
    return (index >= 1 && index <= size(stack));
}

// get element of stack by index
template<typename T>
T get(Stack<T> stack, int index){
    if(!exists(stack, index)) throw "INDEX_NOT_FOUND";

    int cont = 1;
    Node<T> *a = stack.inicio;

    while(a != NULL && cont++ != index){
        a = a->topo;
    }


    return a != NULL ? a->element : throw "ELEMENT_NOT_FOUND";
}

// get the top of stack
template<typename T>
T top(Stack<T> stack){
    if(size(stack) == 0) throw "EMPTY_STACK";
    return stack.inicio->element;
}

#endif // STACK_H_INCLUDED
