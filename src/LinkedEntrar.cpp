#include "opencv2/core.hpp"
#include "LinkedList.hpp"
#include "Nodo.hpp"
#include <iostream>

using namespace std;
using namespace cv;

double LinkedList::euclideanDistance(Mat img1, Mat img2) {
	return norm(img1, img2, NORM_L2);
}

void LinkedList::insert(Mat img) {
	header = insert(header, img);
}
Nodo* LinkedList::insert(Nodo* nodo, Mat img) {
	if (nodo == nullptr) {
		nodo = new Nodo();
		nodo->key = ++counter;
		nodo->next = nullptr;
	}
	else if(DIFFERENT <= euclideanDistance(nodo->image, img)){
		nodo->next = insert(nodo,img);
	}
	else {
		return nullptr;
	}
}
LinkedList::~LinkedList() {
	cout << "Lista Enlazada elimindad" << endl;
}
