// TallerOpenCV.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <iomanip>

#include "Detector.hpp"
#include "Persona.hpp"
#include "ABB.hpp"


using namespace cv;
using namespace std; //se agrega std en los cout ya que lanzo error de tipo

int main(int argc, char** argv)
{
    ABB ABB;

    // Se obtiene la hora de inicio del programa
    time_t now = time(0);
    struct tm timeinfo;
    time(&now);
    localtime_s(&timeinfo, &now);
    int HInicio = timeinfo.tm_hour;

    vector<string> imagesStr;
    // Se Cargan todos los archivos del directorio automáticamente
    imagesStr.push_back("Resources/image0292.png");
    imagesStr.push_back("Resources/image0293.png");
    imagesStr.push_back("Resources/image1679.png");
    imagesStr.push_back("Resources/image1680.png");

    std::cout << "imagesStr = { ";
    for (string n : imagesStr) {
        std::cout << n << ", ";
    }
    std::cout << "};" << endl;

    Detector detector;
    Mat imagen;

    ABB.insert(0,175); //SE AGREGA RAIZ PARA PODER DISTINGUIR LOS QUE ENTRAN Y SALEN

    //Se recorre el vector imageStr
    for (string im : imagesStr) {
        imagen = imread(im);
        vector<Persona> found = detector.detect(imagen);
        for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
        {
            Persona& p = *i;

            std::cout << "(" << p.getXComienzo() << ", " << p.getYComienzo() << ")" << endl;
            rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(0, 0, 255), 1);
            circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(255, 255, 0), 2);
            circle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), 3, cv::Scalar(255, 0, 255), 2);
            circle(imagen, cv::Point(p.getXFin(), p.getYFin()), 3, cv::Scalar(0, 255, 255), 2);

            ABB.insert(p.getXComienzo(),p.getXCentro());
        }

        //Se crea una linea para poder determinar si entra o sale de una determinada zona
        Point p1(175,0), p2(175, 300);// VERTICAL: p1(175,0), p2(175, 300) / HORIZONTAL: p1(0,140), p2(400,140)
        int thickness = 1;
        line(imagen, p1, p2, Scalar(0, 255, 255), thickness, LINE_8);
        
        //Se muestra la imagen
        imshow("People detector", imagen);
        waitKey(0);
    }
    //Se obtiene la hora de finalizacion del programa
    int HFin = timeinfo.tm_hour;

    //Se despliega el flujo de persona sin diferenciarlos
    std::cout << "Entran:" << ABB.Entran() << endl;
    std::cout << "Salen:" << ABB.Salen() << endl;

    while (true) {
        char c = (char)waitKey(10);
        if (c == 27) break;
    }

    //Se calcula cuanto tiempo estuvo activo el programa
    int TiempoTotal = HFin - HInicio;

    //Se despliega el flujo de persona por hora
    if (TiempoTotal > 0) {

        if(ABB.Entran() >= 0) {
            std::cout << "Personas que entran por hora:" << ABB.Entran() /TiempoTotal<< endl;
        }
        if (ABB.Salen() >= 0) {
            std::cout << "Personas que salen por hora:" << ABB.Salen() /TiempoTotal << endl;
        }
    }
    else {
        if (ABB.Entran() >= 0) {
            std::cout << "Personas que entran por hora:" << ABB.Entran() << endl;
        }
        if (ABB.Salen() >= 0) {
            std::cout << "Personas que salen por hora:" << ABB.Salen() << endl;
        }
    }
    return 0;
}
