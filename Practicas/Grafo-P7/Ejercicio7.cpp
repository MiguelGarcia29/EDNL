#include "../Grafos/alg_grafoPMC.h"
#include <algorithm>

template <typename tCoste>
// RUTA Y COSTE
std::pair<vector<typename GrafoP<tCoste>::vertice>, tCoste> viaje(typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino,
                                                                  GrafoP<tCoste> tren, GrafoP<tCoste> bus, typename GrafoP<tCoste>::vertice cambio1,
                                                                  typename GrafoP<tCoste>::vertice cambio2)
{

    vector<typename GrafoP<tCoste>::vertice> P1, P2;
    vector<tCoste> desdeTren, haciaBus;

    desdeTren = Dijkstra(tren, origen, P1);
    haciaBus = DijkstraInv(bus, destino, P2);

    tCoste opcion1 = desdeTren[cambio1] + haciaBus[cambio1];
    tCoste opcion2 = desdeTren[cambio2] + haciaBus[cambio2];

    if (opcion1 <= opcion2)
    {
        vector<typename GrafoP<tCoste>::vertice> ruta;

        typename GrafoP<tCoste>::vertice posActual = cambio1;

        ruta.push_back(posActual);
        while (posActual != origen)
        {
            ruta.push_back(P1[posActual]);
            posActual = P1[posActual];
        }
        ruta.push_back(origen);
        std::reverse(ruta.begin(), ruta.end());

        posActual = cambio1;
        while (posActual != destino)
        {
            ruta.push_back(P2[posActual]);
            posActual = P2[posActual];
        }

        ruta.push_back(destino);

        return std::make_pair<ruta, opcion1>;
    }
    else
    {
        typename GrafoP<tCoste>::vertice posActual = cambio2;
        ruta.push_back(posActual);
        while (posActual != origen)
        {
            ruta.push_back(P1[posActual]);
            posActual = P1[posActual];
        }
        ruta.push_back(origen);
        std::reverse(ruta.begin(), ruta.end());

        posActual = cambio2;
        while (posActual != destino)
        {
            ruta.push_back(P2[posActual]);
            posActual = P2[posActual];
        }

        ruta.push_back(destino);

        return std::make_pair<ruta, opcion1>;
    }
};