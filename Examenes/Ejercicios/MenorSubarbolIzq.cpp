#include "Arboles/aBinCelEnla.hpp"

template <typename T>
bool menorSubarbol(const Abin<T> &a)
{
    return menorSubarbolRec(a, a.raiz());
}

template <typename T>
bool menorSubarbolRec(const Abin<T> &A, typename Abin<T>::nodo n)
{

    if (n == A.NODO_NULO)
        return true;

    // SI TIENE DOS HIJOS
    if (A.hijoIzqdo(n) != A.NODO_NULO && A.hijoDrcho(n) != A.NODO_NULO)
    {
        // MIRO QUE ESTEN ORDENADOS
        if (A.elemento(A.hijoIzqdo(n)) < A.elemento(n) < A.elemento(A.hijoDrcho(n)))
            return menorSubarbolRec(A, A.hijoIzqdo(n)) &&
                   menorSubarbolRec(A, A.hijoDrcho(n));
        else
            return false
    }
    // SI SOLO TIENE UN HIJO
    else
    {
        // ES EL HIJO IZQ
        if (A.hijoIzqdo(n) != A.NODO_NULO && A.hijoDrcho(n) == A.NODO_NULO)
        {
            if(A.elemento(A.hijoIzqdo(n))<A.elemento(n))
                return menorSubarbolRec(A, A.hijoIzqdo(n))
            else
                return false;
        }
        // ES EL HIJO DERECHO
        else if (A.hijoIzqdo(n) == A.NODO_NULO && A.hijoDrcho(n) != A.NODO_NULO)
        {
            if(A.elemento(A.elemento(n)<A.hijoDrcho(n)))
                return menorSubarbolRec(A, A.hijoDrcho(n))
            else
                return false;
        }
        // NO TIENE HIJOS
        else
            return true;
    }
}