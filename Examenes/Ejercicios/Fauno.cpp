#include "Grafos/alg_grafoPMC.h"

typedef std::pair<int, int> Coordenada;

size_t coordenadaACasilla(int i, int j, size_t N)
{
    return i * N + j;
}

template <typename tCoste>
GrafoP<tCoste> laberintoMovimientosFauno(size_t N, size_t M)
{
    GrafoP<tCoste> lab(N * M);

    // MOVIMIENTOS DEL FAUNO
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            size_t actual = coordenadaACasilla(i, j, N);
            if (j - 2 >= 0 && i + 1 < M)
                lab[actual][coordenadaACasilla(i + 1, j - 2, N)] = lab[coordenadaACasilla(i + 1, j - 2, N)][actual] = 1;
            if (j - 1 >= 0 && i - 2 >= 0)
                lab[actual][coordenadaACasilla(i - 2, j - 1, N)] = lab[coordenadaACasilla(i - 2, j - 1, N)][actual] = 1;
            if (j + 1 < N && i - 2 >= 0)
                lab[actual][coordenadaACasilla(i - 2, j + 1, N)] = lab[coordenadaACasilla(i - 2, j + 1, N)][actual] = 1;
            if (j + 2 < N && i - 1 >= 0)
                lab[actual][coordenadaACasilla(i - 1, j + 2, N)] = lab[coordenadaACasilla(i - 1, j + 2, N)][actual] = 1;
            if (j + 2 < N && i + 1 < M)
                lab[actual][coordenadaACasilla(i + 1, j + 2, N)] = lab[coordenadaACasilla(i + 1, j + 2, N)][actual] = 1;
            if (j + 1 < N && i + 2 < M)
                lab[actual][coordenadaACasilla(i + 2, j + 1, N)] = lab[coordenadaACasilla(i + 2, j + 1, N)][actual] = 1;
            if (j - 1 >= 0 && i + 2 < M)
                lab[actual][coordenadaACasilla(i + 2, j - 1, N)] = lab[coordenadaACasilla(i + 2, j - 1, N)][actual] = 1;
            if (j - 2 >= 0 && i - 1 >= 0)
                lab[actual][coordenadaACasilla(i - 1, j - 2, N)] = lab[coordenadaACasilla(i - 1, j - 2, N)][actual] = 1;
        }
    }

    return lab;
};

template <typename tCoste>
void colocarTrampas(GrafoP<tCoste> &G, const vector<Coordenada> &trampas, const vector<Coordenada> &mimos, size_t N, size_t M)
{
    for (Coordenada t : trampas)
    {
        size_t cord = coordenadaACasilla(t.first, t.second, N);
        for (int i = 0; i < G.numVert(); i++)
        {
            if (i != cord)
                G[i][cord] = G[cord][i] = G.INFINITO;
        }
    }

    for (Coordenada m : mimos)
    {
        for (int i = 0; i < G.numVert(); i++)
        {
            if (m.first >= 0 && m.second - 1 >= 0)
                G[i][CasillatoVertice(m.first, m.second - 1, N)] =
                    G[CasillatoVertice(m.first, m.second - 1, N)][i] =
                        GrafoP<size_t>::INFINITO;
            if (m.first + 1 < M && m.second - 1 >= 0)
                G[i][CasillatoVertice(m.first + 1, m.second - 1, N)] =
                    G[CasillatoVertice(m.first + 1, m.second - 1, N)][i] =
                        GrafoP<size_t>::INFINITO;
            if (m.first + 1 < M && m.second >= 0)
                G[i][CasillatoVertice(m.first + 1, m.second, N)] =
                    G[CasillatoVertice(m.first + 1, m.second, N)][i] =
                        GrafoP<size_t>::INFINITO;
            if (m.first + 1 < M && m.second + 1 < N)
                G[i][CasillatoVertice(m.first + 1, m.second + 1, N)] =
                    G[CasillatoVertice(m.first + 1, m.second + 1, N)][i] =
                        GrafoP<size_t>::INFINITO;
            if (m.first >= 0 && m.second + 1 < N)
                G[i][CasillatoVertice(m.first, m.second1, N)] =
                    G[CasillatoVertice(m.first, m.second + 1, N)][i] =
                        GrafoP<size_t>::INFINITO;
            if (m.first - 1 >= 0 && m.second + 1 < N)
                G[i][CasillatoVertice(m.first - 1, m.second + 1, N)] =
                    G[CasillatoVertice(m.first - 1, m.second + 1, N)][i] =
                        GrafoP<size_t>::INFINITO;
            if (m.first - 1 >= 0 && m.second >= 0)
                G[i][CasillatoVertice(m.first - 1, m.second, N)] = G[CasillatoVertice(m.first - 1, m.second, N)][i] =
                    GrafoP<size_t>::INFINITO;
            if (m.first - 1 >= 0 && m.second - 1 >= 0)
                G[i][CasillatoVertice(m.first - 1, m.second - 1, N)] =
                    G[CasillatoVertice(m.first - 1, m.second - 1, N)][i] =
                        GrafoP<size_t>::INFINITO;
        }
    }
}

template <typename tCoste>
std::pair<bool, vector<size_t>> escapa(const vector<Coordenada> &trampas, const vector<Coordenada> &mimos, size_t N, size_t M, size_t entrada, size_t destino)
{
    GrafoP<tCoste> G = laberintoMovimientosFauno(N, M);
    colocarTrampas(G, trampas, mimos, N, M);

    vector<size_t> P;
    vector<tCoste> coste = Dijkstra(G, entrada, P);

    if (coste[destino] != G.INFINITO)
    {
        return std::make_pair(true, coste[destino]);
    }
    else
    {
        return std::make_pair(false, coste[destino]);
    }
}
