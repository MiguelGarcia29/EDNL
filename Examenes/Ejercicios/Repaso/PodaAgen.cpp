#include "../Arboles/aGenCelEnLa.hpp"


template <typename T>
void poda(Agen<T>& A, typename Agen<T>::nodo n){

    podaRec(A,n);

    if(A.raiz()==n)
        A.eliminarRaiz();
    else if(A.hijoIzqdo(A.padre(n))==n)
        A.eliminarHijoIzqdo(A.padre(n));
    else{
        typename Agen<T>::nodo hermano = A.hijoIzqdo(A.padre);
        while (A.hermDrcho(hermano)!=n)
        {
            hermano(A.hermDrcho(hermano));
        }
        A.eliminarHermDrcho(hermano);
    }

} 


template <typename T>
void podaRec(Agen<T>& A, typename Agen<T>::nodo n){
    if(n==A.NODO_NULO)
        return;

    while(A.hijoIzqdo(n)!=A.NODO_NULO){
        podaRec(A.hijoIzqdo(n));
        A.eliminarHijoIzqdo(n);
    }
    
} 
