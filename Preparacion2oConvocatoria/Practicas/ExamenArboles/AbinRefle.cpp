#include "Abin/aBinCelEnla.hpp"

//COMPROBAR QUE SEA REFLEJADO
template <typename T>
bool AbinReflRec(const Abin<T> &A, typename Abin<T>::nodo nA, const Abin<T> &B, typename Abin<T>::nodo nB)
{

    if (nA == A.NODO_NULO && nB == B.NODO_NULO)
        return true;
    else if (nA == A.NODO_NULO && nB != A.NODO_NULO)
        return false;
    else if (nB == A.NODO_NULO && nA != A.NODO_NULO)
        return false;


    return AbinReflRec(A,A.hijoIzqdo(nA),B,B.hijoDrcho(nB)) && AbinReflRec(A,A.hijoDrcho(nA),B,B.hijoIzqdo(nB));
}


template <typename T>
bool AbinRefl(const Abin<T> &A, const Abin<T> &B)
{
    return AbinReflRec(A,A.raiz(),B,B.raiz()) && AbinReflRec(A,A.raiz(),B,B.raiz());
}


//CONSTRUIR REFLEJADO
template <typename T>
void ConstAbinReflRec(const Abin<T> &A, typename Abin<T>::nodo nA,  Abin<T> &B, typename Abin<T>::nodo nB)
{
    if(nA!=A.NODO_NULO){

        if(A.hijoIzqdo(nA)!=A.NODO_NULO){
            B.insertarHijoDrcho(nB,A.elemento(nA));
            ConstAbinReflRec(A,A.hijoIzqdo(nA),B,B.hijoDrcho(nB));
        }
        if(A.hijoDrcho(nA)!=A.NODO_NULO){
            B.insertarHijoIzqdo(nB,A.elemento(nA));
            ConstAbinReflRec(A,A.hijoDrcho(nA),B,B.hijoIzqdo(nB));
        }
    }
};

template <typename T>
Abin<T> ConstAbinRefl(const Abin<T> &A)
{
    Abin<T> B;
    if(!A.vacio()){
        B.insertarRaiz(A.elemento(A.raiz()));
        ConstAbinReflRec(A,A.raiz(),B,B.raiz());
    }
    
    return B;
}