#include "../Grafos/alg_grafoPMC.h"

template <typename tCoste>
tCoste viajeBarato(GrafoP<tCoste> tren, GrafoP<tCoste> bus, typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino)
{

    vector<typename Grafo<tCoste>::vertice> P;
    vector<tCoste> dijkBus = Dijkstra(bus, origen, P);
    vector<tCoste> dijkTren = Dijkstra(tren, origen, P);
    vector<tCoste> dijkInvTren = DijkstraInv(tren, destino, P);
    vector<tCoste> dijkInvBus = DijkstraInv(bus, destino, P);

    tCoste minimo = tren.INFINITO;

    for(int i=0;i<tren.numVert();i++){
        if(suma(dijkBus[i],dijkInvTren[i])<minimo){
            minimo = suma(dijkBus[i],dijkInvTren[i]);
        }
        if (suma(dijkTren[i],dijkInvBus[i])<minimo){
            minimo = suma(dijkTren[i],dijkInvBus[i]);
        }
    }

    minimo = std::min(minimo,std::min(dijkBus[destino],dijkTren[destino]));

    return minimo;
}
