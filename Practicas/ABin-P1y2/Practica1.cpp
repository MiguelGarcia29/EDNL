#include <iostream>
#include <fstream> 
#include "aBinCelEnla.hpp" 
#include "abin_E-S.h"  

using namespace std;  
typedef char tElto; 
const tElto fin = '#';

template <typename T>
int numNodos (const Abin<T>& A){
    return  numNodosRec(A,A.raiz());
};

template <typename T>
int numNodosRec(const Abin<T>& A, typename Abin<T>::nodo n){

    if(n==A.NODO_NULO)
        return 0;
    else
        return 1 + numNodosRec(A,A.hijoIzqdo(n)) + numNodosRec(A,A.hijoDrcho(n));
};

template <typename T>
int alturaArbol(const Abin<T>& A){
    return alturaArbolrec(A,A.raiz());
};

template <typename T>
int alturaArbolrec(const Abin<T>& A, typename Abin<T>::nodo n){
    if(n==A.NODO_NULO)
        return -1;
    else   
        return 1+max(alturaArbolrec(A,A.hijoIzqdo(n)),alturaArbolrec(A,A.hijoDrcho(n)));
};

template <typename T>
int profundidadNodo(const Abin<T>& A, typename Abin<T>::nodo n){
    int prof=0;
    while(n!=A.raiz()){
        prof += 1;
        n = A.padre(n);
    }
    return prof;
}

template <typename T>
int desequilibrio (const Abin<T>& A){
    return  desequilibrioRec(A,A.raiz());
};

template <typename T>
int desequilibrioRec(const Abin<T>& A, typename Abin<T>::nodo n){
    if(n==A.NODO_NULO)
        return -1;
    else  
        return max(abs(A.altArbolNodo(A.hijoIzqdo(n))-A.altArbolNodo(A.hijoDrcho(n)))
                ,max(desequilibrioRec(A,A.hijoIzqdo(n)),desequilibrioRec(A,A.hijoDrcho(n))));
}

template <typename T>
bool pseudocompleto(const Abin<T>& A){
    return pseudocompletoRec(A,A.raiz());
}


template <typename T>
bool pseudocompletoRec(const Abin<T>& A,typename Abin<T>::nodo n){
    //cout<<A.elemento(n)<<": "<< alturaArbol(A)<<", " << profundidadNodo(A,n)<<"\n";
    if(n==A.NODO_NULO)
        return true;
    if(alturaArbol(A)-profundidadNodo(A,n)==1&&
        ((A.hijoIzqdo(n)!=A.NODO_NULO&&A.hijoDrcho(n)==A.NODO_NULO)||
            (A.hijoIzqdo(n)==A.NODO_NULO&&A.hijoDrcho(n)!=A.NODO_NULO)))
        return false;
    else if(alturaArbol(A)-profundidadNodo(A,n)==1 &&
            ((A.hijoIzqdo(n)==A.NODO_NULO&&A.hijoDrcho(n)==A.NODO_NULO)||
             (A.hijoIzqdo(n)!=A.NODO_NULO&&A.hijoDrcho(n)!=A.NODO_NULO)))
        return true;
             
    else if(A.hijoIzqdo(n)==A.NODO_NULO&&A.hijoDrcho(n)==A.NODO_NULO&&alturaArbol(A)-profundidadNodo(A,n)!=1)
        return true;
    else
        return pseudocompletoRec(A,A.hijoIzqdo(n)) && pseudocompletoRec(A,A.hijoDrcho(n));
            
}


int main()
{
    Abin<tElto> A;
    ifstream fe("A.dat");
    rellenarAbin(fe, A);
    fe.close();
    cout << "Ctdad nodos: "<<numNodos(A);
    cout << "\n";
    cout << "Altura arbol: "<<alturaArbol(A);
    cout << "\n";
    cout << "Profundidad nodo f arbol a: "<<profundidadNodo(A,A.hijoDrcho(A.hijoDrcho(A.hijoIzqdo(A.raiz()))));
    cout << "\n\n\n";
    cout << "Altura nodo b: "<<A.altArbolNodo(A.hijoIzqdo(A.raiz()));
    cout << "\n";
    cout << "Profundidad nodo f arbol a: "<<A.profNodo(A.hijoDrcho(A.hijoDrcho(A.hijoIzqdo(A.raiz()))));

    Abin<tElto> B;
    ifstream ed("B.dat");
    rellenarAbin(ed, B);
    ed.close();
    cout << "\n";
    cout << "Desequilibrio en B: "<< desequilibrio(B);
    cout << "\n";

    Abin<tElto> C;
    ifstream ex("C.dat");
    rellenarAbin(ex, C);
    ex.close();
    cout << "\n";
    cout << "Pseudocompleto en C: "<< pseudocompleto(C);
    cout << "\n";
    cout << "Pseudocompleto en B: "<< pseudocompleto(B);
    cout << "\n";
    cout << "Pseudocompleto en A: "<< pseudocompleto(A);

};
    