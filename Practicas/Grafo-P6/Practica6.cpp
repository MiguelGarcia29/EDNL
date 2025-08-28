#include "../Grafos/alg_grafoPMC.h"
#include <iostream>

// TENGO QUE BUSCAR EL DIAMETRO DE UN  NODO Y LUEGO VER DENTRO DE ESE CAMINO EL QUE TENGA MENOR ECENTRICIDAD
template <typename tCoste>
int pseudocentro(GrafoP<tCoste> grafo)
{
    return 0;
}

// CAMINO MAS LARGO DE UN GRAFO
template <typename tCoste>
typename GrafoP<tCoste>::vertice diametro(GrafoP<tCoste> grafo)
{
    vector<typename GrafoP<tCoste>::vertice> P;
    int max = 0;
    typename GrafoP<tCoste>::vertice vertice;
    for (int i = 0; i < grafo.numVert(); i++)
    {
        vector<tCoste>  D = Dijkstra(grafo, i, P);

        for (int j = 0; j< grafo.numVert(); j++)
        {
            if (D[j] > max){
                max = D[j];
                vertice = i;
            }
        }

    }

    return vertice;
}

// CAMINO MAS LARGO DE UN NODO
template <typename tCoste>
int ecentricidad(GrafoP<tCoste> grafo, typename GrafoP<tCoste>::vertice nodo)
{

    vector<typename GrafoP<tCoste>::vertice> &P;
    vector<typename GrafoP<tCoste>::vertice> D = Dijkstra(grafo, nodo, P);

    int max = 0;
    for (int i = 0; i < grafo.numVert(); i++)
    {
        if (grafo[i] > max)
            max = grafo[i];
    }

    return max;
}

int main(){
    GrafoP<int> G ("./GrafoEj3.dat");
    std::cout << "" << diametro(G);


}