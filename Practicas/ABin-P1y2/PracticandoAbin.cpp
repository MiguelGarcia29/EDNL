#include <iostream>
#include <fstream>
#include "aBinCelEnla.hpp"
#include "abin_E-S.h"

using namespace std;
typedef char tElto;
const tElto fin = '#';

template <typename T>
int numNodos(const Abin<T> &A)
{
    return numNodosRec(A, A.raiz());
}

template <typename T>
int numNodosRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
    if (n == A.NODO_NULO)
        return 0;

    return 1 + numNodosRec(A, A.hijoIzqdo(n)) + numNodosRec(A, A.hijoDrcho(n));
}

template <typename T>
int altura(const Abin<T> &A)
{
    // NO SE SUMA LA ALTURA DEL RAIZ
    return alturaRec(A, A.raiz());
}

template <typename T>
int alturaRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
    if (n == A.NODO_NULO)
        return -1;

    return 1 + max(alturaRec(A, A.hijoIzqdo(n)), alturaRec(A, A.hijoDrcho(n)));
}

template <typename T>
int profundidad(const Abin<T> &A, typename Abin<T>::nodo n)
{
    int prof = 0;

    typename Abin<T>::nodo actual = A.padre(n);
    while (actual != A.NODO_NULO)
    {
        prof++;
        actual = A.padre(actual);
    }

    return prof;
}

template <typename T>
int desequilibrio(const Abin<T> &A)
{
    return desequilibrioRec(A, A.raiz());
}

template <typename T>
int desequilibrioRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
    // EL -1 PORQUE NO QUIERO CONTAR EL RAIZ
    if (n == A.NODO_NULO)
        return -1;
    // EL MAXIMO ENTRE LA DIFERENCIA NODO ACTUAL SUS RAMAS O SUS RAMAS DE ABAJO.
    return max(abs(alturaRec(A, A.hijoIzqdo(n)) - alturaRec(A, A.hijoDrcho(n))),
               max(desequilibrioRec(A, A.hijoIzqdo(n)), desequilibrioRec(A, A.hijoDrcho(n))));
}

// BAJO HASTA ENCONTRAR EL ULTIMO NIVEL Y MIRO SI TIENE DOS HIJOS

template <typename T>
bool pseudoCompleto(const Abin<T> &A)
{
    return pseudoCompletoRec(A, A.raiz());
}

template <typename T>
bool pseudoCompletoRec(const Abin<T> &A, typename Abin<T>::nodo n)
{
    // CUANDO LLEGUE ABAJO DEL TODO MIRO
    if (n == A.NODO_NULO)
    {
        return true;
    }

    else if (altura(A) - profundidad(A, n) == 1)
    {
        // SI SOLO TIENE UN HIJO
        if (((A.hijoIzqdo(n) != A.NODO_NULO && A.hijoDrcho(n) == A.NODO_NULO) ||
             (A.hijoIzqdo(n) == A.NODO_NULO && A.hijoDrcho(n) != A.NODO_NULO)))
            return false;
        else
            return true;
    }
    else
        return true && pseudoCompletoRec(A, A.hijoIzqdo(n)) && (A, A.hijoDrcho(n));
}
template <typename T>
bool similar(const Abin<T> &A, const Abin<T> &B)
{
    if (A.raiz() == A.NODO_NULO && B.raiz() == B.NODO_NULO)
    {
        return true;
    }
    return similarRec(A, B, A.raiz(), B.raiz());
}

template <typename T>
bool similarRec(const Abin<T> &A, const Abin<T> &B, typename Abin<T>::nodo nA, typename Abin<T>::nodo nB)
{
    if (nA == A.NODO_NULO && nB == B.NODO_NULO)
    {
        return true;
    }
    // MIRO QUE NO HAYA UNO QUE TENGA DESCENDENCIA Y OTRO NO
    else if ((nA != A.NODO_NULO && nB == B.NODO_NULO) ||
             (nA == A.NODO_NULO && nB != B.NODO_NULO))
    {
        return false;
    }
    else
    {
        return true && similarRec(A, B, A.hijoIzqdo(nA), B.hijoIzqdo(nB)) && similarRec(A, B, A.hijoDrcho(nA), B.hijoDrcho(nB));
    }
}

template <typename T>
Abin<T> arbolReflejado(const Abin<T> &A)
{
    Abin<T> refl;
    refl.insertarRaiz(A.elemento(A.raiz()));
    arbolReflejadoRec(A, refl, A.raiz(), refl.raiz());
    return refl;
}

template <typename T>
void arbolReflejadoRec(const Abin<T> &A, Abin<T> &R, typename Abin<T>::nodo n, typename Abin<T>::nodo nr)
{
    if (n != A.NODO_NULO)
    {
        if (A.hijoIzqdo(n) != A.NODO_NULO)
        {
            R.insertarHijoDrcho(nr, A.elemento(A.hijoIzqdo(n)));
            arbolReflejadoRec(A, R, A.hijoIzqdo(n), R.hijoDrcho(nr));
        }
        if (A.hijoDrcho(n) != A.NODO_NULO)
        {
            R.insertarHijoIzqdo(nr, A.elemento(A.hijoDrcho(n)));
            arbolReflejadoRec(A, R, A.hijoDrcho(n), R.hijoIzqdo(nr));
        }
    }
}

int main()
{ /*
     Abin<tElto> A;
     ifstream fe("A.dat");
     rellenarAbin(fe, A);
     fe.close();
     cout << "Ctdad nodos: " << numNodos(A);
     cout << "\n";
     cout << "Altura arbol: " << altura(A);
     cout << "\n";
     cout << "Profundidad nodo f arbol a: " << profundidad(A, A.hijoDrcho(A.hijoDrcho(A.hijoIzqdo(A.raiz()))));
     cout << "\n\n\n";
     cout << "Altura nodo b: " << A.altArbolNodo(A.hijoIzqdo(A.raiz()));
     cout << "\n";
     cout << "Profundidad nodo f arbol a: " << A.profNodo(A.hijoDrcho(A.hijoDrcho(A.hijoIzqdo(A.raiz()))));

     Abin<tElto> B;
     ifstream ed("B.dat");
     rellenarAbin(ed, B);
     ed.close();
     cout << "\n";
     cout << "Altura arbol: " << altura(B);
     cout << "\n";
     cout << "Desequilibrio en B: " << desequilibrio(B);
     cout << "\n";

     Abin<tElto> C;
     ifstream ex("C.dat");
     rellenarAbin(ex, C);
     ex.close();
     cout << "\n";
     cout << "Pseudocompleto en C: " << pseudoCompleto(C);
     cout << "\n";
     cout << "Pseudocompleto en B: " << pseudoCompleto(B);
     cout << "\n";
     cout << "Pseudocompleto en A: " << pseudoCompleto(A);*/
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
    cout << "Arbol binario entre A y B: " << similar(A, B);
    cout << "\n";
    cout << "Arbol binario entre C y B: " << similar(D, B);
    cout << "\n";
    cout << "Arbol binario entre A y D: " << similar(A, D);
    cout << "\n";
    cout << "\n";
    cout << "Arbol A:";
    imprimirAbin(A);
    cout << "\n";
    cout << "Arbol Reflejado A:";
    imprimirAbin(arbolReflejado(A));
    cout << "\n";
};
