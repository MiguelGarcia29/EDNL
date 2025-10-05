#include "../AGen/aGenCelEnLa.hpp"

template <typename T>
int numHijos(const Agen<T> &A, typename Agen<T>::nodo nA)
{
    if (nA == A.NODO_NULO)
        return 0;

    int numHijos = 0;

    typename Agen<T>::nodo hijos = A.hijoIzqdo(nA);
    while (hijos != A.NODO_NULO)
    {
        numHijos++;
        hijos = A.hermDrcho(hijos);
    }

    return numHijos;
}

template <typename T>
bool SimilarRec(const Agen<T> &A, typename Agen<T>::nodo nA, const Agen<T> &B, typename Agen<T>::nodo nB)
{
    if (nA == A.NODO_NULO && nB == A.NODO_NULO)
        return true;
    else if (nA == A.NODO_NULO &&nB != B.NODO_NULO ||
                 nB = B.NODO_NULO && nA != A.NODO_NULO)
        return false;

    if (numHijos(A, nA) != numHijos(B, nB))
        return false;

    else
    {
        if (numHijos(A, nA) == 0)
        {
            return A.elemento(nA) == B.elemento(nB);
        }
        else
        {
            typename Agen<T>::nodo hijoA = A.hijoIzqdo(nA);
            typename Agen<T>::nodo hijoB = B.hijoIzqdo(nB);

            bool valor = true;

            while(hijoA!=A.NODO_NULO && hijoB!=B.NODO_NULO && valor){
                valor &= SimilarRec(A,hijoA,B,hijoB);
                hijoA = A.hermDrcho(nA);
                hijoB = B.hermDrcho(nB);
            }

            return valor;

        }
    }
}

template <typename T>
bool Similar(const Agen<T> &A,  const Agen<T> &B){

    return SimilarRec(A,A.raiz(),B,B.raiz());

}