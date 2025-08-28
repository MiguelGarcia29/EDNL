#include "../Grafos/alg_grafoPMC.h"

template <typename tCoste>
GrafoP<tCoste> superGrafo(GrafoP<tCoste> T, GrafoP<tCoste> B, GrafoP<tCoste> A, tCoste aero, tCoste busTren)
{

    GrafoP<tCoste> superGraf(3 * T.numVert());

    // PRIMER, QUINTO Y NOVENO CUADRANTE
    for (int i = 0; i < T.numVert(); i++)
    {
        for (int j = 0; j < T.numVert(); j++)
        {
            superGraf[i][j] = T[i][j];
            superGraf[i + T.numVert()][j + T.numVert()] = B[i][j];
            superGraf[i + 2 * T.numVert()][j + 2 * T.numVert()] = A[i][j];
        }
    }

    // TAXIS
    for (int i = 0; i < T.numVert(); i++)
    {
        // SEGUNDO CUADRANTE
        superGraf[i][i + T.numVert()] = busTren;
        // TERCER CUADRANTE
        superGraf[i][i + 2 * T.numVert()] = aero;
        // CUARTO CUADRANTE
        superGraf[i + T.numVert()][i] = busTren;
        // SEXTO CUADRANTE
        superGraf[i + T.numVert()][i + 2 * T.numVert()] = aero;
        // SEPTIMO Y OCTAVO
        superGraf[i + 2 * T.numVert()][i] = busTren;
        superGraf[i + 2 * T.numVert()][i + T.numVert()] = busTren;
    }
}

template <typename tCoste>
std::pair<tCoste, vector<typename GrafoP<tCoste>::vertice>> rutaMasEconomica(GrafoP<tCoste> T, GrafoP<tCoste> B, GrafoP<tCoste> A, tCoste aero, tCoste busTren,
                                                                             typename GrafoP<tCoste>::vertice origen, typename GrafoP<tCoste>::vertice destino)
{

    GrafoP<tCoste> sGrafo = superGrafo(T, B, A, aero, busTren);

    vector<typename GrafoP<tCoste>::vertice> P;
    vector<tCoste> dijks = Dijkstra(sGrafo, origen, P);
    //HAY Q HACER 3 DIJKSTRA PARTIENDO DESDE ORIGEN TREN/BUS o AVION Y LUEGO COMPROBAR LLEGANDO A CADA TIPO DE VUELO
    //POR TANTO HAY QUE COMPARAR 9 VECES LA MEJOR RUTA
    return std::make_pair<dijks[destino],P>;
}