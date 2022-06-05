#include <stdio.h>
#include <opencv2/opencv.hpp>

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

class Detector
{
    //Atributos (Privados)
    // Enumerador 
    enum Mode { Default, Daimler } m;
    // Algoritimo de deteccion de personas
    HOGDescriptor hog, hog_d;

public:

    Detector() : m(Default), hog(), hog_d(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9) {
        hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
        hog_d.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
    }

    void toggleMode() { m = (m == Default ? Daimler : Default); }

    string modeName() const { return (m == Default ? "Default" : "Daimler"); }

    vector<Rect> detect(InputArray img) {
        // Run the detector with default parameters. to get a higher hit-rate
        // (and more false alarms, respectively), decrease the hitThreshold and
        // groupThreshold (set groupThreshold to 0 to turn off the grouping completely).
        vector<Rect> found;
        if (m == Default)
            hog.detectMultiScale(img, found, 0, Size(2, 2), Size(4, 4), 1.05, 2, false);
        else if (m == Daimler)
            hog_d.detectMultiScale(img, found, 0, Size(4, 4), Size(8, 8), 1.01, 3, true);
        return found;
    }

    void adjustRect(Rect& r) const {
        // The HOG detector returns slightly larger rectangles than the real objects,
        // so we slightly shrink the rectangles to get a nicer output.
        r.x += cvRound(r.width * 0.1);
        r.width = cvRound(r.width * 0.8);
        r.y += cvRound(r.height * 0.07);
        r.height = cvRound(r.height * 0.8);
    }

};

int main(int argc, char** argv)
{

    // Es una clase que tiene metodos para detectar personas
    Detector detector;
    // Declaro una estructura de tipo matriz (Mat)
    Mat imagen;
    // Cargo la estructura de datos con una imagen
    imagen = imread("C:/Users/Ignacio Herrera/source/repos/ConsoleApplication2/ConsoleApplication2/personas.png");

    // Cambia el tipo de algoritmo de deteccion de personas
    //detector.toggleMode();

    // Ejecuto el detector llamando al metodo detect
    vector<Rect> found = detector.detect(imagen);

    // Recorrer el vector, obtener el rectangulo y dibujar un rectangulo en la imagen
    for (vector<Rect>::iterator i = found.begin(); i != found.end(); ++i)
    {
        Rect& r = *i;
        cout << r << endl;
        // Los puntos de deteccion que hace el algoritmo muy grande
        detector.adjustRect(r);
        // Dibujar el rectangulo
        rectangle(imagen, r.tl(), r.br(), cv::Scalar(0, 255, 0), 2);
    }

    imshow("People detector", imagen);
    waitKey(0);

    return 0;
}
