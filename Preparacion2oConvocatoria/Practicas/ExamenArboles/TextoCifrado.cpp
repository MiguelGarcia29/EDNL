#include "../Abin/aBinCelEnla.hpp"
#include "../Grafos/colaenla.h"
#include "vector"

Abin<char> construirArbol(char *cadena)
{

    int indice = 0;

    Abin<char> Arbol;

    Arbol.insertarRaiz(cadena[indice]);
    indice++;
    typename Abin<char>::nodo actual = Arbol.raiz();
    Cola<typename Abin<char>::nodo> nodos;
    nodos.push(actual);

    while (cadena[indice] != '\0')
    {

        actual = nodos.frente();
        nodos.pop();

        Arbol.insertarHijoIzqdo(actual, cadena[indice]);
        nodos.push(Arbol.hijoIzqdo(actual));
        indice++;

        if (cadena[indice] != '\0')
        {
            Arbol.insertarHijoDrcho(actual, cadena[indice]);
            nodos.push(Arbol.hijoDrcho(actual));
            indice++;
        }
    }

    return Arbol;
}

int numNodos(const Abin<char> &A, typename Abin<char>::nodo nA)
{
    if (nA != A.NODO_NULO)
        return 0;

    return 1 + numNodos(A, A.hijoIzqdo(nA)) + numNodos(A, A.hijoDrcho(nA));
}

 void cadenaEncriptada(const Abin<char> &A, typename Abin<char>::nodo nA, std::vector<char> texto)
{

    if(nA!=A.NODO_NULO){

        texto.push_back(A.elemento(nA));
        cadenaEncriptada(A,A.hijoIzqdo(nA),texto);
        cadenaEncriptada(A,A.hijoDrcho(nA),texto);
    }    


}


std::vector<char> textoEncriptado(char *texto){

    Abin<char> Arbol = construirArbol(texto);
    std::vector<char> textoV;
    cadenaEncriptada(Arbol,Arbol.raiz(),textoV);

    return textoV;

}