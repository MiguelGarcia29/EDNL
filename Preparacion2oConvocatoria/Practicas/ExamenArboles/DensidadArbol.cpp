#include "../AGen/aGenCelEnLa.hpp"

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
int gradoMaxArbolRec(const Agen<T> &A, typename Agen<T>::nodo n)
{

    if (n == A.NODO_NULO)
        return 0;

    int numHijos = hijosDeUnNodo(A, n);
    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);

    while (hijo != A.NODO_NULO)
    {
        numHijos = std::max(numHijos, gradoMaxArbolRec(A, hijo));
        hijo = A.hermDrcho(A, n);
    }

    return numHijos;
}

template <typename T>
int nodosHojas(const Agen<T> &A, typename Agen<T>::nodo n)
{
    if (n == A.NODO_NULO)
        return 0;

    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
    if (hijo == A.NODO_NULO)
        return 1;
    else{
        int hojas = 0;
        while(hijo!=A.NODO_NULO){
            hojas += nodosHojas(A,hijo);
            hijo = A.hermDrcho(A,hijo);
        }

        return hojas;
    }
}

template <typename T>
double densidad(const Agen<T> &A){
    return gradoMaxArbolRec(A,A.raiz())/nodosHojas(A,A.raiz());
}