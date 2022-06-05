#include <iostream>
#include <iomanip>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;
class Nodo {
public:
	int key;
	Mat image;
	Nodo* next;
};
