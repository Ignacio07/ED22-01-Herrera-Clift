#include "Nodo.hpp"
#include "Persona.hpp"

// Constructor por defecto
template<typename T>

Nodo<T>::Nodo()
{
    persona = NULL;
    next = NULL;
    key = NULL;
}

// Constructor por parámetro
template<typename T>
Nodo<T>::Nodo(T Persona,int data)
{
    persona = Persona;
    next = NULL;
    key=data;
}

// Eliminar todos los Nodos
template<typename T>
void Nodo<T>::delete_all()
{
    if (next)
        next->delete_all();
    delete this;
}

template<typename T>
// Destructor de Nodo
Nodo<T>::~Nodo() {}
