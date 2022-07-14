#include "ABB.hpp"
#include "Nodo.hpp"
#include <iostream>
#include <stack>

using namespace std;

/**
 * Inserta la coordenada en el arboL.
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
Nodo* ABB::LimpiarMemoria(Nodo* node)
{
    if (node == nullptr)
    {
        return node;
    }
    else
    {
        Nodo* aux = node;
        node = LimpiarMemoria(node->left);
        node = LimpiarMemoria(node->right);
        delete(aux);
        cout << "Nodo Eliminado" << endl;
    }
}

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
