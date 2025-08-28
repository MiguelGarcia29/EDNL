#include "../Grafos/alg_grafoPMC.h"
#include "../Grafos/alg_grafo_E-S.h"
#include <iostream>

struct cord
{
    int x;
    int y;
};

template <typename tCoste>
void viajeCostozo(GrafoP<tCoste> G)
{

    // VOY A INVERTIR LOS COSTES PARA CUANDO HAGA FLOYD QUEDARME CON LOS MAS ALTOS
    for (int i = 0; i < G.numVert(); i++)
    {
        for (int j = 0; j < G.numVert(); j++)
        {
            if (G[i][j] != G.INFINITO)
                G[i][j] *= -1;
        }
    }

    matriz<size_t> P;
    matriz<tCoste> M = Floyd(G, P);

    for (int i = 0; i < G.numVert(); i++)
    {
        for (int j = 0; j < G.numVert(); j++)
        {
            if (M[i][j] != G.INFINITO)
                M[i][j] *= -1;
        }
    }
    std::cout << P;

    cord c;
    tCoste max = 0;

    for (int i = 0; i < G.numVert(); i++)
    {
        for (int j = 0; j < G.numVert();j++)
        {
            if (M[i][j] != G.INFINITO)
                if (M[i][j] > max)
                {
                    max = M[i][j];
                    c.x = i;
                    c.y = j;
                }
        }
    }

    std::cout << "Coste mas caro: " << max << " Desde " << c.x << " hasta " << c.y;
    
    std::cout << "\nHay que pasar por:";
    int i = c.y;
    while(i!=c.x){
        std::cout << "\n" << P[c.x][i];
        i=P[c.x][i];
    }
}


int main()
{

    GrafoP<int> G("./Ciudades.dat");
    viajeCostozo(G);
}