#include "Arboles/aBinCelEnla.hpp"

template <typename T>
void hundir(Abin<T> &A, typename Abin<T>::nodo n)
{

    if (n != A.NODO_NULO)
    {
        // EL NODO ES HOJA
        if (A.hijoIzqdo(n) == A.NODO_NULO &&
            A.hijoDrcho(n) == A.NODO_NULO)
        {
            // VEO SI ES EL IZQ
            if (A.hijoIzqdo(A.padre(n)) == n)
                A.eliminarHijoIzqdo(A.padre(n));
            // O EL DERECHO
            else
                A.eliminarHijoDrcho(A.padre(n));
        }
        else
        {

            if (A.hijoIzqdo(n) != A.NODO_NULO &&
                A.elemento(n) > A.elemento(A.hijoIzqdo(n)))
            {
                T aux = A.elemento(n);
                A.elemento(n) = A.elemento(A.hijoIzqdo(n));
                A.elemento(A.hijoIzqdo(n)) = aux;
                hundir(A, A.hijoIzqdo(n));
            }
            else if (A.hijoDrcho(n) != A.NODO_NULO &&
                     A.elemento(n) > A.elemento(A.hijoDrcho(n)))
            {
                T aux = A.elemento(n);
                A.elemento(n) = A.elemento(A.hijoDrcho(n));
                A.elemento(A.hijoDrcho(n)) = aux;
                hundir(A, A.hijoDrcho(n));
            }
        }
    }
};