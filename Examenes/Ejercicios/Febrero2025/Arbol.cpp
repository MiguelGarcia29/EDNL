#include "../Arboles/aBinCelEnla.hpp"
#include "../Grafos/colaenla.h"
#include <iostream>



void preOrdenRec(Abin<char> &a, typename Abin<char>::nodo n)
{
    if (n != a.NODO_NULO)
    {
        std::cout << a.elemento(n);
        preOrdenRec(a, a.hijoIzqdo(n));
        preOrdenRec(a, a.hijoDrcho(n));
    }
}

void construirArbol(char *cad)
{

    Abin<char> a;
    a.insertarRaiz(cad[0]);

    Cola<typename Abin<char>::nodo> nodos;
    nodos.push(a.raiz());

    typename Abin<char>::nodo actual;
    for (int i = 1; cad[i] != '\0'; i++)
    {
        if (!nodos.vacia())
        {
            actual = nodos.frente();
            nodos.pop();

            a.insertarHijoIzqdo(actual, cad[i]);
            nodos.push(a.hijoIzqdo(actual));

            if (cad[i + 1] != '\0')
            {
                a.insertarHijoDrcho(actual, cad[i + 1]);
                i++;
                nodos.push(a.hijoDrcho(actual));
            }
        }
    };

    preOrdenRec(a, a.raiz());
}


int main()
{
    construirArbol("Hola Mundo");
}
