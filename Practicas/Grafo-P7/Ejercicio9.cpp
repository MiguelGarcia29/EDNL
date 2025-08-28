#include "../Grafos/alg_grafoPMC.h"

template <typename tCoste>
GrafoP<tCoste> generarGrafo(GrafoP<tCoste> t, GrafoP<tCoste> b, tCoste costeTaxi)
{
    GrafoP<tCoste> superGrafo((t.numVert() + b.numVert()));

    for (int i = 0; i < t.numVert(); i++)
    {
        for (int j = 0; j < t.numVert(); j++)
        {
            superGrafo[i][j] = t[i][j];
            superGrafo[i + t.numVert()] [j + t.numVert()] = b[i][j];
        }
    }

    //SEGUNDO Y TERCER CUADRANTO
    for (int i = 0; i < t.numVert(); i++)
    {
        superGrafo[i + t.numVert()][i] = costeTaxi;
        superGrafo[i][i + t.numVert()] = costeTaxi;
    }

    return superGrafo;
}

template <typename tCoste>
std::pair<tCoste,vector<typename GrafoP<tCoste>::vertice>> mejorForma(GrafoP<tCoste> t, GrafoP<tCoste> b, tCoste costeTaxi,
                                    typename GrafoP<tCoste>::vertice origen,typename GrafoP<tCoste>::vertice destino){
    
    GrafoP<tCoste> superGrafo = generarGrafo(t,b,costeTaxi);
    
    vector<typename GrafoP<tCoste>::vertice> P;
    vector<tCoste> dijks = Dijkstra(superGrafo,origen,P);
    
    return std::make_pair(dijks[destino],P);
}