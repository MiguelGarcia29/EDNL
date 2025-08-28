#include "../Arboles/aBinCelEnla.hpp"

template <typename T>
void podar(Abin<T> &A, typename Abin<T>::nodo n)
{

    podaRec(A, n);

    if(A.raiz()==n)
        A.eliminarRaiz();
    else if(A.hijoIzqdo(A.padre(n))==n)
        A.eliminarHijoIzqdo(A.padre(n));
    else
        A.eliminarHijoDrcho(A.padre(n));
}

template <typename T>
void podarRec(Abin<T> &A, typename Abin<T>::nodo n) {

    if(n!=A.NODO_NULO){
        podarRec(A,A.hijoIzqdo(n));
        podarRec(A,A.hijoDrcho(n));

        if(A.hijoIzqdo(n)!=A.NODO_NULO){
            A.eliminarHijoIzqdo(n);
        }
        if(A.hijoDrcho(n)!=A.NODO_NULO){
            A.eliminarHijoDrcho(n);
        }
    }

}