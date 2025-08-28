#include "aGenLista.hpp"
#include "agen_E-S.h"
#include <iostream>

template <typename T>
int alturaNodoRec(const Agen<T> &A, typename Agen<T>::nodo n)
{
    if (n == A.NODO_NULO)
        return 0;

    int altura = 0;

    if (A.hijoIzqdo(n) != A.NODO_NULO)
    {
        altura += 1 + alturaNodoRec(A, A.hijoIzqdo(n));
    }

    typename Agen<T>::nodo hermano = A.hermDrcho(n);
    while (hermano != A.NODO_NULO)
    {
        if(A.hijoIzqdo(hermano!=A.NODO_NULO)){
            altura = std::max(altura,1+alturaNodoRec(A,A.hijoIzqdo(hermano)));
        }

         hermano = A.hermDrcho(hermano);
    }


    return altura;
}