#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>
#include "Nodo.hpp"

using namespace cv;
using namespace std;

class LinkedList {
private:
	const int DIFFERENT = 1700;
	int counter = 0;
	double euclideanDistance(Mat, Mat);
public:
	LinkedList() {
		header = nullptr;
	}
	struct Nodo* header;
	Nodo* insert(Nodo* header,Mat);
	Nodo* LimpiarMemoria(Nodo* nodo);
	void insert(Mat);
	~LinkedList();
};
