// Enunciado: Implementa un subprograma que devuelva el porcentaje de descendientes
// propios de un ´arbol general que sean m´ultiplos de 3.
#include "Arboles/aGenCelEnLa.hpp"

template <typename T>
size_t DescendientesMultiplo3(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == A.NODO_NULO)
        return 0;

    int descendientesMultiplo3 = 0;
    int numHijos = 0;

    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);

    while (hijo != A.NODO_NULO)
    {

        numHijos++;
        if (A.hijoIzqdo(hijo) != A.NODO_NULO)
            descendientesMultiplo3 += DescendientesMultiplo3(A.hijoIzqdo(hijo), A);

        hijo = A.hermDrcho(hijo);
    }

    if (numHijos % 3 == 0)
    {
        descendientesMultiplo3++;
    }

    return descendientesMultiplo3;
}

template <typename T>
size_t DescendientesTotales(typename Agen<T>::nodo n, const Agen<T> &A)
{
    if (n == A.NODO_NULO)
        return 0;

    int numHijos = 0;

    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);

    while (hijo != A.NODO_NULO)
    {

        numHijos++;
        if (A.hijoIzqdo(hijo) != A.NODO_NULO)
            numHijos += DescendientesTotales(A.hijoIzqdo(hijo), A);

        hijo = A.hermDrcho(hijo);
    }

    return hijo;
}

template <typename T>
double porcentajeMultiplos3(const Agen<T> &A)
{
    size_t totales = DescendientesTotales(A, A.raiz());
    size_t de3 = DescendientesMultiplo3(A, A.raiz());

    if (totales == 0)
        return 0;

    return (de3 * 100.0) / totales;
}