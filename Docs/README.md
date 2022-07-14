![Logo UCN](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/60x60-ucn-negro.png)


# Informe Técnico

## Curso: Estructura de datos

### Detección y reidentificación de cuerpos en secuencias de imágenes o vídeo
### Alumnos:
 - Camilo Clift Silva (Coordinador)
 - Ignacio Herrera Letelier (Bitácora)

## Resumen

> Se requiere implementar un sistema de detección corporal en una imagen o video, haciendo uso de un algoritmo computacional y una biblioteca libre de visión artificial.
> 
> Se requiere destacar o resaltar con una marca (rectángulo rojo) en la imagen, todas los cuerpos que aparecen en ella.
> 
> Se instala un entorno de desarrollo integrado compatible con múltiples lenguajes de programación, tales como C++, C#.
> 
> A su vez se instala una biblioteca libre de visión artificial con múltiples herramientas de detección de patrones visuales (OpenCV) compatible con el entorno de desarrollo y con el lenguaje de programación que se va a usar (C++).
> 
> Se configura el entorno de desarrollo integrado Visual Studio para utilizar en él la biblioteca de visión artificial.
>
> Se configura la biblioteca OpenCV en el entorno de desarrollo integrado (Visual Studio).
>
> Se crea un arbol binario donde se guardaran los nodos de datos.
> 
> Se crea un sistema que detecta y destaca en un rectángulo rojo todas los cuerpos humanos visibles en una imagen de formato .jpg .
> 
> Se crea un sistema que analiza cuantas personas entran y salen de una zona específica.

![Resultados](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/Resultado1.PNG)
## 1. Introducción

### 1.1 Descripción del problema
Se solicita un programa de sistema de vigilancia basado en conteo de personas. En este se deberá tener en cuenta cuantas veces una determinada persona atraviesa una zona designada por hora. 

### 1.2 Objetivos
**Objetivo General**

Construir un sistema de vigilancia de tráfico peatonal, el cuál a través de visión por computadora o artificial recopile y maneje datos.

**Objetivos Específicos**

1. Adquirir e instalar Software necesario para el desarrollo del sistema.
2. Recopilar información a través del análisis de las imágenes.
3. Analizar cuantas personas entran a una zona especifica.
4. Analizar cuantas personas salen de una zona especifica.
5. Procesar y desplegar la información requerida por el usuario.
6. Creación de un menú.
 

### 1.3 Solución Propuesta
Se creará un programa el cual ocupando la biblioteca de visión artificial OpenCV reconozca las diferentes personas que pasen frente a la camara. Se guardara la data (número de reconocimiento) de cada persona y cuando se finalice el video grabado desplegara una lista ordenada de mayor a menor con el número de reconocimiento y los intervalos de tiempo en el cual aparece la persona.

## 2. Materiales y métodos

### 2.1 Instalación

Se instala Visual Studio, un entorno de desarrollo integrado en el cuál se puede crear y desarrollar softwares como aplicaciones web y móviles, sitios o servicios web. Su primera versión es de 1997, por lo que ha pasado por varias revisiones en más de dos décadas que le han dado mayor solidez y estabilidad.

En Visual Studio se puede:
- Crear softwares y programas relativos al universo web, como es el caso de aplicaciones o móvil, incluso instrimentos de big data y analítica.
- Editar, depurar y compilar código para posteriormente publicar una aplicación. Se puede ahorrar mucho esfuerzo en el desarrollo de tareas antes engorrosas y se puede ejecutar todas las fases de creación de un programa.
- Reducir esfuerzo en actividades rutinarias y mejorar la eficiencia de las tareas esenciales de los desarrolladores.
- Instalar integraciones y extensiones relacionadas con Machine Learning o Github.
- Desarrollar extensiones propias. 
- En este caso no ocuparemos CMake
También se requiere OpenCV, ésta es una biblioteca de código abierto que es muy útil para aplicaciones de visión por computadora, como análisis de video, análisis de secuencias de CCTV y análisis de imágenes. OpenCV está escrito por C ++ y tiene más de 2500 algoritmos optimizados. Cuando se crea aplicaciones para la visión por computadora que no se quiere crear desde cero, se puede usar esta biblioteca para comenzar a enfocarse en problemas del mundo real. Hay muchas empresas que utilizan esta biblioteca en la actualidad, como Google, Amazon, Microsoft y Toyota. Contribuyen muchos investigadores y desarrolladores. Se puede instalar fácilmente en cualquier SO como Windows, Ubuntu y MacOS.

### 2.2 Diseño

Se usará una Lista Enlazada (LinkedList) la cual guardará los datos de las personas en el video (ID de personas).

![DIAGRAMA CLASE](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/Diseño1.PNG)

### 2.3 Implementación
Como detector corporal, se utiliza la función de OpenCV HOGDescriptor, y se configura en Visual Studio en el lenguaje C++.

Se carga HOGDescriptor:

```
    private:
      enum Mode { Default, Daimler } m;
      HOGDescriptor hog, hog_d;
    public:
      Detector() : m(Default), hog(), hog_d(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9) {
        hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
        hog_d.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
```
Se itera por las personas detectadas y se destacan con un rectangulo rojo:

```
    for (vector<Persona>::iterator i = found.begin(); i != found.end(); ++i)
    {
        Persona& p = *i;
        cout << "(" << p.getXComienzo() << ", " << p.getYComienzo() << ")" << endl;
        //detector.adjustRect(r);
        rectangle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), cv::Point(p.getXFin(), p.getYFin()), cv::Scalar(0, 255, 0), 2);
        circle(imagen, cv::Point(p.getXCentro(), p.getYCentro()), 3, cv::Scalar(0, 0, 255), 3);
        circle(imagen, cv::Point(p.getXComienzo(), p.getYComienzo()), 3, cv::Scalar(255, 0, 255), 2);
        circle(imagen, cv::Point(p.getXFin(), p.getYFin()), 3, cv::Scalar(0, 255, 255), 2);
    }
```
Se despliega la imagen:
```
       imshow("People detector", imagen);
       waitKey(0);
```
## 3. Resultados Obtenidos
![Resultados](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/Resultado1.PNG)
![Resultados](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/Resultado2.PNG)
![Resultados](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/Resultado3.PNG)

## 4. Conclusiones
Con la ayuda de la biblioteca de visión artificial llamada OpenCV, se logró crear un sistema de detección de peatones, las cuales se enmarcan con un rectangulo rojo, a su vez con ayuda de listas enlazadas (Linked List), se pudó realizar conteo de personas, pero no se logro diferenciar a los peatones. Por otro lado, apredimos a utilizar de mejor manera Visual Studio y los lenguajes tanto de C como C++.

## Anexos

### Anexo A: Instalación librerías OpenCV

Se hace ingreso a la página web https://opencv.org en la cual se debe dirigir a la sección de Library y seleccionar la opción de releases en la cual se hace la descarga del instalador de OpenCV version 4.6.0
![OpenCV](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/OpenCV.png)

Luego de la instalación por el instalador descargado anteriormente se debe añadir a las Variables de entorno del pc en PATH la dirección de opencv\build\x64\vc15\bin y opencv\build\x64\vc15\lib la agregamos en la sección de C/C++, que correspondera a la carpeta "include" dentro de OpenCV, a continuación en la sección "Vinculador", agregamos el directorio donde se encuentra la libreria de OpenCV, finalmente hacemos lo mismo, pero en el apartado "Entrada", con esto OpenCV ya esta configurado para nuestro proyecto.
![VariablesEntorno](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/OpenCv1.png)
![VariablesEntorno](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/OpenCV2.png)
![VariablesEntorno](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/OpenCV3.png)

### Anexo B: Instalación de IDE y configuración librerías OpenCV
Se hace ingreso a la página web del IDE Visual Studio https://visualstudio.microsoft.com/es/ donde se hizo descarga de Visual Studio Community 2022 
![WebVisualStudio](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/VisualPagina.png)
Luego de la instalación de Visual Studio se debera descargar la extensión de Desarrollo para escritorio con C++
![C++](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/CVisual.png)
Cuando se tenga la extensión se debera cambiar la disposición del IDE para trabajar con 64 bits y hacerlo compatible con el OpenCV, finalmente se debera incluir los archivos de la biblioteca OpenCV en el proyecto
![VisualStudio](https://github.com/Ignacio07/ED22-01-Herrera-Clift/blob/main/Docs/Images/x64.PNG)

## Referencia

BoostMyTool. (01/01/2022). Youtube. Recuperado 15 de Junio de 2022, de https://www.youtube.com/watch?v=unSce_GPwto&lc=z23adnkzmkfucje4p04t1aokg3ksytasstznr4hhw3sirk0h00410
