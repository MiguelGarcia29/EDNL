// Implementa un subprograma que determine si un árbol binario es o no pseudocompleto.
// En este problema entenderemos que un árbol es pseudocompleto, si en el penúltimo nivel
// del mismo cada uno de los nodos tiene dos hijos o ninguno.

#include <iostream>
#include <fstream>
#include "../Abin/aBinCelEnla.hpp"
#include "../Abin/abin_E-S.h"

template <typename T>
int alturaArbolRec(const Abin<T> &A, typename Abin<T>::nodo n)
{

    if (n == A.NODO_NULO)
        return -1;

    return 1 + std::max(alturaArbol(A, A.hijoIzqdo(n)), alturaArbol(A, A.hijoDrcho(n)));
}

template <typename T>
int alturaArbol(const Abin<T> &A)
{
    return alturaArbolRec(A, A.raiz());
}

template <typename T>
int prof(const Abin<T> &A, typename Abin<T>::nodo n)
{

    int profundidad = 0;
    while (n != A.raiz())
    {
        prof++;
        n = A.padre(n);
    }

    return prof;
}

template <typename T>
bool tieneUnHijo(const Abin<T> &A, typename Abin<T>::nodo n){
    if(A.hijoIzqdo(n)==A.NODO_NULO&&A.hijoDrcho(n)!=A.NODO_NULO)
        return true;
    else if (A.hijoIzqdo(n)!=A.NODO_NULO&&A.hijoDrcho(n)==A.NODO_NULO)
        return true;
    else
        return false;
}

template <typename T>
bool pseudocompleto(const Abin<T> &A, typename Abin<T>::nodo n)
{
    if (N == A.NODO_NULO)
        return true;

    if (alturaArbol(A) - prof(A, n) != 1)
    {
        return pseudocompleto(A,A.hijoIzqdo(n)) && pseudocompleto(A,A.hijoDrcho(n));   
    }
    else{
        return !tieneUnHijo(A,n);
    }
}