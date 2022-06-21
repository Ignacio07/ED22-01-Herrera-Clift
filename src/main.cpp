#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <iomanip>

#include "Detector.hpp"
#include "Persona.hpp"

using namespace cv;
using namespace std;
    
int main(int argc, char** argv)
{
    int entran = 0;
    int salen = 0;

    time_t now = time(0);
    struct tm timeinfo;
    time(&now);
    localtime_s(&timeinfo, &now);
    int HInicio = timeinfo.tm_hour;

    vector<string> imagesStr;
    //TODO: Cargar todos los archivos del directorio automáticamente
    imagesStr.push_back("Resources/image0292.png");
    imagesStr.push_back("Resources/image0293.png");
    imagesStr.push_back("Resources/image1679.png");
    imagesStr.push_back("Resources/image1680.png");

    cout << "imagesStr = { ";
    for (string n : imagesStr) {
        cout << n << ", ";
    }
    cout << "};" << endl;

    Detector detector;
    Mat imagen;


    for (string im : imagesStr) {
        imagen = imread(im);
        vector<Persona> found = detector.detect(imagen);
        for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
        {
            Persona& p = *i;
            cout << "(" << p.getXComienzo() << ", " << p.getYComienzo() << ")" << endl;
            rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(0, 0, 255), 1);
            circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(255, 255, 0), 2);
            circle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), 3, cv::Scalar(255, 0, 255), 2);
            circle(imagen, cv::Point(p.getXFin(), p.getYFin()), 3, cv::Scalar(0, 255, 255), 2);
            if (p.getXComienzo() < 175) {
                if (p.getXCentro() > 175) {
                    entran++;// falla por no saber diferenciar a una persona de otra
                }
            }
            if (p.getXComienzo() > 175) {
                if (p.getXCentro() < 175) {
                    salen++;
                }
            }
        }
        Point p1(175,0), p2(175, 300);// VERTICAL: p1(175,0), p2(175, 300) / HORIZONTAL: p1(0,140), p2(400,140)
        int thickness = 1;

        line(imagen, p1, p2, Scalar(0, 255, 255), thickness, LINE_8);
        imshow("People detector", imagen);
        waitKey(0);
    }
    
    int HFin = timeinfo.tm_hour;

    cout << "Entran:" << entran << endl;
    cout << "Salen:" << salen << endl;

    while (true) {
        char c = (char)waitKey(10);
        if (c == 27) break;
    }

    int TiempoTotal = HFin - HInicio;

    if (TiempoTotal > 0) {

        if(entran >= 0) {
            cout << "Personas que entran por hora:" << entran/TiempoTotal<< endl;
        }
        if (salen >= 0) {
            cout << "Personas que salen por hora:" << salen/TiempoTotal << endl;
        }
    }
    else {
        if (entran >= 0) {
            cout << "Personas que entran por hora:" << entran << endl;
        }
        if (salen >= 0) {
            cout << "Personas que salen por hora:" << salen << endl;
        }
    }
    return 0;
}
