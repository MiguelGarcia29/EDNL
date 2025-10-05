#include "../Abin/aBinCelEnla.hpp"
#include "../Grafos/colaenla.h"

template <typename T>
bool hijosMayores(const Abin<T> &A)
{

    return hijosMayoresRec(A, A.raiz());
}

template <typename T>
bool hijosMayoresRec(const Abin<T> &A, typename Abin<T>::nodo n)
{

    if (n == A.NODO_NULO)
        return true;

    if (A.hijoIzqdo(n) != A.NODO_NULO)
    {
        if (A.elemento(n) > A.elemento(A.hijoIzqdo(n)))
            return false;
    }

    if (A.hijoDrcho(n) != A.NODO_NULO)
    {
        if (A.elemento(n) > A.elemento(A.hijoDrcho(n)))
            return false;
    }

    return hijosMayoresRec(A, A.hijoIzqdo(n)) && hijosMayoresRec(A, A.hijoDrcho(n));
};

template <typename T>
bool esCompleto(const Abin<T> &A)
{

    Cola c;
    bool nuloPrevio = false;
    c.push(A.raiz());

    typename Abin<T>::nodo actual;

    do
    {
        if (!c.vacia())
        {
            actual = c.frente();
            c.pop();
        }

        if (actual == A.NODO_NULO && !nuloPrevio)
        {
            nuloPrevio = true;
        }

        if (actual != A.NODO_NULO && nuloPrevio)
        {
            return false;
        }
        
        if (actual != A.NODO_NULO)
        {
            c.push(A.hijoIzqdo(actual));
            c.push(A.hijoDrcho(actual));
        }

    } while (!c.vacia());

    return true;
}

template <typename T>
bool esAPO(const Abin<T> &A)
{
    return esCompleto(A) && hijosMayores(A);
}