#include "Arboles/aBinCelEnla.hpp"


template <typename T>
void flotar(Abin<T>& A, typename Abin<T>::nodo n){
    if(n!=A.NODO_NULO&&n!=A.raiz()){
        if(A.elemento(n)>A.elemento(A.padre(n))){
            T aux = A.elemento(n);
            A.elemento(n) = A.elemento(A.padre(n));
            A.elemento(A.padre(n)) = aux;
            flotar(A,A.padre(n));
        }
    }
}