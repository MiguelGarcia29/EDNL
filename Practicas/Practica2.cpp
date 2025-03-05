#include <iostream>
#include <fstream>
#include "aBinCelEnla.hpp"
#include "abin_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin = '#';

template <typename T>
bool arbolSimilar(const Abin<T> &A, const Abin<T> &B)
{
    if (A.raiz() == A.NODO_NULO && B.raiz() != B.NODO_NULO)
        return false;
    else if (A.raiz() != A.NODO_NULO && B.raiz() == B.NODO_NULO)
        return false;
    else if (A.raiz() == A.NODO_NULO && B.raiz() == B.NODO_NULO)
        return true;
    else
        return arbolSimilarRec(A, B, A.raiz(), B.raiz());
}

template <typename T>
bool arbolSimilarRec(const Abin<T> &A, const Abin<T> &B, typename Abin<T>::nodo nA, typename Abin<T>::nodo nB)
{
    if (nA == A.NODO_NULO && nB != B.NODO_NULO)
        return false;
    else if (nA != A.NODO_NULO && nB == B.NODO_NULO)
        return false;
    else if (nA == A.NODO_NULO && nB == B.NODO_NULO)
        return true;
    else
        return arbolSimilarRec(A, B, A.hijoIzqdo(nA), A.hijoIzqdo(nB)) && arbolSimilarRec(A, B, A.hijoDrcho(nA), A.hijoDrcho(nB));
}

template <typename T>
Abin<T> arbolReflejao(const Abin<T> &A)
{
    assert(A.raiz() != A.NODO_NULO);
    Abin<T> ref;
    ref.insertarRaiz(A.elemento(A.raiz()));
    arbolReflejaoRec(A, ref, A.raiz(),ref.raiz());
    return ref;
}

template <typename T>
void arbolReflejaoRec(const Abin<T> &A, Abin<T> &B, typename Abin<T>::nodo nA, typename Abin<T>::nodo nB)
{
    if (A.hijoIzqdo(nA) != A.NODO_NULO)
    {
        B.insertarHijoDrcho(nB, A.elemento(A.hijoIzqdo(nA)));
        arbolReflejaoRec(A, B, A.hijoIzqdo(nA), B.hijoDrcho(nB));
    }
    if (A.hijoDrcho(nA) != A.NODO_NULO)
    {
        B.insertarHijoIzqdo(nB, A.elemento(A.hijoDrcho(nA)));
        arbolReflejaoRec(A, B, A.hijoDrcho(nA), B.hijoIzqdo(nB));
    }
}



int main()
{

    Abin<tElto> A;
    ifstream fe("A.dat");
    rellenarAbin(fe, A);
    fe.close();
    Abin<tElto> B;
    ifstream ed("B.dat");
    rellenarAbin(ed, B);
    ed.close();
    Abin<tElto> D;
    ifstream ex("D.dat");
    rellenarAbin(ex, D);
    ex.close();
    cout << "\n";
    cout << "Arbol binario entre A y B: " << arbolSimilar(A, B);
    cout << "\n";
    cout << "Arbol binario entre C y B: " << arbolSimilar(D, B);
    cout << "\n";
    cout << "Arbol binario entre A y D: " << arbolSimilar(A, D);
    cout << "\n";
    cout << "\n";
    cout << "Arbol A:";
    imprimirAbin(A);
    cout << "\n";
    cout << "Arbol Reflejado A:";
    imprimirAbin(arbolReflejao(A));
    cout << "\n";

}
