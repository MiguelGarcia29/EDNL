// Enunciado: A partir de un ´arbol binario, creamos otro intercambiando los sub´arboles del mismo.

#include "Arboles/aBinCelEnla.hpp"

template <typename T>
Abin<T> reflejar(const Abin<T> &A)
{
    Abin<T> reflejado;
    if (!A.vacio())
    {
        reflejado.insertarRaiz(A.elemento(A.raiz()));

        reflejar(A, reflejado, A.raiz(), reflejado.raiz())
    }
    return reflejado;
}

template <typename T>
void reflejarRec(const Abin<T> &A, Abin<T> &R,
                 typename Abin<T>::nodo nA,
                 typename Abin<T>::nodo nR)
{

    if (nA != A.NODO_NULO)
    {
        if (A.hijoIzqdo(nA) != A.NODO_NULO)
        {
            R.insertarHijoDrcho(nR, A.elemento(A.hijoIzqdo(nA)));
            reflejarRec(A, R, A.hijoIzqdo(nA), R.hijoDrcho(nR));
        }

        if (A.hijoDrcho(nA) != A.NODO_NULO)
        {
            R.insertarHijoIzqdo(nR, A.elemento(A.hijoDrcho(nA)));
            reflejarRec(A, R, A.hijoDrcho(nA), R.hijoIzqdo(nR);)
        }
    }
}