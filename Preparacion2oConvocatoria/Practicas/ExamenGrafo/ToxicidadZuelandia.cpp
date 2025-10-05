#include "../Grafos/alg_grafoPMC.h"

template <typename tCoste>
matriz<tCoste> zuelandiaToxica(GrafoP<tCoste> &Zuelandia, typename GrafoP<tCoste>::vertice Capital)
{

    GrafoP<tCoste> Copia(Zuelandia);

    // HAGO IMPOSIBLE MOVERSE A LA CAPITAL
    for (int i = 0; i < Copia.numVert(); i++)
    {
        Copia[i][Capital] = Copia[Capital][i] = Copia.INFINITO;
    }

    matriz<tCoste> Costes = Floyd(Copia, matriz<typename GrafoP<tCoste>::vertice>(Copia.numVert()));

    vector<tCoste> desdeCapital = Dijkstra(Zuelandia, vector<typename GrafoP<tCoste>::vertice>(Copia.numVert()));
    vector<tCoste> haciaCapital = DijkstraInv(Zuelandia, vector<typename GrafoP<tCoste>::vertice>(Copia.numVert()));

    for (int i = 0; i < Copia.numVert(); i++){

        Costes[i][Capital] = haciaCapital[i];
         Costes[Capital][i] = desdeCapital[i];

    }


    return Costes;

}