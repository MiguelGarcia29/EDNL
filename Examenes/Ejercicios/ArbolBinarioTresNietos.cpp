// Enunciado: Un nodo verde es aquel nodo que cumple una cierta codici´on, por ejemplo
// en este caso, nuestra condici´on es aquel que tiene estrictamente 3 nietos.
// Es decir, vamos a devolver el n´umero de nodos que tienen 3 en el ´arbol.
#include "Arboles/aBinCelEnla.hpp"

template <typename T>
int nodosCon3Nietos(const Abin<T> &A)
{

    return nodosCon3Nietos(A, &a, A.raiz());
};

template <typename T>
int nodosCon3NietosRec(const Abin<T> &A, int &ctd, typename Abin<T>::nodo n)
{
    if (n == A.NODO_NULO)
        return 0;

    int n = 0;
    // MIRO QUE TENGA HIJO POR LA IZQ
    if (A.hijoIzqdo(n) != A.NODO_NULO)
    {
        // MIRO SI ESOS HIJOS TIENEN HIJOS (NIETOS DE n)
        if (A.hijoIzqdo(A.hijoIzqdo(n)) != A.NODO_NULO)
            n++;
        if (A.hijoDrcho(A.hijoIzqdo(n)) != A.NODO_NULO)
            n++;
    }
    // MIRO QUE TENGA HIJOS POR LA DERECHA
    if (A.hijoDrcho(n) != A.NODO_NULO)
    {
        // MIRO SI ESOS HIJOS TIENEN HIJOS (NIETOS DE n)
        if (A.hijoIzqdo(A.hijoDrcho(n)) != A.NODO_NULO)
            n++;
        if (A.hijoDrcho(A.hijoDrcho(n)) != A.NODO_NULO)
            n++;
    }
    if (n == 3)
        return 1 + nodosCon3NietosRec(A, ctd, A.hijoIzqdo(n)) + nodosCon3NietosRec(A, ctd, A.hijoDrcho(n));
    else
        return nodosCon3NietosRec(A, ctd, A.hijoIzqdo(n)) + nodosCon3NietosRec(A, ctd, A.hijoDrcho(n));
};
