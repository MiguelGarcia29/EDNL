#include "../Grafos/alg_grafoPMC.h"

std::pair<vector<typename GrafoP<int>::vertice>, int> viaje(const GrafoP<int> &Avion, const GrafoP<int> &Bus, const GrafoP<int> &Tren,
                                     typename GrafoP<int>::vertice origen, typename GrafoP<int>::vertice destino, 
                                     int trenBus, int costeAeropuerto)
{

    GrafoP<int> superGrafo(3 * Avion.numVert());

    for (int i = 0; i < Avion.numVert(); i++)
    {
        for (int j = 0; j < Avion.numVert(); j++)
        {
            // AÑADO AVION
            superGrafo[i][j] = Avion[i][j];
            // AÑADO BUS
            superGrafo[i + Avion.numVert()][j + Avion.numVert()] = Bus[i][j];
            // AÑADO TREN
            superGrafo[i + 2 * Avion.numVert()][j + 2 * Avion.numVert()] = Tren[i][j];
        }
    }

    // COSTE DE IR DEL BUS AL TREN Y VICIVERSA

    for (int i = 0; i < Avion.numVert(); i++)
    {
        for (int j = 0; j < Avion.numVert(); j++)
        {
            superGrafo[i + Avion.numVert()][j + 2 * Avion.numVert()] =
                superGrafo[j + 2 * Avion.numVert()][i + Avion.numVert()] = trenBus;
        }
    }

    // COSTE DE IR DEL AVION A CUALQUEIR SITIO Y VICIVERSA
    for (int i = 0; i < Avion.numVert(); i++)
    {
        for (int j = 0; j < Avion.numVert(); j++)
        {
            superGrafo[i][j + Avion.numVert()] =
                superGrafo[j + Avion.numVert()] [i] = costeAeropuerto;


            superGrafo[i][j + 2 * Avion.numVert()] =
                superGrafo[j + 2 * Avion.numVert()] [i] = costeAeropuerto;
        }
    }

    vector<typename GrafoP<int>::vertice> P(superGrafo.numVert());
    vector<int> coste = Dijkstra(superGrafo,origen,P);

    return std::make_pair(P,coste[destino]);

}