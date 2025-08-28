//Enunciado: Calcular densidad de un ´arbol. La densidad se define como el Grado
//m´aximo de un ´arbol partido del n´umero de nodos hojas.


#include "Arboles/aGenCelEnLa.hpp"

template <typename T>
int grado_rec(const Agen<T>&A,typename Agen<T>::nodo n){

    int numHijos = 1;
    int gradoMaxHijo = 0;

    if(n==A.NODO_NULO){
        return numHijos;
    }

    typename Agen<T>::nodo hijo=A.hijoIzqdo(n);

    while(hijo!=A.NODO_NULO){
        numHijos++;

        if(A.hijoIzqdo(hijo)!=A.NODO_NULO)
            gradoMaxHijo = grado_rec(A,A.hijoIzqdo(A));

        hijo = A.hermDrcho(hijo);

    }

    return std::max(numHijos,gradoMaxHijo);

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
double densidadArbol(const Agen<T> &A){

    size_t t =DescendientesTotales(A.raiz(),A);
    size_t grado = grado_rec(A,A.raiz());

    return (t/grado);

}

