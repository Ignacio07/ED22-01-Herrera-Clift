#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;


#include "Detector.hpp"

void Detector::toggleMode() { m = (m == Default ? Daimler : Default); }

string Detector::modeName() const { return (m == Default ? "Default" : "Daimler"); }

vector<Persona> Detector::detect(InputArray img) {
    // Se ejectuta el Detector con los parametros pre establecidos, para obtener resultados mas existosos.
    vector<Rect> found;
    if (m == Default)
        hog.detectMultiScale(img, found, 0, Size(2, 2), Size(4, 4), 1.05, 2, false);
    else if (m == Daimler)
        hog_d.detectMultiScale(img, found, 1, Size(2, 2), Size(4, 4), 1.05, 3, true);

    // Convertir un objeto Rect a un objeto persona.
    vector<Persona> personas;

    for (vector<Rect>::iterator i = found.begin(); i != found.end(); ++i) {
        Rect& r = *i;
        Persona p(r);
        personas.push_back(p);
    }

    return personas;
}

void Detector::adjustRect(Rect& r) const {
    // El HOG detector retorna un rectangulo un poco mas grande que el objeto real,
    // asi que ajustamos el rectangulo para que se vea mejor.
    r.x += cvRound(r.width * 0.1);
    r.width = cvRound(r.width * 0.8);
    r.y += cvRound(r.height * 0.07);
    r.height = cvRound(r.height * 0.8);
}
