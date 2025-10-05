#include "../Abin/aBinCelEnla.hpp"
#include "ComprobarABB.cpp"


template <typename T>
int alturaNodo(const Abin<T> & A, typename Abin<T>::nodo nA){

    if(nA==A.NODO_NULO)
        return -1;

    return 1 + std::max(alturaNodo(A,A.hijoIzqdo(nA)),alturaNodo(A,A.hijoDrcho(nA)));

}



template <typename T>
int equilibrioAVLRec(const Abin<T> & A, typename Abin<T>::nodo nA){

    if (nA==A.NODO_NULO)
        return 0;

    return std::max(std::abs(alturaNodo(A.hijoIzqdo(nA))-alturaNodo(A.hijoDrcho(nA))),
                    std::max(equilibrioAVLRec(A,A.hijoIzqdo(nA)),equilibrioAVLRec(A,A.hijoDrcho(nA))));


}

template <typename T>
bool esAVL(const Abin<T> &A){
    return equilibrioAVLRec(A,A.raiz()) >= 0 && equilibrioAVLRec(A,A.raiz()) <= 1 && esABB(A);
}







