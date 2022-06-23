#ifndef NODE_H
#define NODE_H

#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>

#include "Persona.hpp"

using namespace cv;
using namespace std;
template <class T>

class Nodo
{
public:
    
    T persona;
    int key;
    Nodo* next;

    Nodo();
    Nodo(T,int key);
    ~Nodo();

    void delete_all();
};
#endif
