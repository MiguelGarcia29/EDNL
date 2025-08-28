/*Dos árboles binarios son similares cuando tienen idéntica estructura de ramificación, 
es  decir,  ambos  son  vacíos,  o  en  caso  contrario,  tienen  subárboles  izquierdo  y  derecho 
similares.  Implementa  un  subprograma  que  determine  si  dos  árboles  binarios  son 
similares. */

#include <iostream>
#include <fstream> 
#include "../Abin/aBinCelEnla.hpp" 
#include "../Abin/abin_E-S.h"  

template <typename T>
bool mismaEstructura(const Abin<T> &A,const Abin<T> &B, typename Abin<T>::nodo nA,typename Abin<T>::nodo nB){


    if(nA==A.NODO_NULO&&nB==B.NODO_NULO){
        return true;
    }
    else if(nA==A.NODO_NULO||nB==B.NODO_NULO){
        return false;
    }

    return mismaEstructura(A,B,A.hijoIzqdo(nA),B.hijoIzqdo(nB)) && mismaEstructura(A,B,A.hijoDrcho(nA),B.hijoDrcho(nB)) 


}