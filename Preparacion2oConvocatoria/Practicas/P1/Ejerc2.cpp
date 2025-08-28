//2. Implementa un subprograma que calcule la altura de un árbol binario. 

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