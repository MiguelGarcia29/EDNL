#include "../Grafos/alg_grafoPMC.h"

typedef std::pair<typename GrafoP<int>::tCamino, int> Camino_Coste;
typedef struct Casilla
{
    size_t x, y, z;
    Casilla(size_t i, size_t j, size_t k) : x{i}, y{j}, z{k} {};
};
typedef std::pair<Casilla, Casilla> Pared;

typename GrafoP<double>::vertice CasillaToVertice(Casilla c, int N)
{
    return c.x + c.y * N + c.z * N * N;
}

Camino_Coste escaparLaberinto(int N, vector<Pared> &Paredes, Casilla entrada, Casilla salida)
{

    GrafoP<int> laberinto(N * N * N);

    // Construyo el laberinto
    for (size_t z = 0; z < N; z++)
    {
        for (size_t y = 0; y < N; y++)
        {
            for (size_t x = 0; x < N; x++)
            {
                typename GrafoP<double>::vertice posActual = CasillaToVertice(Casilla(x, y, z), N);
                // IZQ
                if (x - 1 > 0)
                {
                    laberinto[posActual][CasillaToVertice(Casilla(x - 1, y, z), N)] = laberinto[CasillaToVertice(Casilla(x - 1, y, z), N)][posActual] = 1;
                }
                // DER
                if (x + 1 < N)
                {
                    laberinto[posActual][CasillaToVertice(Casilla(x + 1, y, z), N)] = laberinto[CasillaToVertice(Casilla(x + 1, y, z), N)][posActual] = 1;
                }
                // ADELANTE
                if (y + 1 < N)
                {
                    laberinto[posActual][CasillaToVertice(Casilla(x, y + 1, z), N)] = laberinto[CasillaToVertice(Casilla(x, y + 1, z), N)][posActual] = 1;
                }
                // ATRAS
                if (y - 1 > 0)
                {
                    laberinto[posActual][CasillaToVertice(Casilla(x, y - 1, z), N)] = laberinto[CasillaToVertice(Casilla(x, y - 1, z), N)][posActual] = 1;
                }
                // ARRIBA
                if (z + 1 < N)
                {
                    laberinto[posActual][CasillaToVertice(Casilla(x, y, z + 1), N)] = laberinto[CasillaToVertice(Casilla(x, y, z + 1), N)][posActual] = 1;
                }
                // ABAJO
                if (z - 1 > 0)
                {
                    laberinto[posActual][CasillaToVertice(Casilla(x, y - 1, z), N)] = laberinto[CasillaToVertice(Casilla(x, y - 1, z), N)][posActual] = 1;
                }
            }
        }
    }

    // Pongo las paredes
    for (Pared p : Paredes)
    {
        laberinto[p.first, N][p.second, N] = laberinto[p.second, N][p.first, N] = laberinto.INFINITO;
    }

    vector<typename GrafoP<double>::vertice> P(laberinto.numVert());
    typename GrafoP<double>::vertice vertEntrada = CasillaToVertice(entrada, N);
    vector<int> Coste = Dijkstra(laberinto, vertEntrada, P);
    typename GrafoP<double>::vertice v = CasillaToVertice(salida, N);
    int costeTotal = Coste[v];

    typename GrafoP<int>::tCamino C;
    C.insertar(v, C.primera());
    do
    {
        C.insertar(P[v],C.primera());
        v = P[v];
    } while (v != vertEntrada);


    return std::make_pair(C,costeTotal);

}