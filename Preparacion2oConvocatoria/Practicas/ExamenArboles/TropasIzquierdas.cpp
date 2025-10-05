#include "../AGen/aGenCelEnLa.hpp"
#include "../AGen/listaenla.h"
#include "../Grafos/colaenla.h"

template <typename T>
int profundidadNodo(const Agen<T> &A, typename Agen<T>::nodo nA)
{

    if (nA == A.NODO_NULO)
        return 0;

    int prof = 0;

    while (nA != A.raiz())
    {
        prof++;
        nA = A.padre(nA);
    }
}

template <typename T>
Lista<typename Agen<T>::nodo> TropasIzquierdas(const Agen<T> &A)
{

    int profActual = 0;

    Cola<typename Agen<T>::nodo> c;
    c.push(A.raiz());
    typename Agen<T>::nodo n;
    Lista<typename Agen<T>::nodo> lista;

    do
    {
        if (!c.vacia())
        {
            n = c.frente();
            c.pop();
        }

        if (profActual < profundidadNodo(A, n))
        {
            lista.insertar(n, lista.fin());
            profActual++;
        }

        typename Agen<T>::nodo hijo = A.hijoIzqdo(n);
        while(hijo!=A.NODO_NULO){
            c.push(hijo);
            hijo = A.hermDrcho;
        }

    } while (!c.vacia());


    return lista;
}