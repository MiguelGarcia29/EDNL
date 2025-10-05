#include "../Grafos/alg_grafoPMC.h"
#include <iostream>

// LA ECENTRICIDAD ES EL CAMINO MAS LARGO DE UN NODO
template <typename tCoste>
tCoste diametro(GrafoP<tCoste> &grafo, size_t nodo)
{

    vector<typename GrafoP<tCoste>::vertice> P;
    tCoste tamMax = -1;

    vector<size_t> D = Dijkstra(grafo, nodo, P);
    for (int j = 0; j < grafo.numVert(); j++)
    {
        if (tamMax < D[j] && D[j] != grafo.INFINITO)
        {
            tamMax = D[j];
        }
    }

    return tamMax;
}



