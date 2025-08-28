#include "Arboles/aGenCelEnLa.hpp"

template <typename T>
Agen<T> reflejar(const Agen<T> &A)
{
    Agen<T> reflejado;

    if (!A.vacio())
    {
        reflejado.insertarRaiz(A.elemento(A.raiz()));
        reflejarRec(A, reflejado, A.raiz(), reflejado.raiz());
    }

    return reflejado;
}

template <typename T>
void reflejarRec(const Agen<T> &A, Agen<T> &R,
                 typename Agen<T>::nodo nA,
                 typename Agen<T>::nodo nR)
{
    if (nA != A.NODO_NULO)
    {

        typename Agen<T>::nodo aux = A.hijoIzqdo(nA);

        while (aux != A.NODO_NULO)
        {
            R.insertarHijoIzqdo(nR, A.elemento(aux));
            reflejarRec(A, R, aux, R.hijoIzqdo(nR));
            aux = A.hermDrcho(aux);
        }
    }
}