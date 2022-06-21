#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>

#include "Persona.hpp"

using namespace cv;
using namespace std;
class Nodo {
public:
	int key;
	Persona persona;
	Nodo* next;
};
