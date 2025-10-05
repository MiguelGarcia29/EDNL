#include "../Abin/aBinCelEnla.hpp"

template <typename T>
bool esABBRec(const Abin<T> &A, typename Abin<T>::nodo &nA){

    if (nA==A.NODO_NULO)
        return true;


    if(A.hijoIzqdo(nA)!=A.NODO_NULO){
        if(A.elemento(nA)<A.elemento(A.hijoIzqdo(nA)))
            return false;
    }

     if(A.hijoDrcho(nA)!=A.NODO_NULO){
        if(A.elemento(nA)>A.elemento(A.hijoDrcho(nA)))
            return false;
    }

    return esABB(A,A.hijoIzqdo(nA)) && esABB(A,A.hijoDrcho(nA));

}

template <typename T>
bool esABB(const Abin<T> &A){

    return esABBRec(A,A.raiz());
    
}