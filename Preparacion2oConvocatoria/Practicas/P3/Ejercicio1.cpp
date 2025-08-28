#include "aGenLista.hpp"
#include "agen_E-S.h"
#include <iostream>

template <typename T>
int gradoAgen(const Agen<T> &A)
{

    int gradoMax = 1;
    gradoAgenRec(A, A.raiz(), gradoMax);
    return gradoMax;
}

template <typename T>
void gradoAgenRec(const Agen<T> &A, typename Agen<T>::nodo n, int &gradoMax)
{

    if (n == A.NODO_NULO)
        return;

    int grado = 1;

    typename Agen<T>::nodo hermano = A.hermDrcho(n);

    while (hermano != A.NODO_NULO)
    {
        grado++;
        gradoAgenRec(A, A.hijoIzqdo(hermano), gradoMax);
        hermano = A.hermDrcho(hermano);
    }

    gradoAgenRec(A, A.hermanoIzqdo(n), gradoMax);

    gradoMax = std::max(grado, gradoMax);
}