/*. Para un árbol binario B, podemos construir el árbol binario reflejado BR cambiando los
subárboles izquierdo y derecho en cada nodo. Implementa un subprograma que devuelva
el árbol binario reflejado de uno dado.*/

#include <iostream>
#include <fstream>
#include "../Abin/aBinCelEnla.hpp"
#include "../Abin/abin_E-S.h"

template <typename T>
Abin<T> reflejado(const Abin<T> &A)
{

    Abin<T> t;

    t.insertarRaiz(A.elemento(A.raiz()));

    return t;
}

template <typename T>
void reflejar(const Abin<T> &R, const Abin<T> &A, typename Abin<T>::nodo nR, typename Abin<T>::nodo nA)
{
    if (nA == A.NODO_NULO)
        return;

    if (A.hijoIzqdo(nA) != A.NODO_NULO)
    {
        R.insertarHijoDrcho(nR, A.elemento(nA));
        reflejar(R, A, R.hijoDrcho(nR), A.hijoIzqdo(nA));
    }
    if (A.hijoDrcho(nA) != A.NODO_NULO)
    {
        R.insertarHijoIzqdo(nR, A.elemento(nA));
        reflejar(R, A, R.hijoIzqdo(nR), A.hijoDrcho(nA));
    }
}


