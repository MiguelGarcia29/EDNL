#include <Grafos/alg_grafoPMC.h>

typedef std::pair<size_t, size_t> carretera;
typedef matriz<size_t> costes;

template <typename T>
void quitarCiudadesTomadas(GrafoP<T> &G, vector<size_t> ciudadesTomadas)
{

    // CORTO LAS CONEXIONES CON LA CIUDADES
    for (size_t c : ciudadesTomadas)
    {
        for (int i = 0; i < G.numVert(); i++)
        {
            G[i][c] = G[c][i] = G.INFINITO;
        }
    }
}

template <typename T>
void quitarCarreterasCorta(GrafoP<T> &G, vector<carretera> carreterasCortadas)
{

    // CORTO LAS CARRETERAS
    for (carretera c : carreterasCortadas)
    {
        G[c.first][c.second] = G.INFINITO;
    }
}

template <typename T>
costes distanciasMinimas(GrafoP<T> &G, vector<carretera> carreterasCortadas, vector<size_t> ciudadesTomadas, size_t capital)
{

    costes m(G.numVert());

    quitarCiudadesTomadas(G, ciudadesTomadas);
    quitarCarreterasCorta(G, carreterasCortadas);

    vector<typename GrafoP<T>::nodo> P;
    vector<typename GrafoP<T>::tCoste> desdeCapital = Dijkstra(G,capital,P);
    vector<typename GrafoP<T>::tCoste> haciaCapital = DijkstraInv(G, capital, P);

    for (int i = 0; i < G.numVert(); i++)
    {
        for(int j=0;j<G.numVert();j++){
            m[i][j]=suma(haciaCapital[i],desdeCapital[j]);
        }
    }

    return m;
}
