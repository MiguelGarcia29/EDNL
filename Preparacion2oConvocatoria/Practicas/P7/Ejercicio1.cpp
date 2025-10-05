#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/alg_grafo_E-S.h"

struct Viaje
{
    size_t Origen;
    size_t Destino;
};

template <typename tCoste>
Viaje masCostoso(GrafoP<tCoste> G)
{

    for (int i = 0; i < G.numVert; i++)
    {
        for (int j = 0; j < G.numVert; j++)
        {
            if (G[i][j] != G.INFINITO)
                G[i][j] *= -1;
        }
    }

    matriz<typename GrafoP<tCoste>::vertice> &P;
    matriz<tCoste> M = Floyd(G, P);
    tCoste max = -1;
    Viaje v;
    for (int i = 0; i < G.numVert; i++)
    {
        for (int j = 0; j < G.numVert; j++)
        {
            if (G[i][j] != G.INFINITO)
                G[i][j] *= -1;
            if (M[i][j] != G.INFINITO){
                M[i][j] *= -1;
                if(M[i][j]>max){
                    max = M[i][j];
                    v.Origen = i;
                    v.Destino = j;
                }
            }
            
        }
    }

    return v;
}

