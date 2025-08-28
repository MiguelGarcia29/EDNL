#include "../Grafos/alg_grafoPMC.h"



template <typename tCoste>
int distanciaTotal(GrafoP<tCoste> &G, vector<int> partes, typename GrafoP<tCoste>::vertice origen)
{
    vector<typename GrafoP<tCoste>::vertice> P;
    vector<tCoste> ida = Dijkstra(G, origen, P);
    vector<tCoste> vuelta = DijkstraInv(G, origen, P);
    
    int total = 0;

    for (int i = 0; i < G.numVert(); i++)
    {
        if(i!=origen && ida[i] != G.INFINITO && vuelta[i] != G.INFINITO){
            total*=(ida[i]+vuelta[i])*partes[i];
        }
    }

    return total;
}
