#include "../Grafos/alg_grafoPMC.h"

template <typename tCoste>
matriz<tCoste> tarifaMinima(GrafoP<tCoste> tren, GrafoP<tCoste> bus, typename GrafoP<tCoste>::vertice cambioEstaciones, GrafoP<tCoste>::vertice origen)
{

    vector<typename GrafoP<tCoste>::vertice> P;
    matriz<tCoste> C1 = Floyd(tren, P);
    matriz<tCoste> C2 = Floyd(bus, P);

    matriz<tCoste> costes(tren.numVert());
    for (int i = 0; i < tren.numVert(); i++)
    {
        tCoste min;
        for (int j = 0; j < tren.numVert(); j++)
        {
            costes[i][j] = std::min(std::min(C1[i][j], C2[i][j]), std::min(C1[i][cambioEstaciones] + C2[cambioEstaciones][j],
                                                                           C2[i][cambioEstaciones] + C1[cambioEstaciones][j]));
            ;
        }
    }

    return costes;
}