//Implementa un subprograma que, dados un árbol binario y un nodo del mismo, determine 
//la profundidad de este nodo en dicho árbol. 



#include <iostream>
#include <fstream> 
#include "../Abin/aBinCelEnla.hpp" 
#include "../Abin/abin_E-S.h"  

template <typename T>
int prof(const Abin<T>& A, typename Abin<T>::nodo n){

    int profundidad = 0;
    while(n!=A.raiz()){
        prof++;
        n = A.padre(n);
    }

    return prof;
}