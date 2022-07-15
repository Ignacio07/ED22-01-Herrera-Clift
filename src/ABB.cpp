#include "ABB.hpp"
#include "Nodo.hpp"
#include <iostream>
#include <stack>

using namespace std;

/**
 * Inserta la coordenada en el arbol le asigna un identificador.
 *
 * @param coordenada (int) centroide de la imagen
 */
void ABB::insert(int coordenadaInicio,int centroide) {
    root = insert(root,coordenadaInicio,centroide);
}
Nodo* ABB::insert(Nodo* node, int coordenadaInicio,int centroide) {
    //Si el árbol no tiene hijos
    if (node == nullptr) {
        node = new Nodo();
        node->CentroideX = centroide;
        node->left = nullptr;
        node->right = nullptr;
        return node;
    }
    else{ 
        if (coordenadaInicio > 175 && centroide < 175) {
            node->left = insert(node->left, coordenadaInicio, centroide);
        }
        if (coordenadaInicio < 175 && centroide > 175) {
            node->right = insert(node->right, coordenadaInicio, centroide);
        }
    }
    return node;
}
/*
* Elimina los nodos del arbol
*/
void ABB::LimpiarMemoria(){
    if (root){
        stack<Nodo*> s;
        s.push(root);
        while (!s.empty()) {
            Nodo* curr = s.top();
            s.pop();
            if (curr->left != NULL) {
                s.push(curr->left);
            }
            if (curr->right != NULL) {
                s.push(curr->right);
            }
            curr->left = nullptr;
            curr->right = nullptr;
        }
    }
}
/**
* Recorre el lado derecho del ABB para saber cuantas personas entran.
**/
int ABB::Entran() {
    if (root) {
        int count = 0;
        stack<Nodo*> s;
        if (root->right != NULL) {
            s.push(root->right);
            while (!s.empty()) {
                count++;
                Nodo* curr = s.top();
                s.pop();
                if (curr->left != NULL) {
                    s.push(curr->left);
                }
                if (curr->right != NULL) {
                    s.push(curr->right);
                }
            }
            return count;
        }
    }
    return 0;
}
/**
* Recorre el lado izquierdo del ABB para saber cuantas personas salen.
**/
int ABB::Salen() {
    if (root) {
        int count = 0;
        stack<Nodo*> s;
        if (root->left != NULL) {
            s.push(root->left);
            while (!s.empty()) {
                count++;
                Nodo* curr = s.top();
                s.pop();
                if (curr->left != NULL) {
                    s.push(curr->left);
                }
                if (curr->right != NULL) {
                    s.push(curr->right);
                }
            }
            return count;
        }
    }
    return 0;
}

ABB::~ABB(void)
{
    cout << "Arbol Eliminado" << endl;
}
