// PARA QUE SEA AVL TIENE QUE SER ABB hijoIz<e<hijoDer
// TIENE QUE ESTAR BALANCEADO (LA DIFERENCIA DE ALTURA DE LAS SUBRAMAS DEBE SER -1,0 o 1)

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
            if (A.elemento(A.hijoIzqdo(n)) < A.elemento(n))
                return menorSubarbolRec(A, A.hijoIzqdo(n)) else return false;
        }
        // ES EL HIJO DERECHO
        else if (A.hijoIzqdo(n) == A.NODO_NULO && A.hijoDrcho(n) != A.NODO_NULO)
        {
            if (A.elemento(A.elemento(n) < A.hijoDrcho(n)))
                return menorSubarbolRec(A, A.hijoDrcho(n)) else return false;
        }
        // NO TIENE HIJOS
        else
            return true;
    }
}

template <typename T>
bool balenceado(const Abin<T> &a)
{

    int b = balenceadoRec(a, a.raiz());

    return !(b>1);
}

template <typename T>
int balenceadoRec(const Abin<T> &A, typename Abin<T>::nodo n)
{

    if(n==A.NODO_NULO)
        return -1;

    return max(abs(alturaNodo(A,A.hijoIzqdo(n))-alturaNodo(A,A.hijoDrcho(n))),
            max(balenceadoRec(A,A.hijoIzqdo(n)),balenceadoRec(A,A.hijoDrcho(n))));

}

template <typename T>
int alturaNodo(const Abin<T> &A, typename Abin<T>::nodo n){

    if(n==A.NODO_NULO)
        return -1;

    return 1 + max(alturaNodo(A,A.hijoIzq(n)),alturaNodo(A,A.hijoDrcho(n)))

}

template <typename T>
bool esAvl(const Abin<T> &A){
    return balenceado(A)&&menorSubarbol(A);
}

