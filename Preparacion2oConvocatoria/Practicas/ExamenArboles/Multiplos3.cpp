#include "../AGen/aGenCelEnLa.hpp"

template <typename T>
int numNodosArbol(const Agen<T> &A)
{

    if (!A.vacio())
    {
        return 1 +
    }

    return 0;
}

template <typename T>
int numNodosArbolRec(const Agen<T> &A, typename Agen<T>::nodo n)
{

    if (n == A.NODO_NULO)
        return 0;

    int numHijos = 0;
    typename Agen<T>::nodo hijo = A.hijoIzqdo(A, n);

    while (hijo != A.NODO_NULO)
    {
        numHijos += 1 + numNodosArbolRec(A, hijo);
        hijo = A.hermDrcho(hijo);
    }

    return numHijos;
}

template <typename T>
int hijosDeUnNodo(const Agen<T> &A, typename Agen<T>::nodo n)
{

    if (n == A.NODO_NULO)
        return 0;

    int numHijos = 0;
    typename Agen<T>::nodo hijo = A.hijoIzqdo(A, n);

    while (hijo != A.NODO_NULO)
    {
        numHijos++;
        hijo = A.hermDrcho(hijo);
    }

    return numHijos;
}

template <typename T>
int nodosConDescendenciaMultiplo3Rec(const Agen<T> &A, typename Agen<T>::nodo n)
{

    if (n == A.NODO_NULO)
        return 0;

    int numHijos = hijosDeUnNodo(A, n);
    typename Agen<T>::nodo hijo = A.hijoIzqdo(A, n);
    int descendientesMultiplos3 = numHijos % 3 == 0 ? 1 : 0;

    while (hijo != A.NODO_NULO)
    {
        descendientesMultiplos3 += nodosConDescendenciaMultiplo3Rec(A, hijo);
        hijo = A.hermDrcho(hijo);
    }

    return descendientesMultiplos3;
}

template <typename T>
double porcentajeDescendientesMultiplos3(const Agen<T> &A)
{

    return nodosConDescendenciaMultiplo3Rec(A,A.raiz())*100/numNodosArbol(A);
}