#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include "Nodo.hpp"
#include "Nodo.cpp"
#include "Persona.hpp"

using namespace cv;
using namespace std;

template <class T>

class LinkedList {
private:
	Nodo<T> *header;
	int CantNodos;

public:
	LinkedList();
	~LinkedList();
	void AgregarPersona(T);
	void LimpiarMemoria();
};
