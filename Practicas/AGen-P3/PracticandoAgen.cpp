#include "aGenLista.hpp"
#include "agen_E-S.h"

using namespace std;
typedef char tElto;

template <typename T>
int numGrado(const Agen<T> &A)
{
    int gradoMax = 1;
    if (A.hijoIzqdo(A.raiz()) != A.NODO_NULO)
        numGradoRec(A, A.hijoIzqdo(A.raiz()), gradoMax);
    return gradoMax;
}

template <typename T>
void numGradoRec(const Agen<T> &A, typename Agen<T>::nodo n, int &gradoMax)
{

    if (n != A.NODO_NULO)
    {

        int num = 0;

        typename Agen<T>::nodo hermano = n;
        while (hermano != A.NODO_NULO)
        {
            num++;
            if (A.hijoIzqdo(hermano) != A.NODO_NULO)
                numGradoRec(A, A.hijoIzqdo(hermano), gradoMax);
            hermano = A.hermDrcho(hermano);
        }

        if (gradoMax < num)
            gradoMax = num;
    }
};

template <typename T>
int numGrado(const Agen<T> &A, typename Agen<T>::nodo n)
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

    return alturaNodo(A, A.raiz());
}

template <typename T>
int alturaNodo(const Agen<T> &A, typename Agen<T>::nodo n)
{

    int altura = 1;

    if (n == A.NODO_NULO)
    {
        return -1;
    }

    typename Agen<T>::nodo hermano = n;

    while (hermano != A.NODO_NULO)
    {
        if (A.hijoIzqdo(hermano) != A.NODO_NULO)
        {
            altura = max(altura, 1 + alturaNodo(A, A.hijoIzqdo(hermano)));
        }
        hermano = A.hermDrcho(hermano);
    }

    return altura;
}

template <typename T>
int alturaMinNodo(const Agen<T> &A, typename Agen<T>::nodo n)
{

    int alturaMin = 10000000;

    if (n == A.NODO_NULO)
    {
        return 0;
    }

    // SI ES HOJA
    if (A.hijoIzqdo(n) == A.NODO_NULO)
    {
        return 1;
    }

    typename Agen<T>::nodo hermano = n;
    while (hermano != A.NODO_NULO)
    {
        if (A.hijoIzqdo(hermano) != A.NODO_NULO)
        {
            alturaMin = min(alturaMin, 1 + alturaMinNodo(A, A.hijoIzqdo(hermano)));
        }
       
        hermano = A.hermDrcho(hermano);
    }

    return alturaMin;
}

template <typename T>
int desequilibrio (const Agen<T> &A){
    return (alturaArbol(A)-alturaMinNodo(A,A.raiz()));
}

/*
template <typename T>
int numGradoRec(const Agen<T>& A,typename Agen<T>::nodo n){

    if (n==A.NODO_NULO)
        return 0;

    int num = 1;

    typename Agen<T>::nodo hermano = A.hermDrcho(n);
    while(hermano!=A.NODO_NULO){
        num++;
        hermano = A.hermDrcho(hermano);
    }

    hermano = n;
    while(hermano!=A.NODO_NULO){
        if(A.hijoIzqdo(hermano)!=A.NODO_NULO)
            num = max(num,numGradoRec(A,A.hijoIzqdo(hermano)));
        hermano = A.hermDrcho(hermano);
    }

    return num;

};*/

int main()
{
    Agen<tElto> B(16);
    ifstream fe("agen.dat"); // Abrir fichero de entrada.
    rellenarAgen(fe, B);     // Desde fichero.
    fe.close();

    cout << "Grado AGen: " << numGrado(B) << "\n";
    cout << "Altura del arbol: " << alturaArbol(B) << "\n";
    cout << "Altura del nodo: " << alturaNodo(B, B.hijoIzqdo(B.raiz())) << "\n";
    cout << "Altura minima: " << alturaMinNodo(B,B.raiz()) << "\n";
}