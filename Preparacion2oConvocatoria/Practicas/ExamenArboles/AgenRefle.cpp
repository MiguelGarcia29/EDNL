#include "AGen/aGenCelEnLa.hpp"

template <typename T>
void arbolRefleRec(const Agen<T> &A, typename Agen<T>::nodo nA, Agen<T> &B, typename Agen<T>::nodo nB)
{

    if (nA == A.NODO_NULO)
        return;

    typename Agen<T>::nodo hijos = A.hijoIzqdo(nA);
    while (hijos != A.NODO_NULO)
    {
        B.insertarHijoIzqdo(nB, A.elemento(hijos));
        arbolRefleRec(A, hijos, B, B.hijoIzqdo(nB));

        hijos = A.hermDrcho(nB);
    }
}


template <typename T>
Agen<T> arbolRefleRec(const Agen<T> &A)
{

    Agen<T> B;
    if (!A.vacio()){
        B.insertarRaiz(A.elemento(A.raiz()));
        arbolRefleRec(A,A.raiz(),B,B.raiz());
    }

    return B;
        
}