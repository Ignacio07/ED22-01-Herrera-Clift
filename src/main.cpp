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
using namespace std;

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
            DetectarPersonas(imagesStr);
        }
        if (respuesta == 2) {
            cout << "Entran:" << ABB.Entran() << endl;
        }
        if (respuesta == 3) {
            cout << "Salen:" << ABB.Salen() << endl;
        }
        if (respuesta == 4) {
            if (TiempoTotal > 0) {
                cout << "Personas que entran por hora:" << ABB.Entran() / TiempoTotal << endl;
            }
            else {
                cout << "Personas que entran por hora:" << ABB.Entran() << endl;
            }
        }
        if (respuesta == 5) {
            if (TiempoTotal > 0) {
                cout << "Personas que entran por hora:" << ABB.Salen() / TiempoTotal << endl;
            }
            else {
                cout << "Personas que entran por hora:" << ABB.Salen() << endl;
            }
        }
        cout << "Elija una de las opciones: " << "\n" << "1.- Detectar personas" << "\n" << "2.- Contar Personas que entran" << "\n" << "3.- Contar Personas que salen" << "\n" << "4.- Velocidad entran" << "\n" << "5.- Velocidad Salen" << "\n" << "6.- Salir" << endl;
        cin >> respuesta;
    }

}

void MenuAdmin(vector<string>* imagesStr) {
    int respuesta;
    cout << "Bienvenido al menu de Administrador" << "\n" << "Elija que secuencia de imagenes va a ser analizada" << "\n" << "1.- Video1" << "\n" << "2.- Video2" << "\n" << "3.- Video3" << endl;
    cin >> respuesta;
    while (respuesta != 1 && respuesta != 2 && respuesta != 3) {
        cout << "Bienvenido al menu de Administrador" << "\n" << "Elija que secuencia de imagenes va a ser analizada" << "\n" << "1.- Video1" << "\n" << "2.- Video2" << "\n" << "3.- Video3" << endl;
        cin >> respuesta;
    }
    if (respuesta == 1) {
        imagesStr->push_back("Resources/Video1/image0292.png");
        imagesStr->push_back("Resources/Video1/image0293.png");
        imagesStr->push_back("Resources/Video1/image1679.png");
        imagesStr->push_back("Resources/Video1/image1680.png");
    }
    if (respuesta == 2) {
        imagesStr->push_back("Resources/Video2/image0292.png");
        imagesStr->push_back("Resources/Video2/image0293.png");
    }
    if (respuesta == 3) {
        imagesStr->push_back("Resources/Video3/image1679.png");
        imagesStr->push_back("Resources/Video3/image1680.png");
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
    vector<string>* pimagesStr=&imagesStr;

    Detector detector;
    Mat imagen;

    ABB.insert(0, 175); //SE AGREGA RAIZ PARA PODER DISTINGUIR LOS QUE ENTRAN Y SALEN

    //Se obtiene la hora de finalizacion del programa
    int HFin = timeinfo.tm_hour;
    int respuesta;
    cout << "Elija una de las opciones: " << "\n" << "1.- Guardia" << "\n" << "2.- Administrador"<< "\n" << "3.- Salir" << endl;
    cin >> respuesta;
    while (respuesta != 1 && respuesta != 2 && respuesta!=3) {
        cout << "Elija una de las dos opciones: " << "\n" << "1.- Guardia" << "\n" << "2.- Administrador"<< "\n" << "3.- Salir"<<endl;
        cin >> respuesta;
    }
    while (respuesta != 3) {
        if (respuesta == 1) {
            if (imagesStr.size() == 0) {
                cout << "No hay un video cargado" << endl;
            }
            else {
                MenuGuardia(ABB, imagesStr, HInicio, HFin);
            }
        }
        if (respuesta == 2) {
            MenuAdmin(pimagesStr);
        }
        //Se recorre el vector imageStr para cargar arbol binario
        for (string im : *pimagesStr) {
            imagen = imread(im);
            vector<Persona> found = detector.detect(imagen);
            for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
            {
                Persona& p = *i;
                ABB.insert(p.getXComienzo(), p.getXCentro());
            }
        }
        cout << "Elija una de las opciones: " << "\n" << "1.- Guardia" << "\n" << "2.- Administrador" << "\n" << "3.- Salir" << endl;
        cin >> respuesta;
    }
    return 0;
}
