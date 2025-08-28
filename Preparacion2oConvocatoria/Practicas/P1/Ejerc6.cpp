//6. Implementa un subprograma que determine el nivel de desequilibrio de un árbol binario, 
//definido como el máximo desequilibrio de todos sus nodos. El desequilibrio de un nodo se 
//define como la diferencia entre las alturas de los subárboles del mismo

#include <iostream>
#include <fstream> 
#include "../Abin/aBinCelEnla.hpp" 
#include "../Abin/abin_E-S.h"  

template <typename T>
int alturaArbolRec(const Abin<T>& A, typename Abin<T>::nodo n){

    if(n==A.NODO_NULO)
        return -1;
    
    return 1 + std::max(alturaArbol(A,A.hijoIzqdo(n)),alturaArbol(A,A.hijoDrcho(n)));

}


template <typename T>
int equilibrio(const Abin<T>& A, typename Abin<T>::nodo n){

    if(n==A.NODO_NULO)
        return -1;

    return std::max(std::abs(alturaArbolRec(A.hijoIzqdo(n))-alturaArbolRec(A.hijoDrcho(n))),
            std::max(equilibrio(A,A.hijoIzqdo(n),equilibrio(A,A.hijoDrcho(n)))));

}