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

void MenuGuardia(ABB ABB, vector<String> imagesStr, int Hinicio, int Hfin) {
    int respuesta;
    int TiempoTotal = Hfin - Hinicio;
    cout << "Elija una de las opciones: " << "\n" << "1.- Detectar personas" << "\n" << "2.- Contar Personas que entran" << "\n" << "3.- Contar Personas que salen" << "\n" << "4.- Velocidad entran" << "\n" << "5.- Velocidad Salen" << "\n" << "6.- Salir" << endl;
    cin >> respuesta;
    while (respuesta != 1 && respuesta != 2 && respuesta != 3 && respuesta != 4 && respuesta != 5 && respuesta != 6) {
        cout << "Elija una de las opciones: " << "\n" << "1.- Detectar personas" << "\n" << "2.- Contar Personas que entran" << "\n" << "3.- Contar Personas que salen" << "\n" << "4.- Velocidad entran" << "\n" << "5.- Velocidad Salen" << "\n" << "6.- Salir" << endl;
        cin >> respuesta;
    }
    while (respuesta != 6) {
        if (respuesta == 1) {
            for (string im : imagesStr) {
                Detector detector;
                Mat imagen;
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
                }

                //Se crea una linea para poder determinar si entra o sale de una determinada zona
                Point p1(175, 0), p2(175, 300);// VERTICAL: p1(175,0), p2(175, 300) / HORIZONTAL: p1(0,140), p2(400,140)
                int thickness = 1;
                line(imagen, p1, p2, Scalar(0, 255, 255), thickness, LINE_8);

                //Se muestra la imagen
                imshow("People detector", imagen);
                waitKey(0);
            }
        }
        if (respuesta == 2) {
            std::cout << "Entran:" << ABB.Entran() << endl;
        }
        if (respuesta == 3) {
            std::cout << "Salen:" << ABB.Salen() << endl;
        }
        if (respuesta == 4) {
            if (TiempoTotal > 0) {
                std::cout << "Personas que entran por hora:" << ABB.Entran() / TiempoTotal << endl;
            }
            else {
                std::cout << "Personas que entran por hora:" << ABB.Entran() << endl;
            }
        }
        if (respuesta == 5) {
            if (TiempoTotal > 0) {
                std::cout << "Personas que entran por hora:" << ABB.Salen() / TiempoTotal << endl;
            }
            else {
                std::cout << "Personas que entran por hora:" << ABB.Salen() << endl;
            }
        }
        cout << "Elija una de las opciones: " << "\n" << "1.- Detectar personas" << "\n" << "2.- Contar Personas que entran" << "\n" << "3.- Contar Personas que salen" << "\n" << "4.- Velocidad entran" << "\n" << "5.- Velocidad Salen" << "\n" << "6.- Salir" << endl;
        cin >> respuesta;
    }

}
void DetectarPersonas(vector<String>imagesStr) {
    for (string im : imagesStr) {
        Detector detector;
        Mat imagen;
        imagen = imread(im);
        vector<Persona> found = detector.detect(imagen);
        for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
        {
            Persona& p = *i;
            rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(0, 0, 255), 1);
            circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(255, 255, 0), 2);
            circle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), 3, cv::Scalar(255, 0, 255), 2);
            circle(imagen, cv::Point(p.getXFin(), p.getYFin()), 3, cv::Scalar(0, 255, 255), 2);
        }

        //Se crea una linea para poder determinar si entra o sale de una determinada zona
        Point p1(175, 0), p2(175, 300);// VERTICAL: p1(175,0), p2(175, 300) / HORIZONTAL: p1(0,140), p2(400,140)
        int thickness = 1;
        line(imagen, p1, p2, Scalar(0, 255, 255), thickness, LINE_8);

        //Se muestra la imagen
        imshow("People detector", imagen);
        waitKey(0);
    }
}

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

    Detector detector;
    Mat imagen;

    ABB.insert(0, 175); //SE AGREGA RAIZ PARA PODER DISTINGUIR LOS QUE ENTRAN Y SALEN

    //Se recorre el vector imageStr para cargar arbol binario
    for (string im : imagesStr) {
        imagen = imread(im);
        vector<Persona> found = detector.detect(imagen);
        for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
        {
            Persona& p = *i;
            ABB.insert(p.getXComienzo(), p.getXCentro());
        }
    }
    //Se obtiene la hora de finalizacion del programa
    int HFin = timeinfo.tm_hour;
    int respuesta;
    cout << "Elija una de las dos opciones: " << "\n" << "1.- Guardia" << "\n" << "2.- Administrador"<<endl;
    cin >> respuesta;
    while (respuesta != 1 && respuesta != 2) {
        cout << "Elija una de las dos opciones: " << "\n" << "1.- Guardia" << "\n" << "2.- Administrador"<<endl;
        cin >> respuesta;
    }
    if (respuesta == 1) {
        MenuGuardia(ABB, imagesStr, HInicio, HFin);
    }
    return 0;
}
