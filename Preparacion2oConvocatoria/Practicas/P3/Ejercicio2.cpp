#include "aGenLista.hpp"
#include "agen_E-S.h"
#include <iostream>

template <typename T>
int gradoNodo(const Agen<T> &A, typename Agen<T>::nodo & n){

    int grado = 0;

    if(n==A.NODO_NULO)
        return -1;

    while(n!=A.raiz()){
        grado ++;
        n = A.padre(n);
    }

    return grado;

}