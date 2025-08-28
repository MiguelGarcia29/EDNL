#include "Grafos/alg_grafoPMC.h"

struct Casilla
{
    int x, y, z;
};

typedef std::pair<Casilla, Casilla> Pared;

size_t casillaToVertice(int x, int y, int z, int N)
{
    return (x * (N * N) + y * N + z);
}

template <typename tCoste>
GrafoP<tCoste> construirLaberinto(size_t N, vector<Pared> paredes)
{

    GrafoP<tCoste> laberinto(N * N * N);

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            for (int z = 0; z < N; z++)
            {
                size_t actual = casillaToVertice(i, j, z, N);
                if (i + 1 < N)
                {
                    size_t adyacente = casillaToVertice(i + 1, j, z, N);
                    laberinto[actual][adyacente] = laberinto[adyacente][actual] = 1;
                }
                if (i - 1 >= 0)
                {
                    size_t adyacente = casillaToVertice(i - 1, j, z, N);
                    laberinto[actual][adyacente] = laberinto[adyacente][actual] = 1;
                }
                if (j + 1 < N)
                {
                    size_t adyacente = casillaToVertice(i, j + 1, z, N);
                    laberinto[actual][adyacente] = laberinto[adyacente][actual] = 1;
                }
                if (j - 1 >= 0)
                {
                    size_t adyacente = casillaToVertice(i, j - 1, z, N);
                    laberinto[actual][adyacente] = laberinto[adyacente][actual] = 1;
                }
                if (k + 1 < N)
                {
                    size_t adyacente = casillaToVertice(i, j, z + 1, N);
                    laberinto[actual][adyacente] = laberinto[adyacente][actual] = 1;
                }
                if (k - 1 >= 0)
                {
                    size_t adyacente = casillaToVertice(i, j, z - 1, N);
                    laberinto[actual][adyacente] = laberinto[adyacente][actual] = 1;
                }
            }
        }
    }

    for (Pared p : paredes)
    {
        size_t p1 = casillaToVertice(p.first.x, p.first.y, p.first.z);
        size_t p2 = casillaToVertice(p.second.x, p.second.y, p.second.z);
        laberinto[p1][p2]=laberinto[p2][p1]=laberinto.INFINITO;
    }
}

template <typename tCoste>
std::pair<tCoste, vector<typename GrafoP<tCoste>::vertice>> escaparLaberinto(size_t N, const vector<Pared> &paredes, const Casilla& cEnt, const Casilla& cSal)
{
    GrafoP<tCoste> lab = construirLaberinto(N,paredes);

    typename GrafoP<tCoste>::vertice entrada = casillaToVertice(cEnt.x,cEnt.y,cEnt.z);
    typename GrafoP<tCoste>::vertice salida = casillaToVertice(cSal.x,cSal.y,cSal.z);

    vector<typename GrafoP<tCoste>::vertice> P;
    vector<tCoste> costes = Dijkstra(lab,entrada,P);

    return std::make_pair(costes[salida],P);

}