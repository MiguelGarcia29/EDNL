#include <iostream>
#include <fstream> 
#include "../Abin/aBinCelEnla.hpp" 
#include "../Abin/abin_E-S.h"  

//1. Implementa un subprograma que calcule el número de nodos de un árbol binario. 


template <typename T>
int numNodos(const Abin<T>& A, typename Abin<T>::nodo n){

    if(n==A.NODO_NULO)
        return 0;
    
    return 1 + A.hijoIzqdo(n) + A.hijoDrcho(n);

}