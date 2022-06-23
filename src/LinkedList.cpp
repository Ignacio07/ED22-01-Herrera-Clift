#include "LinkedList.hpp"

using namespace std;

// Constructor por defecto
template<typename T>
LinkedList<T>::LinkedList()
{
    CantNodos = 0;
    header = NULL;
}

// Insertar Nodo
template<typename T>
void LinkedList<T>::AgregarPersona(T persona) // Falta poder calcular distancia entre los centroides para diferenciar a las personas
{
    Nodo<T>* NodoNuevo = new Nodo<T>(persona);
    Nodo<T>* temp = header;

    if (header) {
        header = NodoNuevo;
    }
    else {
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = NodoNuevo;
    }
    CantNodos++;
}
template<typename T>
// Elimina todos los nodos de la LinkedList
void LinkedList<T>::LimpiarMemoria()
{
    header->delete_all();
    header = NULL;
}
template<typename T>
// Destructor de LinkedList
LinkedList<T>::~LinkedList() {}
