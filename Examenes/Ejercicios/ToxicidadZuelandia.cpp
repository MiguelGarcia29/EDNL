#include "Grafos/alg_grafoPMC.h"

template <typename tCoste>
matriz<tCoste> costes(GrafoP<tCoste> &G, typename GrafoP<tCoste>::vertice capital)
{

    GrafoP<tCoste> Z(G);
    // POR SI NO ERES RESIDENTE
    for (int i = 0; i < Z.numVert(); i++)
    {
        Z[i][capital] = Z[capital][i] = Z.INFINITO;
    }

    matriz<typename GrafoP<tCoste>::vertice> P;
    matriz<tCoste> coste = Floyd(Z, P);

    //AHORA VAMOS A CALCULAR PARA LOS RESIDENTES
    vector<typename GrafoP<tCoste>::vertice> r;
    vector<tCoste> haciaCapi = DijkstraInv(G, capital, r);
    vector<tCoste> desdeCapi = Dijkstra(G, capital, r);

    for (int i = 0; i < Z.numVert(); i++)
    {
        coste[i][capital]=haciaCapi[i];
        coste[capital][i]=desdeCapi[i];
    }

    return coste;
}