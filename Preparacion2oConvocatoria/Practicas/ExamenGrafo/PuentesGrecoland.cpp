#include "../Grafos/alg_grafoPMC.h"

struct Ciudad
{
    double x;
    double y;
};

double distanciaEuclidea(Ciudad a, Ciudad b)
{

    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

double viajeGrecoland(vector<Ciudad> &ciudadesFobos, vector<Ciudad> &ciudadesDeimos,
                      vector<bool> &ciudadCosteraFobos, vector<bool> &ciudadCosteraDeimos,
                      typename GrafoP<double>::vertice origen, typename GrafoP<double>::vertice destino)
{

    GrafoP<double> Grafo(ciudadesFobos.size() + ciudadesDeimos.size());

    double distanciaMaxima = 0;

    // CONSTRUYO FOBOS
    for (int i = 0; i < ciudadesFobos.size(); i++)
    {
        for (int j = 0; j < ciudadesFobos.size(); j++)
        {
            if (i == j)
            {
                Grafo[i][j] = 0;
            }
            else
            {
                double distancia = distanciaEuclidea(ciudadesFobos[i], ciudadesFobos[j]);
                Grafo[i][j] = distancia;
                distanciaMaxima = std::max(distancia, distanciaMaxima);
            }
        }
    }

    // CONSTRUYO DEIMOS
    for (int i = 0; i < ciudadesDeimos.size(); i++)
    {
        for (int j = 0; j < ciudadesDeimos.size(); j++)
        {
            if (i == j)
            {
                Grafo[i + ciudadesFobos.size()][j + ciudadesFobos.size()] = 0;
            }
            else
            {
                double distancia = distanciaEuclidea(ciudadesDeimos[i], ciudadesDeimos[j]);
                Grafo[i + ciudadesFobos.size()][j + ciudadesFobos.size()] = distancia;
                distanciaMaxima = std::max(distancia, distanciaMaxima);
            }
        }
    }

    // CONSTRUYO PUENTES FOBOS-DEIMOS//DEIMOS-FOBOS
    for (int i = 0; i < ciudadesFobos.size(); i++)
    {
        for (int j = 0; j < ciudadesDeimos.size(); j++)
        {
            if (ciudadCosteraFobos[i] && ciudadCosteraDeimos[j])
            {
                Grafo[i + ciudadesFobos.size()][j] = Grafo[j + ciudadesFobos.size()][i] = distanciaEuclidea(ciudadesDeimos[i], ciudadesDeimos[j]) + distanciaMaxima;
            }
        }
    }

    Grafo = Kruskall(Grafo);

    // QUITO EL AUMENTO DEL PUENTE
    for(int i=0;i< Grafo.numVert(); i++){
        for(int j=0; j< Grafo.numVert();j++){
            if(Grafo[i][j]>distanciaMaxima)
                Grafo[i][j] -= distanciaMaxima;
        }
    }

    vector<double> costeViajar = Dijkstra(Grafo,origen,vector<typename GrafoP<double>::vertice>(Grafo.numVert()));

    return costeViajar[destino+ciudadesFobos.size()];
    
}