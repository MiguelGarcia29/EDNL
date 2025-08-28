#include "aGenLista.hpp"
#include "agen_E-S.h"
#include <iostream>

using namespace std;
typedef char tElto;

template <typename T>
int gradoAGen(const Agen<T> &A)
{

    int gradoMax = 1;
    if (A.hijoIzqdo(A.raiz()) != A.NODO_NULO)
        gradoAGenRec(A, A.hijoIzqdo(A.raiz()), gradoMax);
    return gradoMax;
}

template <typename T>
void gradoAGenRec(const Agen<T> &A, typename Agen<T>::nodo n, int &gradoMax)
{
    if (n != A.NODO_NULO)
    {
        int grado = 1;

        typename Agen<T>::nodo hermano = A.hermDrcho(n);
        while (hermano != A.NODO_NULO)
        {
            grado++;

            if (A.hijoIzqdo(hermano) != A.NODO_NULO)
            {
                gradoAGenRec(A, A.hijoIzqdo(hermano), gradoMax);
            }
            hermano = A.hermDrcho(hermano);
        }
        if (A.hijoIzqdo(n) != A.NODO_NULO)
        {
            gradoAGenRec(A, A.hijoIzqdo(n), gradoMax);
        }
        if (grado > gradoMax)
            gradoMax = grado;
    }
}

template <typename T>
int profNodo(const Agen<T> &A, typename Agen<T>::nodo n)
{

    int prof = 0;
    while (n != A.raiz())
    {
        prof++;
        n = A.padre(n);
    }

    return prof;
}

template <typename T>
int alturaArbol(const Agen<T> &A)
{

    int altura = 1;

    if (A.hijoIzqdo(A.raiz()) != A.NODO_NULO)
        altura += 1 + alturaArbolRec(A, A.hijoIzqdo(A.raiz()));

    return altura;
}

template <typename T>
int alturaArbolRec(const Agen<T> &A, typename Agen<T>::nodo n)
{
    if (n == A.NODO_NULO)
    {
        return 0;
    }
    int altura = 1;
    if (A.hijoIzqdo(n) != A.NODO_NULO)
    {
        altura += alturaArbolRec(A, A.hijoIzqdo(n));
    }

    typename Agen<T>::nodo hermano = A.hermDrcho(n);
    while (hermano != A.NODO_NULO)
    {
        if (A.hijoIzqdo(hermano) != A.NODO_NULO)
        {
            altura = max(altura, alturaArbolRec(A, A.hijoIzqdo(hermano)));
        }
        hermano = A.hermDrcho(hermano);
    }

    return altura;
}

template <typename T>
int alturaMinArbol(const Agen<T> &A)
{
    int altura = 0;
    if (A.hijoIzqdo(A.raiz()) != A.NODO_NULO)
    {
        altura += 1 + alturaMinArbolRec(A, A.hijoIzqdo(A.raiz()));
    }
    return altura;
}

template <typename T>
int alturaMinArbolRec(const Agen<T> &A, typename Agen<T>::nodo n)
{

    if (n == A.NODO_NULO)
        return 0;

    int altura = 0;
    if (A.hijoIzqdo(n) != A.NODO_NULO)
        altura += 1 + alturaMinArbolRec(A, A.hijoIzqdo(n));

    typename Agen<T>::nodo hermano = A.hermDrcho(n);
    while (hermano != A.NODO_NULO)
    {
        if (A.hijoIzqdo(hermano) != A.NODO_NULO)
        {
            altura = min(altura, alturaMinArbolRec(A, A.hijoIzqdo(hermano)));
        }
        hermano = A.hermDrcho(hermano);
    }

    return altura;
}

template <typename T>
int desequilibrio(const Agen<T> &A)
{
    return (alturaArbol(A) - 1) - (alturaMinArbol(A) - 1);
}
/*
template <typename T>
void podarArbol(Agen<T> A, typename Agen<T>::nodo n)
{
    podarArbolRec(A, n);
    if (n == A.raiz())
    {
        A.eliminarRaiz();
    }
    else if (n == A.hijoIzqdo(A.padre(n)))
    {
        A.eliminarHijoIzqdo(A.padre(n));
    }
    else
    { // SI NO ES HERMANO DRCHO DE UN NODO
        bool elimado = false;
        typename Agen<T>::nodo hrmano = A.hijoIzqdo(A.padre(n));

        while (A.hermDrcho(hrmano) != n) // AVANZO HASTA QUE EL HERMANO DEL NODO SEA N
            hrmano = A.hermDrcho(hrmano);
        A.eliminarHermDrcho(hrmano);
    }
}

template <typename T>
void podarArbolRec(Agen<T> A, typename Agen<T>::nodo n)
{
    if (n != A.NODO_NULO)
        while (A.hijoIzqdo(n) != A.NODO_NULO)
        {
            podarArbolRec(A, A.hijoIzqdo(n));
            A.eliminarHijoIzqdo(n);         //ME DA ERROR AL ELIMINAR H HABIENDOSE ELIMINADO J
        }
}*/

// Enunciado: Calcular densidad de un ´arbol. La densidad se define como el Grado
// m´aximo de un ´arbol partido del n´umero de nodos hojas.

template <typename T>
int grado_rec(const Agen<T> &A, typename Agen<T>::nodo n)
{

    int numHijos = 1;
    int gradoMaxHijo = 0;

    if (n == A.NODO_NULO)
    {
        return numHijos;
    }

    typename Agen<T>::nodo hijo = A.hijoIzqdo(n);

    while (hijo != A.NODO_NULO)
    {
        numHijos++;

        if (A.hijoIzqdo(hijo) != A.NODO_NULO)
            gradoMaxHijo = grado_rec(A, A.hijoIzqdo(hijo));

        hijo = A.hermDrcho(hijo);
    }

    return std::max(numHijos, gradoMaxHijo);
}

int main()
{
    Agen<tElto> B(16);
    ifstream fe("agen.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, B);     // Desde fichero.
    fe.close();

    cout << "Grado AGen: " << gradoAGen(B) << "\n";
    cout << "Grado AGen: " << grado_rec(B, B.raiz()) << "\n";

    cout << "Profundida de nodo j: " << profNodo(B, B.hijoIzqdo(B.hermDrcho(B.hermDrcho(B.hijoIzqdo(B.hijoIzqdo(B.raiz())))))) << "\n";
    cout << "Altura del arbol: " << alturaArbol(B) << "\n";
    cout << "Rama mas cortas: " << alturaMinArbol(B) << "\n";
    cout << "Desequilibrio: " << desequilibrio(B) << "\n";
    cout << "PODANDO EL ARBOL ENTERO: ";
    //podarArbol(B, B.raiz());
    //imprimirAgen(B);
}