#ifndef UCN_TALLER_EDATOS_2021_1_BINARYSEARCHTREE_H
#define UCN_TALLER_EDATOS_2021_1_BINARYSEARCHTREE_H

class ABB {

public:

    ABB() {
        root = nullptr;
    }

    struct Nodo* root;

    Nodo* insert(Nodo* node, int coordenadaIncio,int centroide);

    void LimpiarMemoria();

    void insert(int coordenadaInicio,int centroide);

    int Entran();

    int Salen();

    ~ABB(void);

};
#endif
