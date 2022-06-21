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
	double euclideanDistance(int CentroideX, int CentroideY);
	struct Nodo* header;
public:
	LinkedList() {
		header = nullptr;
	}
	Nodo* insert(Nodo* header,Mat img);
	~LinkedList();
};
